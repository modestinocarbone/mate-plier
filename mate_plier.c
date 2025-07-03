#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"
#define HIGH   "\x1B[34m"
#define RESET "\x1B[0m" 
#define MAX_IN 64

void help(){
	printf("\nRemember to use the parenthesis '(', ')'\n");
	printf("\nAVAILABLE COMMANDS:\nMATE_PLIER:>:q = quit\nMATE_PLIER:>:h = help\nMATE_PLIER:>:c = clear\n");
	printf("\n");
}

int main(int argc,char **argv){

	char input_bar[MAX_IN];
	char input_buff[MAX_IN];

	if(argc ==1){

	while(1){

	printf("MATE_PLIER:>");
	fflush(stdin);
	scanf("%s", input_buff);
	sscanf(input_buff,"%s\n",input_bar);

		//functional
		if(strcmp(input_bar,":q")==0){
			return 0;
		}else if(strcmp(input_bar,":h")==0){
			help();
		}else if(strcmp(input_bar,":c")==0){
			system("clear");
		}else{

			float res =  eval(input_bar);

			if (res - (int)res == 0) 
				printf(HIGH "%d\n" RESET, (int)res);
			else 
				printf(HIGH "%f\n" RESET,res);
					
		}
		
	}
	
	}

}