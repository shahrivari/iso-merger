#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 64*1024

static void printhelp(void)
{
	printf("reducer: merges duplications\n\n");
}


int main(int argc, char *argv[]){
	if(argc!=1){
		printhelp();
		return 0;
	}
	
	char line[BUFSIZE];
	char key[BUFSIZE];
	char last_key[BUFSIZE];

	long long freq=0;
	long long total_freq=0;
	int first_time=1;
	
	while(fgets(line, sizeof(line), stdin)) {		
		sscanf(line,"%s %lld\n",key,&freq);		
		if(first_time){
			first_time=0;
			strcpy(last_key,key);
			total_freq=freq;
			continue;			
		}
		
		//printf("%s %s\n",last_key,key);
		
		if(!strcmp(last_key,key)){
			total_freq+=freq;
		}else{
			printf("%s %lld\n",last_key,total_freq);
			total_freq=freq;
			strcpy(last_key,key);
		}
	  };
	  
	printf("%s %lld\n",last_key,total_freq);
	return 0;  
}