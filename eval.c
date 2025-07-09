#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "eval.h"

const char func[] = "*/+-^"; 
const char *adv_func[] = {"exp", "sin", "cos", "tan", "log", "ln"};

void remove_par(char *str) {
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != '(' && str[i] != ')') {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}

void remove_space(char *str) {
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}



equation fill_fields(char  *input){

	int check = 0;
	equation new_eq;
	new_eq.n_op = 1;


	int len = strlen(input);
	for(int i = 0 ; i<len; i++){
		for(int j = 0 ; j<5; j++){
			if(func[j] == input[i]){
				new_eq.sign[check] = func[j];
				int bias = 0;

				for(int k = i ;k< len; k++){
					if (input[k] == ')')bias++;if (input[k] == '(') bias--;
				}

				if(bias<0){
					printf("invalid sintax [missing ')' or '(']\n");
					new_eq.status = NOT_VALID;
					return new_eq;
				}
				new_eq.bias[check] = bias;


				check++;
				new_eq.n_op++;
			}
		}

	}

	int i=0;
	remove_par(input);
	char *start = input;
	while (start) {
		char *end = strpbrk(start, func);  
		if (end) *end = '\0';              
		new_eq.op[i++] = atof(start);      

		if (end) start = end + 1;         
		else break;
	}

	if(check == 0){
		//printf("invalid sintax [No operation detected]\n");
		strcpy(new_eq.single_res, input);
		new_eq.status = NOT_VALID;
	}else{
		new_eq.status = VALID;
	}


	return new_eq;
}

equation gen_priority(equation my_eq){

	for(int i=0;i<my_eq.n_op;i++){

		switch (my_eq.sign[i]){
		case '+': my_eq.priority[i] = 0 + my_eq.bias[i]*10; break;	
		case '-': my_eq.priority[i] = 1 + my_eq.bias[i]*10; break;	
		case '*': my_eq.priority[i] = 3 + my_eq.bias[i]*10; break;	
		case '/': my_eq.priority[i] = 2 + my_eq.bias[i]*10; break;	
		case '^': my_eq.priority[i] = 4 + my_eq.bias[i]*10; break;
 		default:
		}
		
		if(i > 0 && my_eq.sign[i] == my_eq.sign[i-1] && my_eq.bias[i] == my_eq.bias[i-1] ) my_eq.priority[i] = my_eq.priority[i-1]+ 0.1;
	}

	return my_eq;

}


equation solve(equation my_eq){

	float tmp = -1;
	int indx = 0;
	float res =0;

	while(my_eq.n_op != 1){
		tmp = -1;
 		indx = 0;
		for(int i=0;i<my_eq.n_op-1;i++){
			if(my_eq.priority[i]>tmp){
				tmp = my_eq.priority[i];

				indx=i;
			}
		}
	

		switch (my_eq.sign[indx]){
			case '+': res = my_eq.op[indx] + my_eq.op[indx+1]; 
			break;	
			case '-':res = my_eq.op[indx] - my_eq.op[indx+1]; 
			break;	
			case '*': res = my_eq.op[indx] * my_eq.op[indx+1]; 
			break;	
			case '/':res = my_eq.op[indx] / my_eq.op[indx+1];  
			break;	
			case '^':res = pow(my_eq.op[indx],my_eq.op[indx+1]);  
			break;	
	 		default:
		}

		my_eq.op[indx] = res;
	
	
			 // SHIFT: elimina op[indx + 1]
		for (int i = indx + 1; i < my_eq.n_op - 1; i++) {
		    my_eq.op[i] = my_eq.op[i + 1];
		}

		// SHIFT: elimina sign[indx] e priority[indx]
		for (int i = indx; i < my_eq.n_op - 2; i++) {
		    my_eq.sign[i] = my_eq.sign[i + 1];
		    my_eq.priority[i] = my_eq.priority[i + 1];
		}

		

		my_eq.n_op--;

	}

	
	my_eq.res = my_eq.op[0];
	my_eq.status = SOLVED;
	
	return my_eq;
}

int check_func(char *input) {

 	char buffer[1024];
	for (int i = 0; i < strlen(input); i++) {
		for (int f = 0; f < 6; f++) {
			int len = strlen(adv_func[f]);
			if (strncmp(&input[i], adv_func[f], len) == 0) {
				int start = i + len;
				if (input[start] != '(') {
				    printf("invalid function syntax\n");
				    return 0;
				}

				int open = 1, j = start + 1;
				while (open && input[j] != '\0') {
				    if (input[j] == '(') open++;
				    else if (input[j] == ')') open--;
				    j++;
				}

				if (open != 0) {
				    printf("mismatched parentheses in function\n");
				    return 0;
				}

				char inner_expr[256];
				strncpy(inner_expr, &input[start + 1], j - start - 2);
				inner_expr[j - start - 2] = '\0';

				//recursive
				float value = eval(inner_expr); 

		 		float result = 0;
				switch(f){
				case 0:result = exp(value); break;
				case 1:result = sin(value); break;
				case 2:result = cos(value);  break;
				case 3:result = tan(value);  break;
				case 4:result = log10(value);  break;
				case 5:result = log(value);  break;
				default:return 0;
				}
				
				//concatenate result
				snprintf(buffer, sizeof(buffer), "%.8f", result);
				char temp[1024];
				strcpy(temp, &input[j]);      
				input[i] = '\0';  
				strcat(input, "(");           
				strcat(input, buffer);  
				strcat(input, ")");      
				strcat(input, temp);         
				i = -1; 
				break;


			}
		}
	}
	return 1;
}



float eval (char *input){

	//remove sapces
	remove_space(input);
	check_func(input);
	remove_space(input);
	//create the equation variable
	equation new_eq = fill_fields (input);
	

	//check if format is valid
	if(new_eq.status == NOT_VALID){
		return atof(new_eq.single_res);
	}

	// build priority tree
	new_eq = gen_priority(new_eq);

	//solve
	new_eq = solve(new_eq);
	
	//return result
	return new_eq.res;

}