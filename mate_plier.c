#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//environmental variable
#define NUM_OP 5
#define MAX_IN 64
#define NUM_CONST 2
#define HIGH   "\x1B[34m"
#define RESET "\x1B[0m" 

//GENERAL MATE_PLIER POSSIBLE RETURN
enum {MATE_OK,MATE_ERR,MATE_RETURN, MATE_CONTINUE,MATE_EXIT};
//SYNTAX VERIFICATION POSSIBLE RETURN
enum {SYN_OK, SYN_ERR};
//constant names and val
const char *costant[NUM_CONST] = {"pi", "nep"};
const float value[NUM_CONST] = {3.14159265,  2.71828182};


void help(){
	printf("\nonly two input at the time {fact1 [operation] fact2},\nuse brakets to increment factors\n");
	printf("\n\nAVAILABLE COMMANDS:\nMATE_PLIER:>:q = quit\nMATE_PLIER:>:h = help\nMATE_PLIER:>:c = clear\n");	
	int i;
	printf("\ncostants:\n");
	for(i=0;i<NUM_CONST;i++)printf("%s: %f\n",costant[i],value[i]);
	printf("\n");
	
}

int count_substrings(const char *code, int *first_index, int *first_position) {
    int count = 0;
    int min_pos = -1;
    int min_index = -1;
    
    for (int i = 0; i < NUM_CONST; i++) {
        const char *found = code;
        while ((found = strstr(found, costant[i])) != NULL) {
            int pos = found - code;
            if (min_pos == -1 || pos < min_pos) {
                min_pos = pos;
                min_index = i;
            }
            count++;
            found++; // Sposta il puntatore per evitare loop infinito
        }
    }
    
    if (first_index) {
        *first_index = min_index;
    }
    if (first_position) {
        *first_position = min_pos;
    }
    
    return count;
}




void substring(char* str, int start, int end, char* result) {

	if (start > end || start < 0 || end >= strlen(str)) {
        	printf("Errore: brackets not used correctly\n");
        	return;
    	}

	int ln = end - start + 1;
	for (int i = 0; i < ln; i++) {
        	result[i] = str[start + i];
    	}
    	result[ln] = '\0';

}

void  mergestring(char *str, int start, int end, float res, char *resu){

	char buff1[MAX_IN];
	char buff2[MAX_IN];
	int ln = end -start +1,i;

	for(i=0;i<start;i++){
		buff1[i]=str[i];
	}
	buff1[start]='\0';
	for (i=0;i<strlen(str)-end;i++){
		buff2[i]=str[end+1+i];
	}
	buff2[strlen(str)-end]='\0';

	if(start != 0 && end != strlen(str))
		sprintf(resu,"%s%f%s",buff1,res,buff2);
	if(start ==0 && end != strlen(str) )
		sprintf(resu,"%f%s",res,buff2);
	if(start !=0 && end == strlen(str) )
		sprintf(resu,"%s%f",buff1,res);
	if(start ==0 && end ==0 )
		sprintf(resu,"%f",res);
	return;
}

void const_sub(char* str){
	int pos=0;
	int index=0;
	while(count_substrings(str, &index, &pos)>0){
		char buff[MAX_IN];
		mergestring(str, pos, pos+strlen(costant[index])-1,value[index],str);
	}

}

float solve(char *input){

	int j,i,open=0,closed=strlen(input)-1,num=0;
	float op1,op2;
	char op[NUM_OP]={'+','-','/','*','^'};


	for(j=0;j<(int)(strlen(input));j++){
		if(input[j]=='{'){
			open=j;
			num++;
		}
	}

	//calculate substring
	for(j=0;j<(int)strlen(input);j++){
		if(input[open+j]=='}'){
			closed = open + j;
			}
	}

	if(num != 0){

	char result[MAX_IN];
	char nested[MAX_IN];

	substring(input, open+1, closed-1, result);
	float res_buf = solve(result);
	mergestring(input, open, closed, res_buf, nested);
	return solve(nested);
	}else if(num == 0){
	float res=0;
		for(i=0;i<strlen(input);i++){
			for(j=0;j<NUM_OP;j++){
				if(input[i]==op[j]){
					sscanf(input,"%f%c%f",&op1,&op[j],&op2);
					if(op[j]=='+'){res = op1+op2;return res;}
					if(op[j]=='-'){res = op1-op2;return res;}
					if(op[j]=='*'){res = op1*op2;return res;}
					if(op[j]=='/'){if(op2!=0){res = op1/op2;return res;}
					else{printf("no division by 0");}}
					if(op[j]=='^'){res = pow(op1,op2);return res;}
				}
			}
		}
		sscanf(input,"%f",&res);
		return res;
	}
	return MATE_OK;
}


int err_ver(char *input){
 	int j,open=0,closed=0;
	for (j = 0; j < (int)(strlen(input)); j++){
	if(input[j]=='{')open++;
	else if(input[j]=='}')closed++;
	if(input[j]=='[' || input[j]==']')printf("'[' and ']' are illegal");
	}
	if(open==closed){
		return SYN_OK;
	}else{
		printf("\nSyntax error: unclosed brackets\n");
		return SYN_ERR;
	}
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
		//syntax verify
		if(err_ver(input_bar)!=SYN_OK){
		}else{
			const_sub(input_bar);
			//functional
			if(strcmp(input_bar,":q")==0){
				return MATE_EXIT;
			}else if(strcmp(input_bar,":h")==0){
			help();
			}else if(strcmp(input_bar,":c")==0){
			system("clear");
			}else{
			printf(HIGH "%f\n" RESET,solve(input_bar));
			}
		}
	}
	}else if(argc == 2){
		if(err_ver(argv[1])!=SYN_OK){
			return MATE_ERR;
		}else if(strcmp(argv[1],":h")==0){
		help();
		}else{
			const_sub(argv[1]);			
			printf(HIGH"%f\n" RESET,solve(argv[1]));

		}
	}
	return MATE_EXIT;
}
