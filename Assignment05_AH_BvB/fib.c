//August Ho und Benjamin von Behren

#include "base.h"
// calculates the n-th fibonacci number and prints it on the output
int fib (int n){
    int fn_1 = 1;
    int fn_2 = 1;
    int fn = 1;
	if (n <= 0) {
		prints("n too small");
		println();
	}else if (n <= 2){
		printi(fn);
		println();
	}else{
		while (true){
			if (n <= 2){
				printf("%d\n", fn);
				break;
			}
			fn = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = fn;
			n = n - 1;
		}
	}
	return fn;
}

void test_fib(void){
	prints("Test fib(0): ");
	fib(0);
	prints("Test fib(-5): ");
	fib(-5);
	prints("Test fib(1): ");
	test_equal_i(fib(1), 1);
	prints("Test fib(2): ");
	test_equal_i(fib(2), 1);
	prints("Test fib(6): ");
	test_equal_i(fib(6), 8);
	prints("Test fib(10): ");
	test_equal_i(fib(10), 55);
	prints("Test fib(20): ");
	test_equal_i(fib(20), 6765);
}

int main(void) {
	test_fib();
	return 0;
}
