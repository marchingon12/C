/*
August Ho und Benjamin von Behren
Assignment 05
Aufgabe 2: Guess my number
*/

#include "base.h"

int main() {
	int number = i_rnd(101);
	printsln("Rate meine Zahl. Sie liegt im Intervall [0,100]");
	while(true) {
		int guess = i_input();
		if (number > guess) {
			printsln("Zahl zu klein!");
		} else if (number < guess) {
			printsln("Zahl zu gross!");
		} else {   // Gleichheit
			printsln("Zahl korrekt!");
			break;
		}

	}

	return 0;
}
