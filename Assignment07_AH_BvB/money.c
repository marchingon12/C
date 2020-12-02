/*
Compile: make money
Run: ./money
make money && ./money
*/

#include "base.h"


const double BITCOIN_USD = 4273.38; // 1 Bitcoin = 4273.38 USD
const double EURO_USD = 1.14; 		// 1 EURO = 1.14 USD
const double DKK_USD = 0.15; 		// 1 Dansk Krone (DKK) = 0.15 USD

enum Currency { BITCOIN, DOLLAR, EURO, DANSK_KRONE }; 
typedef enum Currency Currency;

struct Money { double amount; Currency currency; }; 
typedef struct Money Money;

// double, Currency -> Money
// Initialize a Money structure.
Money make_money(double amount, Currency currency) {
    Money m = { amount, currency };
    return m;
}

// int Money, Money, double -> bool
// Test wheather the actual value of the money is within +/- tolerance of the expected value of the money.
bool test_value(int line, Money a, Money e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.currency, e.currency);
    return x && u;
}

void print_money(Money m);

void print_money_test() {
    print_money(make_money(1234, DOLLAR));
    print_money(make_money(1.234, BITCOIN));
    print_money(make_money(1.34, EURO));
    print_money(make_money(27.50, DANSK_KRONE));
}

// Money -> void
// Print the ammount of money.
void print_money(Money m) {
    // todo: implement

}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(1, BITCOIN), DOLLAR), make_money(4273.38, DOLLAR), 1e-3);
    // todo: add tests (at least 5)
	
    
}

// Money, Currency -> Money
// Convert an amount of money to the given target currency.
Money to_currency(Money m, Currency target_currency) {
    // todo: implement
    return make_money(1, EURO);
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(877.19, EURO)), 0);
    // todo: add tests (at least 5)
	
    
}
    
// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal, 
// -1 if w is smaller than v and +1 otherwise.
int compare(Money m, Money v) {
    // todo: implement. May use the fabs function. fabs(double input) returns the absolute value of input.
    
    return 0;
}

int main(void) {
	printf("%.2f\n", 22.3);
    print_money_test();
    to_currency_test();
    compare_test();
    return 0;
}
