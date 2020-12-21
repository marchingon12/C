/*
August Ho und Benjamin von Behren
Assignment 09
Aufgabe 1: Zeichenketten find and replace
*/

/*
    make string_replace
    ./string_replace
    make string_replace && ./string_replace
*/
#include "base.h"

/**
Return a pointer to the first occurence of find in s or NULL if find is not in s.
*/
char* next_occurence(char* s, char* find){
    int s_len = s_length(s);
    int find_len = s_length(find);
    // loop through s
    for (int i = 0; i < s_len - (find_len - 1); i++) {  // find cannot be found in the last find_len - 1 chars
        bool find_is_found = true;
        // compare s+i with find
        for (int j = 0; j < find_len; j++) {
            if (find_is_found) {  // do not overwrite find_is_found if one char was different already
                find_is_found = s[i+j] == find[j];
            }
        }
        
        if (find_is_found){
            return s + i;
        }
    }
    return NULL;
}

void test_next_occurence(){
    test_equal_s(next_occurence("aabbccdd", "aa"), "aabbccdd");
    test_equal_b(next_occurence("abbccdd", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa") == NULL, true);
    test_equal_s(next_occurence("abbccdda", "a"), "abbccdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye") == NULL, true);
}

/**
Return how often find is in s.
*/
int count(char* s, char* find){
    int find_len = s_length(find);
    char* next_find = next_occurence(s, find);
    if (next_find == NULL) {
        return 0;
    } else {
        char* continue_search = next_find + find_len;
        return 1 + count(continue_search, find);
    }
}

void test_count(){
    test_equal_i(count("aabbccdd", "aa"), 1);
    test_equal_i(count("abbccdda", "aa"), 0);
    test_equal_i(count("aabbaadd", "aa"), 2);
    test_equal_i(count("aabbccdd", "a"), 2);
    test_equal_i(count("aabbccdd", "abbc"), 1);
    test_equal_i(count("Die Uhrzeit ist 3:10", "Uhrzeit"), 1);
    test_equal_i(count("hello, hello world", "hello"), 2);
    test_equal_i(count("hello, hello world", "lo"), 2);
}

/**
Copies n chars from source to destination.
*/
void copy(char* destination, char* source, int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

/**
Create a new string which is a copy of s but find is replaced by replace_by.
*/
char* replace(char* s, char* find, char* replace_by){
    int s_len = s_length(s);
    int find_len = s_length(find);
    int replace_by_len = s_length(replace_by);
    int find_count = count(s, find);
    int new_s_len = s_len + find_count * (replace_by_len - find_len);
    
    char* new_s = xmalloc(new_s_len + 1);
    new_s[new_s_len] = '\0';
    
    int i_s = 0;
    int i_new_s = 0;
    while (i_new_s < new_s_len) {
        char* next_find = next_occurence(s + i_s, find);
        
        bool next_find_exists = true;
        if (next_find == NULL) {
            next_find_exists = false;
            next_find = s + s_len;  // end of s -> copy all of s
        }
        
        // copy until next_find
        int until_next_find = next_find - (s + i_s);
        
        copy(new_s + i_new_s, s + i_s, until_next_find);
        i_s += until_next_find;
        i_new_s += until_next_find;
        
        // put replace_by in new_s if there is a find in s
        if (next_find_exists) {
            copy(new_s + i_new_s, replace_by, replace_by_len);
            i_s += find_len;
            i_new_s += replace_by_len;
        }
    }
    
    return new_s;
}

void test_replace(){
    test_equal_s(replace("aabbccdd", "a", "d"), "ddbbccdd");
    test_equal_s(replace("aaabbccdd", "aa", "d"), "dabbccdd");
    test_equal_s(replace("aabbccdd", "aa", "d"), "dbbccdd");
    test_equal_s(replace("aabbccdd", "b", "olo"), "aaolooloccdd");
    test_equal_s(replace("aabbccdd", "c", ""), "aabbdd");
    test_equal_s(replace("hello, hello world", "hello", "bye"), "bye, bye world");
    test_equal_s(replace("aabbccdd", "dd", "eee"), "aabbcceee");
    test_equal_s(replace("for(int x = X; x < X * 3; x++){printiln(x);}", "X", "90"), "for(int x = 90; x < 90 * 3; x++){printiln(x);}");
}

int main(void){
    test_next_occurence();
    test_count();
    test_replace();
    
    return 0;
}
    