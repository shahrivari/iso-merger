#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>

#define MAXN 128
#include "nauty.h"
 #include "nautinv.h"

#define BUFSIZE 64*1024
#define RADIX 32


static void printhelp(void)
{
	printf("XXX: a duplicate finder\n\n");
	printf("options:\n");
	printf("\t-s size  \tsize of the subgraphs\n");
}


int main(int argc, char *argv[]){
	static int subgraph_size=0;
	graph g[MAXN*MAXM];
	graph canong[MAXN*MAXM];
	int lab[MAXN],ptn[MAXN],orbits[MAXN];
	static DEFAULTOPTIONS_DIGRAPH(options);
	statsblk stats;
	
	if(argc<2){
		printhelp();
		return 0;
	}
		
	for (int i = 1; i < argc; i++) {
		switch (argv[i][0] == '-' ? argv[i][1] : 'h') {
		case 's':
			subgraph_size = atoi(argv[i][2] ? argv[i] + 2 : argv[++i]);
			break;
		default:
			printhelp();
			return 0;
		}
	}
	
	if (subgraph_size > MAXN)
        {
            printf("size of graph must be in the range 1..%d\n",MAXN);
            exit(1);
        }
	
	options.defaultptn = TRUE;
	options.getcanon = TRUE;
	
	
	char line[BUFSIZE];
	char adj_str[BUFSIZE];
	char bin_adj[BUFSIZE];
	char zeroed_adj[BUFSIZE];
	char str[BUFSIZE];

	int n=subgraph_size;
	int m=SETWORDSNEEDED(n);
	nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);
	
	mpz_t integ;
	mpz_init (integ);
	long freq=0;
	
	while(fgets(line, sizeof(line), stdin)) {		
		sscanf(line,"%s %ld\n",adj_str,&freq);
		mpz_set_str(integ,adj_str,RADIX);
		mpz_get_str(bin_adj,2,integ);
		int bin_len=strlen(bin_adj);
		if(bin_len<subgraph_size*subgraph_size){
			memset(zeroed_adj,'0',subgraph_size*subgraph_size-bin_len);
			strcpy(zeroed_adj+subgraph_size*subgraph_size-bin_len,bin_adj);
		}
		
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
		mpz_set_str(integ,str,2);
		mpz_get_str(str,32,integ);
		//printf("zero %s %ld\n",str,freq);		
		printf("%s %ld\n",str,freq);		
	  };

	return 0;  
}