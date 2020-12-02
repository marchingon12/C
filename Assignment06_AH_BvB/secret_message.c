/*
August Ho und Benjamin von Behren

Compile: make secret_message
Run: ./secret_message
*/

#include "base.h"

//todo: Write decode method
/**
 * This function is able to decode a message and the reverse. A new String is initialised with a copy of the given String,
 * then is checked whether each char in the String matches a char in the boundaries 'A' to 'Z'. This way we don't need to
 * add extra conditions for special chars like '!', '.' etc. Once all checks are verified, the conversion takes place.
 * @param  n String that is to be decoded
 * @return   new String that has been decoded from String n
 */
String decode(String n){
	String newString = s_copy(n);
  	for (int i = 0; i <= s_length(n); i++){
	  	if (toupper(n[i]) >= 'A' && toupper(n[i]) <= 'Z'){
		 	if (toupper(n[i]) == n[i]){
				// 90 - n[i] + 65
				char x = 'A' + 'Z' - n[i];
				//char x = 'Z' - s_get(n, i) + 'A';
			 	newString[i] = x;
				//s_set(newString, i, x);
		 	}else{
			 	char x = 'z' - n[i] + 'a';
				//char x = 'z' - s_get(n, i) + 'a';
			 	newString[i] = x;
				//s_set(newString, i, x);
		}
	 }
  }
  return newString;
}

//todo: Write test method for decode
void decode_test (void) {
	printsln("Decode test: ");
    test_equal_s(decode("leibniz"),"ovrymra");
	test_equal_s(decode("august"), "zftfhg");
	test_equal_s(decode("benjaminvonbehren"), "yvmqznrmelmyvsivm");
	test_equal_s(decode("UNIVERSITAET"),"FMREVIHRGZVG" );
	test_equal_s(decode("Programmieren"),"Kiltiznnrvivm");
}
//todo: Write encode method
/**
 * This function uses decode() to do the reverse, since it generally is doing the same thing.
 * @param  n String that is to be encoded
 * @return   new String that has been decoded from String n
 */
String encode(String n){
	String newString = decode(n);
  	return newString;
}
//todo: Write test method for encode
void encode_test (void) {
	printsln("Encode test: ");
    test_equal_s(encode(decode("kekse")), "kekse");
	test_equal_s(encode(decode("knoedel")), "knoedel");
	test_equal_s(encode(decode("frikadellen")), "frikadellen");
	test_equal_s(encode("Kzirh"),"Paris" );
	test_equal_s(encode("Gvovtiznrhofe"),"Telegramisluv");
}

int main(void){
	//todo: Decode this message to get a hint for part c) + d)
	String secret_message = "Kiltiznnrvivm 1 nzxsg Hkzhh. Wrvh rhg pvrmv Dviyfmt ufvi vgdzrtv Kilwfpgv zfu wvn Yrow. Grkk: Wrv Olvhfmt ufvi wzh vmxlwrvivm rhg tzma vrmuzxs fmw kzhhg rm vrmv Avrov.";
	printsln("Decode secret_message: ");
	printsln(decode(secret_message));
	printsln("Encode and decode secret_message: ");
	printsln(encode(decode(secret_message)));
	//call test functions
	decode_test();
	encode_test();
	return 0;
}
