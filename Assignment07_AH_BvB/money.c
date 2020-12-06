/*
August Ho und Benjamin von Behren
Assignment 07
Aufgabe 2: Währungen umrechnen
*/


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
    switch (m.currency) {
        case DOLLAR:
            printf("%.2f $\n", m.amount);
            break;
        case BITCOIN:
            printf("%.8f Bitcoin\n", m.amount);
            break;
        case EURO:
            printf("%.2f Euro\n", m.amount);
            break;
        case DANSK_KRONE:
            printf("%.2f DKK\n", m.amount);
            break;
    }
}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(1, BITCOIN), DOLLAR), make_money(4273.38, DOLLAR), 1e-3);
	test_value(__LINE__, to_currency(make_money(3.4, EURO), DOLLAR), make_money(3.4*EURO_USD, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(1555, DANSK_KRONE), BITCOIN), make_money(1555*DKK_USD/BITCOIN_USD, BITCOIN), 1e-3);
    test_value(__LINE__, to_currency(make_money(0, DOLLAR), DANSK_KRONE), make_money(0, DANSK_KRONE), 1e-3);
    test_value(__LINE__, to_currency(make_money(500.5, DOLLAR), EURO), make_money(500.5/EURO_USD, EURO), 1e-3);
    test_value(__LINE__, to_currency(make_money(99.99, DANSK_KRONE), EURO), make_money(99.99*DKK_USD/EURO_USD, EURO), 1e-3);
}

// Money, Currency -> Money
// Convert an amount of money to the given target currency.
Money to_currency(Money m, Currency target_currency) {
    if (m.currency == target_currency) {
        return m;
    }

    // Rechne DOLLAR zu target_currency um, rechne alle andere Waehrungen zu DOLLAR um und rufe die Funktion erneut auf.
    Money money_target; // Kann nicht im switch statement deklariert werden.
    Money money_USD;
    money_USD.currency = DOLLAR;
    switch (m.currency) {
        case DOLLAR:
            switch (target_currency) {
                case DOLLAR:    // Ueberfluessig, aber ansonsten kommt eine Warnung beim Kompilieren, dass DOLLAR nicht beachtet wurde.
                    return m;
                case BITCOIN:
                    money_target.amount = m.amount/BITCOIN_USD;
                    money_target.currency = BITCOIN;
                    break;
                case EURO:
                    money_target.amount = m.amount/EURO_USD;
                    money_target.currency = EURO;
                    break;
                case DANSK_KRONE:
                    money_target.amount = m.amount/DKK_USD;
                    money_target.currency = DANSK_KRONE;
                    break;
            }
            return money_target;
        case BITCOIN:
            money_USD.amount = m.amount*BITCOIN_USD;
            return to_currency(money_USD, target_currency);
        case EURO:
            money_USD.amount = m.amount*EURO_USD;
            return to_currency(money_USD, target_currency);
        case DANSK_KRONE:
            money_USD.amount = m.amount*DKK_USD;
            return to_currency(money_USD, target_currency);
    }

    return make_money(1, EURO);
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(877.19, EURO)), 0);
    test_equal_i(compare(make_money(564, DOLLAR), make_money(1, BITCOIN)), -1);
    test_equal_i(compare(make_money(50, DANSK_KRONE), make_money(1, EURO)), 1);
    test_equal_i(compare(make_money(0, DOLLAR), make_money(0, EURO)), 0);
    test_equal_i(compare(make_money(1, BITCOIN), make_money(500, DANSK_KRONE)), 1);
    test_equal_i(compare(make_money(7497.158, EURO), make_money(2, BITCOIN)), 0);
}

// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal,
// -1 if w is smaller than v and +1 otherwise.
int compare(Money m, Money v) {
    const double TOLERANCE = 0.01;
    Money v_currency_of_m = to_currency(v, m.currency);
    double m_amount = m.amount;
    double v_amount = v_currency_of_m.amount;
    if (m_amount < v_amount - TOLERANCE) {
        return -1;
    } else if (m_amount > v_amount + TOLERANCE) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
	printf("%.2f\n", 22.3);
    print_money_test();
    to_currency_test();
    compare_test();
    return 0;
}
