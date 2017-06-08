#include <stdio.h> 
#define MAX_LEN 8
#define SPACE " "

int main() { 
	int sym;
	while((sym = getchar()) != EOF){
		if(sym == '\t'){
			printf(" {There is tab, I found it, master}");
			for(int i = 0; i < MAX_LEN; i++){
				printf(SPACE);
			}
		}
		else{
			printf("%c", sym);
		}
	}
return 0; 
