#ifndef EVAL_H
#define EVAL_H

#define MAX_OP 20



typedef enum{
	VALID,
	NOT_VALID,
	SOLVED
}status_t;

typedef struct{
	float op[MAX_OP];
	char sign[MAX_OP-1];
	float priority[MAX_OP-1]; 
	float bias[MAX_OP-1]; 
	status_t status;
	int n_op;
	float res;
}equation;


void remove_par(char *str);
equation fill_fields(char  *input);
equation gen_priority(equation my_eq);
equation solve(equation my_eq);
float eval (char *input);

#endif