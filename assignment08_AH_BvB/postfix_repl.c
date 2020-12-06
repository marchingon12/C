/*
	make postfix_repl && ./postfix_repl
*/

#include "base.h"

/*
    Macro for testing if a condition is valid for all i's in the range of [0, length)].
    e.g.
    int length = 10;
    int x[length];
    
    ensure("Array initialized with 0's", forall_i(length, x[i] == 0));

*/
#define forall_i(length, condition) ({\
   bool result = true;\
   for (int i = 0; i < length; i++) { if (!(condition)) { result = false; break; } }\
   result;\
})


#define STACK_SIZE  10

typedef enum {
	OPERATION, VALUE, EMPTY
} Tag;



typedef struct{
	Tag tag;
	
	union{
		int value;
		char operation;
	};
} StackElement;

typedef struct{
	StackElement elements[STACK_SIZE];
	int stack_pointer;
    int stack_height;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c){
	return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks wheter c is a digit
bool is_digit(char c){
	return c >= '0' && c <= '9';
}

//todo:
StackElement make_stack_element(Tag tag){
	StackElement ele;
	return ele;
} 
//todo:
StackElement make_value(int value){
	StackElement ele;
	return ele;
}
//todo:
StackElement make_operation(char operation){
	StackElement ele; 
	return ele;
}


bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}

//todo:
void clear_stack(Stack* stack){
	//todo
}

void push(StackElement element, Stack* stack){
    require_not_null(stack);
	if(stack->stack_pointer < (stack->stack_height - 1)){
		stack->stack_pointer++;
		stack->elements[stack->stack_pointer] = element;
	}
}

StackElement pop(Stack* stack){
    require_not_null(stack);
    require("non empty stack", stack->stack_pointer >= 0);
    StackElement ele = stack->elements[stack->stack_pointer ];
    stack->elements[stack->stack_pointer] = make_stack_element(EMPTY);
	stack->stack_pointer--;
	return ele;
}

//todo:
void print_stack_element(StackElement ele){
	//todo
}

//todo:
void print_stack(Stack* stack, int n){
	//todo:
}

void compute(Stack* stack){
	//todo
}

int main (void){	
	Stack stack;
    stack.stack_height = STACK_SIZE;
	clear_stack(&stack);
	

	int input_size = 128;	
	char input[input_size];
	
	for(int i = 0; i< input_size; i++){
		input[i] = '\0';
	}
	int input_index = 0;
	
	
	int c;
	while((c = getchar()) != 'q'){

		if(c == '\n'){
			for(int i = 0; i< input_index; i++){
                char c = input[i];
				//todo:
				
			}
			
			for(int i = 0; i< input_size; i++){
				input[i] = '\0';
			}
			input_index = 0;
			
		}else{
			input[input_index] = c;
			input_index++;
		}

	
	}
	return 0;
}