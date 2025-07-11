#ifndef EVAL_H
#define EVAL_H

#define MAX_OP 20

//equation possible states
typedef enum{
	VALID,
	NOT_VALID,
	SOLVED
}status_t;

//equation structure
typedef struct{
	float op[MAX_OP];
	char sign[MAX_OP-1];
	char single_res[MAX_OP];
	float priority[MAX_OP-1]; 
	float bias[MAX_OP-1]; 
	status_t status;
	int n_op;
	float res;
}equation;

//functions
void remove_par(char *str);
equation fill_fields(char  *input);
equation gen_priority(equation my_eq);
equation solve(equation my_eq);
float eval (char *input);

#endif