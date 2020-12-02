/*
August Ho und Benjamin von Behren
Assignment 06
Aufgabe 1: Place-Value Notation
Aufgabe 2: Operationen auf einzelnen Bits
*/

/*
    make base_converter
    ./base_converter
    make base_converter && ./base_converter
*/

#include "base.h"

String characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
    Gibt die Laenge der Zahl in der Zielbasis zurueck.
    @param number Zahl, die in der Zielbasis dargestellt werden soll.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
    @return Laenge (Int) der Zahl in der Zielbasis. 
*/
int length_for_base(int number, int base){
    if(number == 0)
        return 1;
    double needed_chars = log(number)/log(base);
    int length = ceil(needed_chars);
    if(length == (int)(needed_chars)){
        length++;
    }
    return length;
}
/*
    Gibt einen dynamisch allokierte String zurueck, der so viele Zeichen hat wie noetig sind um die Zahl in der Zielbasis darzustellen. 
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
    @return Eine Zeichenkette mit der noetigen Anzahl an Stellen mit '#' initialisiert.
*/
String get_string_for_number_and_base(int number, int base){
    int length = length_for_base(number, base);
    String s = xcalloc(sizeof(char), length + 1);
    //printf("length: %d\n", length);
    for(int i = 0; i< length; i++){
        s[i] = '#';
    }
    return s;
}

/*
    Gibt die Zahl number in der Zielbasis als Zeichenkette zurueck.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
    @return String der die Zahl in der Zielbasis enthaelt.
*/
String convert_to_base(int number, int base){
	if (base < 2 || base > 36) {
		return "";
	}
    String s = get_string_for_number_and_base(number, base);
    int length = s_length(s);
	for (int i = 0; i < length; i++)  {
        int position_multiplier = round( pow(base, length - (i + 1)) );
		int digit_value = number / position_multiplier;
        char digit_char = s_get(characters, digit_value);
        s_set(s, i, digit_char);
        number %= position_multiplier;
	}
    return s;
}

/*
    Schoen formatierte Ausgabe der Zahl, die zu konvertieren ist, sowie des Ergebnisses.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
*/
void print_convert(int number, int base){
    printf("Convert %4d to base %2d: %s\n", number, base, convert_to_base(number, base));
}
/*
    Testfaelle fuer convert_to_base.
*/
void test_convert_to_base(){
    print_convert(16, -1);
    test_equal_s(convert_to_base(16, -1), "");
    
    print_convert(10, 1);
    test_equal_s(convert_to_base(10, 1), "");
    
    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");
    
    print_convert(16, 3);
    test_equal_s(convert_to_base(16, 3), "121");
    
    print_convert(16, 16);
    test_equal_s(convert_to_base(16, 16), "10");
    
    print_convert(100, 10);
    test_equal_s(convert_to_base(100, 10), "100");
    
    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");
    
    print_convert(10, 16);
    test_equal_s(convert_to_base(10, 16), "A");
    
    print_convert(100, 2);
    test_equal_s(convert_to_base(100, 2), "1100100");
    
    print_convert(20, 5);
    test_equal_s(convert_to_base(20, 5), "40");
    
    print_convert(1300300300, 36);
    test_equal_s(convert_to_base(1300300300, 36), "LI5Y4S");
}


void print_bits(int number){
    String bits = convert_to_base(number, 2);
    printf("0x%4x : %16s\n", number, bits);
}

void bit_operations(){
    printsln("Bitmagic");
    //what does the following?
    printsln("&");
    int a = 0xaf;
    int b = 0xa5;
    int c = a & b;
    print_bits(a);
    print_bits(b);
    print_bits(c);
    /*
        & ist der bitweise Und-Operator, 
        er vergleicht alle korrespondierenden Bits der beiden Zahlen mit dem Und-Operator.
    */
    
    printsln("|");
    a = 0xb1;
    b = 0x93;
    c = a | b;
    print_bits(a);
    print_bits(b);
    print_bits(c);
    /*
        | ist der bitweise Oder-Operator, 
        er vergleicht alle korrespondierenden Bits der beiden Zahlen mit dem Oder-Operator.
    */
    
    printsln("^");
    a = 0xb1;
    b = 0x33;
    c = a ^ b;
    print_bits(a);
    print_bits(b);
    print_bits(c);
    /*
        ^ ist der bitweise Entweder-Oder-Operator, 
        er vergleicht alle korrespondierenden Bits der beiden Zahlen mit dem Entweder-Oder-Operator.
    */
    
    printsln("<< und >>");
    a = 0x30;
    print_bits(a);
    a <<= 2;
    print_bits(a);
    a >>= 3;
    print_bits(a);
    /*
        << und >> sind die Linksshift- und Rechtsshift-Operatoren, 
        sie verschieben eine Zahl in der Binärdarstellung nach links bzw. rechts, 
        also fügen hinter der Zahl Nullen ein oder entfernen die hinteren Bits.
        Je Bit entspricht dies einem "*2" bzw. "/2".
    */
    
}

/*
    Konvertiert eine Zahl (als String vorliegend) in der Basis base in die entsprechende Dezimalzahl (Integer).
*/
int base_to_decimal(String value_binary, int base) {
    int length = s_length(value_binary);
    int ret = 0;
    for (int i = 0; i < length; i++)  {
        int position_multiplier = round( pow(base, length - (i + 1)) );
        char bit = s_get(value_binary, i);
        String bit_string = s_repeat(1, bit);    // entspricht char zu String
        int bit_value = s_index(characters, bit_string);   // Wert des Bits 
        ret += bit_value * position_multiplier;
    }
    return ret;
}
/*
    Setz den Bit der Zahl value an der Stelle index auf den Wert von bit und gibt die neue (Dezimal-)Zahl zurueck.
*/
int set_bit(int value, int index, bool bit){
    String value_binary = convert_to_base(value, 2);
    int length = s_length(value_binary);
    if (index >= length) {
        return value;
    }
    char bit_char = bit ? '1' : '0';
    int index_from_front = length - (index + 1);
    s_set(value_binary, index_from_front, bit_char);
    return base_to_decimal(value_binary, 2);
}


/*
    Gib true zurück, wenn das Bit am Index index 1 ist, und false, wenn es 0 ist.
*/
bool get_bit(int value, int index ){
    String value_binary = convert_to_base(value, 2);
    int length = s_length(value_binary);
    if (index >= length) {
        return false;
    }
    int bit_value = s_get(value_binary, index) - '0'; // s_get gibt einen Char wieder
    return bit_value;
}

/*
    Testfaelle fuer get_bit und set_bit
*/
void test_get_set_bit(){
    printsln("test_get_bit");
    int a = 0x77;
    print_bits(a);
    
    test_equal_b(get_bit(a,0), true);
    test_equal_b(get_bit(a,1), true);
    test_equal_b(get_bit(a,2), true);
    test_equal_b(get_bit(a,3), false);
    test_equal_b(get_bit(a,4), true);
    test_equal_b(get_bit(a,5), true);
    test_equal_b(get_bit(a,6), true);
    test_equal_b(get_bit(a,7), false);
    test_equal_b(get_bit(a,8), false);
    
    /*
    printsln("test base_to_decimal");
    int test_base = 2;
    int test_number = 0;
    test_equal_i(base_to_decimal(convert_to_base(test_number, test_base), test_base), test_number);
    test_base = 2;
    test_number = 10;
    test_equal_i(base_to_decimal(convert_to_base(test_number, test_base), test_base), test_number);
    test_base = 3;
    test_number = 10;
    test_equal_i(base_to_decimal(convert_to_base(test_number, test_base), test_base), test_number);
    test_base = 11;
    test_number = 20;
    test_equal_i(base_to_decimal(convert_to_base(test_number, test_base), test_base), test_number);
    test_base = 11;
    test_number = 9999;
    test_equal_i(base_to_decimal(convert_to_base(test_number, test_base), test_base), test_number);
    */

    printsln("test_set_bit");
    printsln(convert_to_base(a, 2));
    a = set_bit(a, 0, false);
    test_equal_i(a, 0x76);
    a = set_bit(a, 0, true);
    test_equal_i(a, 0x77);
    a = set_bit(a, 5, false);
    test_equal_i(a, 0x57);
    a = set_bit(a, 1, true);
    test_equal_i(a, 0x57);
    a = set_bit(a, 3, false);
    test_equal_i(a, 0x57);
}


/*
    Extrahiert die Bits der Zahl value von start bis ausschließlich end und gibt diese als Dezimalzahl (Integer) zurueck.
*/
int extract_bits(int value, int start, int end){
    const int INT_SIZE_IN_BITS = sizeof(int) * 8;
    if (start < 0 || start >= end || end > INT_SIZE_IN_BITS - 1) {
        return 0;
    }
    int left_shift = (INT_SIZE_IN_BITS - 1) - end;
    value = value << left_shift;
    int right_shift = left_shift + start;
    value = value >> right_shift;
    return value;
}

/*
    Testfaelle fuer extract_bits.
*/
void test_extract_bits(){
    printsln("test_extract_bits");
    test_equal_s(convert_to_base(extract_bits(0x1805, 0, 4),2), "101");
    test_equal_s(convert_to_base(extract_bits(0x1404, 8, 16),2), "10100");
    test_equal_s(convert_to_base(extract_bits(0x1701, 12, 16),2), "1");
    test_equal_s(convert_to_base(extract_bits(0x1503, 1, 9),2), "10000001");
    test_equal_s(convert_to_base(extract_bits(0x1602, 0, 16),2), "1011000000010");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 16, 0),2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, -1, 3),2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 4, 34),2), "0");
}

int main(void){
    test_convert_to_base();

    printsln("------------------------------");
    bit_operations();
    bit_operations();
    printsln("------------------------------");
    test_get_set_bit();
    test_extract_bits();
    
    return 0;
}
