#include "org_tmu_core_Nauty.h"
#include <stdlib.h>
#include <string.h>

#define MAXN 128
#include "nauty.h"
#include "nautinv.h"

#define BUFSIZE 64*1024


JNIEXPORT jobjectArray JNICALL Java_org_tmu_core_Nauty_canonize
  (JNIEnv * env, jobject thisobj, jobjectArray arr, jint k){
    int subgraph_size=0;
	graph g[MAXN*MAXM];
	graph canong[MAXN*MAXM];
	int lab[MAXN],ptn[MAXN],orbits[MAXN];
	static DEFAULTOPTIONS_DIGRAPH(options);
	statsblk stats;

	subgraph_size=k;
		
	
	if (subgraph_size > MAXN)
        {
            printf("size of graph must be in the range 1..%d\n",MAXN);
            return NULL;
        }
	
	options.defaultptn = TRUE;
	options.getcanon = TRUE;
	
	
	char bin_adj[BUFSIZE];
	char zeroed_adj[BUFSIZE];
	char str[BUFSIZE];

	int n=subgraph_size;
	int m=SETWORDSNEEDED(n);
	nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);
	
	int stringCount = GetArrayLength(env, arr);
	
	jobjectArray ret;
	ret= (jobjectArray)env->NewObjectArray(stringCount,  
         env->FindClass("java/lang/String"),  
         env->NewStringUTF(""));
		 

    
	for (int i=0; i<stringCount; i++) {
        jstring string = (jstring) GetObjectArrayElement(env, arr, i);
        const char *rawString = GetStringUTFChars(env, string, 0);
        strcpy(bin_adj,rawString);
		ReleaseStringUTFChars(rawString);
		int bin_len=strlen(bin_adj);
		if(bin_len<subgraph_size*subgraph_size){
			memset(zeroed_adj,'0',subgraph_size*subgraph_size-bin_len);
		}
		strcpy(zeroed_adj+subgraph_size*subgraph_size-bin_len,bin_adj);		
		EMPTYGRAPH(g,m,n);
		for (int i = 0; i < subgraph_size; i++)
            for (int j = 0; j < subgraph_size; j++)
                if (i!=j&&zeroed_adj[i * subgraph_size + j] == '1')
						ADDONEARC(g,i,j,m);
		
		densenauty(g,lab,ptn,orbits,&options,&stats,m,n,canong);
		
		memset(str,'0',subgraph_size*subgraph_size);
		for (int i = 0; i < subgraph_size; i++) {	
			for(int j = 0; j < subgraph_size; j++) {
				if(i!=j&&zeroed_adj[lab[i]*subgraph_size+lab[j]]=='1') 
					str[i*subgraph_size+j]='1';
			}
		}
		str[subgraph_size*subgraph_size]=0;
		
		env->SetObjectArrayElement(ret,i,env->NewStringUTF(str));
    }   
	
	return ret;  
}