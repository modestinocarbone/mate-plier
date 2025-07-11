#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"

#include <editline/readline.h>
#include <editline/history.h>

#define HIGH   	"\x1B[34m"
#define RESET 	"\x1B[0m" 
#define MAX_LEN 4096

void help(){
	printf("\nRemember to use the parenthesis '(', ')'\n");
	printf("\nAVAILABLE COMMANDS:\n\nMATE_PLIER:>:q = quit\nMATE_PLIER:>:h = help\nMATE_PLIER:>:c = clear\n");
	printf("\nfunctions:\nexp = exponentital\nsin = sine\ncos = cosine\ntan = tangent\nlog = logarithm in base 10\nln = logarithm in base e\n");
	printf("\n");
}

int main(int argc,char **argv){

	if(argc ==1){

	while(1){


	char* input_bar = readline("MATE_PLIER:> ");

	/* Add input to history */
	add_history(input_bar);

   	
	

		//functional
		if(strcmp(input_bar,":q")==0){
			free(input_bar);
			return 0;
		}else if(strcmp(input_bar,":h")==0){
			help();
		}else if(strcmp(input_bar,":c")==0){
			system("clear");
		}else{
			char extended_buffer[4096];
  			strcpy(extended_buffer, input_bar);
			float res =  eval(extended_buffer);

			if (res - (int)res == 0) 
				printf(HIGH "%d\n" RESET, (int)res);
			else 
				printf(HIGH "%f\n" RESET,res);
					
		}
	
	free(input_bar);

	}
	
	}

}