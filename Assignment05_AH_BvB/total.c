/*
August Ho und Benjamin von Behren

Compile: make total-solution
Run: ./total-solution
make total-solution && ./total-solution

Aufgabe 1: Rabatt aud Schokoriegel
- =1 Riegel kostet pro Stück 50cent
- >=10 Riegeln kostet pro Stück 45cent
- >=100 Riegeln kostet pro Stück 40cent
- <0 Riegeln kostet 0cent
- Wenn Gesamtpreis unter 2000cent dann Versandskosten = 500cent
- Gesamtpreis > 2000cent dann Versandskosten = 0cent
*/

#include "base.h"

//todo: define constants
const int SMALL = 50;			//Preis für 1-9 Riegeln
const int MEDIUM = 45;			//Preis für 10-99 Riegeln
const int LARGE = 40;			//Preis für 100-infinity Riegeln
const int DELIVERY = 500;		//Versandskosten
const int GRENZE = 2000;		//Grenze, ab der keine Versandkosten mehr anfallen.

//todo: Write function total
/**
 * Diese Funktion berechnet den Gesamtpreis:
 * Die Summe von den Preis für die Anzahl an gekauften Riegeln und Versandskosten.
 * @param  Riegel 		Anzahl der Riegeln
 * @return Gesamtpreis	Preis nach Anzahl Riegeln + Versandskosten
 */
int total (int Riegel){
	int Preis;
    if (Riegel > 99){
		Preis = LARGE;
	}else if (Riegel > 9){
		Preis = MEDIUM;
	}else if (Riegel > 0){
		Preis = SMALL;
	}else{
		Preis = 0;
	}

	int Gesamtpreis = Riegel * Preis;
	if (Gesamtpreis <= GRENZE && Gesamtpreis > 0){
		Gesamtpreis += DELIVERY;
	}
	return Gesamtpreis;
}


//todo: Write function total_test
void total_test(void) {
	test_equal_i(total(1), 550); // given 1, expect 50 + 500 = 550
	test_equal_i(total(10), 950); // given 10, expect 450 + 500 = 950
	test_equal_i(total(-5), 0); // given -5, expect 0
	test_equal_i(total(100), 4000); // given 100, expect 4000
	test_equal_i(total(30), 1850); // given 100, expect 1350 + 500 = 1850
	test_equal_i(total(60), 2700); // given 100, expect 2700
}

int main (void){
	//todo: call total_test Function
	total_test();
}
