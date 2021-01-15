/*
August Ho und Benjamin von Behren
Assignment 08
Aufgabe 3: Meine erste eigene Postfix REPL
*/


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

// Creates a stack element of the given tag.
StackElement make_stack_element(Tag tag){
    require("valid tag", tag == EMPTY || tag == VALUE || tag == OPERATION);
	StackElement ele;
    ele.tag = tag;
	return ele;
} 
// Creates a stack element with the given value.
StackElement make_value(int value){
	StackElement ele;
    ele.tag = VALUE;
    ele.value = value;
	return ele;
}
// Creates a stack element with the given operation.
StackElement make_operation(char operation){
    require("valid operation", operation == '+' || operation == '-' || operation == '*' || operation == '/');
	StackElement ele;
    ele.tag = OPERATION;
    ele.operation = operation;    
	return ele;
}


bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}

// Set the elements of the given stack to EMPTY and set the stack pointer to -1 to indicate an empty stack.
void clear_stack(Stack* stack){
	require_not_null(stack);
    stack->stack_pointer = -1;
    for (int i = 0; i < stack->stack_height; i++) {
        stack->elements[i] = make_stack_element(EMPTY);
    }
    ensure("stack_pointer is -1", stack->stack_pointer == -1);
    ensure("stack is empty", forall_i(STACK_SIZE, stack->elements[i].tag == EMPTY));
}

/*
    Schreibt das gegebene Element auf den gegebenen Stack (ohne Ausgabe).
    Wenn der Stack voll ist, wird nichts gemacht, da die Bedingung in der If-Schleife dann false ist.
    Deshalb sollte dies lieber mit einer Precondition abgefragt werden um bei vollem Stack eine Fehlermeldung zu bekommen.
*/
void push(StackElement element, Stack* stack){
    require_not_null(stack);
	if(stack->stack_pointer < (stack->stack_height - 1)){
		stack->stack_pointer++;
		stack->elements[stack->stack_pointer] = element;
	}
}

/*
    Liest das oberste Element vom gegebenen Stack und gibt dies wieder.
*/
StackElement pop(Stack* stack){
    require_not_null(stack);
    require("non empty stack", stack->stack_pointer >= 0);
    StackElement ele = stack->elements[stack->stack_pointer ];
    stack->elements[stack->stack_pointer] = make_stack_element(EMPTY);
	stack->stack_pointer--;
	return ele;
}

// Prints the stack element.
void print_stack_element(StackElement ele){
	switch (ele.tag) {
        case VALUE:
            printf("[%d]", ele.value);
            break;
        case OPERATION:
            printf("[%c]", ele.operation);
            break;
        case EMPTY:
            printf("[ ]");
            break;
    }
}

// Print the first n elements from the given stack.
void print_stack(Stack* stack, int n){
	require_not_null(stack);
    int stack_pointer = stack->stack_pointer;
    printf("stack:\n");
    for (int i = stack_pointer; i >= stack_pointer - n; i--) {
        print_stack_element(stack->elements[i]);
        printf("\n");
    }
    printf("\n");
}

void compute(Stack* stack){
    StackElement element_on_top = stack->elements[stack->stack_pointer];
    if (element_on_top.tag == OPERATION) {
        
        require_not_null(stack);
        require("enough (>3) elements for operation on stack", stack->stack_pointer >= 2);
        require("valid first element for operation", stack->elements[stack->stack_pointer - 1].tag == VALUE);
        require("valid second element for operation", stack->elements[stack->stack_pointer - 2].tag == VALUE);
        ensure_code(int stack_pointer_start = stack->stack_pointer);
        
        //printsln("compute:");
        //print_stack(stack, stack->stack_pointer);
        char operation = pop(stack).operation;
        int first_value = pop(stack).value;
        int second_value = pop(stack).value;
        int result = 0;
        //printf("operation: %c\n", operation);
        //printf("first_value: %d\n", first_value);
        //printf("second_value: %d\n", second_value);
        
        switch (operation) {
            case '+':
                result = second_value + first_value;
                break;
            case '-':
                result = second_value - first_value;
                break;
            case '*':
                result = second_value * first_value;
                break;
            case '/':
                result = second_value / first_value;
                break;
            default:
                assert("known opertation", false);
        }
        
        push(make_value(result), stack);
        
        
        
        //print_stack(stack, stack->stack_pointer);
        
        
        ensure("VALUE was written on stack", stack->elements[stack->stack_pointer].tag == VALUE)
        //ensure("non-negativ result", stack->elements[stack->stack_pointer].value >= 0)
        ensure("stack has two elements less than before", stack->stack_pointer == stack_pointer_start - 2)
    }
}

int main (void){	
	Stack stack;
    stack.stack_height = STACK_SIZE;
	clear_stack(&stack);
    
    /*
    push(make_operation('+'), &stack);
    push(make_stack_element(EMPTY), &stack);
    push(make_value(23), &stack);
    print_stack(&stack, 3);
    clear_stack(&stack);
    */
    
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
				
                char c_previous;
                if (i == 0) {
                    c_previous = ' ';
                } else {
                    c_previous = input[i - 1];
                }
                
                char c_next = input[i + 1];
                if (c_next == '\0') {   // c is the last char of the input
                    c_next = ' ';
                }
                
                
                // skip spaces
                if (c == ' ') {
                    continue;
                }
                
                // check wether input is an operation
                if (c_previous == ' ' && is_operation(c) && c_next == ' ') {
                    push(make_operation(c), &stack);
                    print_stack(&stack, stack.stack_pointer);
                    
                    compute(&stack);
                    //printf("computed stack\n");
                    print_stack(&stack, stack.stack_pointer);
                    
                    continue;
                }
                
                
                // check wether input is a number (VALUE)
                if (c_previous == ' ' && (is_digit(c) || c == '-')) {
                    if (c == '-' && c_next == ' ') {  // c is not a number but an operation
                        continue;                     // optional because loop continues when operation was found
                    }
                    bool negative_number = false;
                    if (c == '-' && is_digit(c_next)) {
                        negative_number = true;
                        i++;    // increase i to treat the negative number like a positive one (only digits, no '-')
                                // decreasing i later is optional because the next loop run will not find a new token
                    }
                    
                    // check how many following numbers there are
                    int value_length = 0;
                    while (is_digit(input[i + value_length])) {
                        value_length++;
                    }
                    
                    // convert input to integer
                    int value = 0;
                    for (int j = 0; j < value_length; j++) {
                        int digit = input[i + j] - '0';
                        value += digit * round(pow(10, value_length - (j + 1)));
                    }
                    if (value_length >= 10) {
                        printf("value with length %d may cause over- or underflow\n", value_length);
                    }
                    
                    if (negative_number) {
                        value *= -1;
                        i--;
                    }
                    
                    push(make_value(value), &stack);
                    print_stack(&stack, stack.stack_pointer);
                    
                    continue;
                }
                
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