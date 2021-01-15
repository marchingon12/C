/*
August Ho und Benjamin von Behren
Assignment 11
Aufgaben 1 und 2: Wunschbaum
*/

/*
Compile: make student_list
Run: ./student_list
make student_list && ./student_list
*/

#include "pointer_list.h"

// Data definition for a student
typedef struct {
	String name;
	String sex;
	int mat_nr;
	double debts;
} Student;


// String, String, int, double -> City*
// Create a student (constructor).
Student* new_student(String name, String sex, int mat_nr, double debts) {
    Student* s = xcalloc(1, sizeof(Student));
    s->name = s_copy(name);
    s->sex = s_copy(sex);
	s->mat_nr = mat_nr;
    s->debts = debts;
	return s;
}

// // // // a) // // // //
// Student* -> Student*
// Create a copy of student.
void* copy_student(void* x) {
    Student* s = (Student*)x;
    return new_student(s->name, s->sex, s->mat_nr, s->debts);
}

// Student* -> String
// String representation of student in the form:
// s is a hard working student who is in debt for debts €. The matriculations number is mat_nr and the students sex is sex
String student_to_string(void* x) {
    Student* s = (Student*)x;
    int n = s_length(s->name) + s_length(s->sex) + 150;
    String text = xmalloc(n);
    snprintf(text, n, "%s is a hard working student who is in debt for %.2f Euro. The matriculation number is %d and the students sex is %s", s->name, s->debts, s->mat_nr, s->sex);
    return text;
}

// // // // a) // // // //
// Student* -> void
// Releases memory of a student.
void free_student(void* x) {
    Student* s = (Student*)x;
    free(s->name);
    free(s->sex);
    free(s);
}

// // // // b) // // // //
// Student* -> bool
// Returns true if the amount of debts is above 20000.
bool poor_student(void* element, int i, void* x) {
    Student* s = (Student*)element;
	return s->debts > 20000;
}

// // // // c) // // // //
// Student* -> bool
// Returns true if the matriculation number is shorter than *x.
bool mat_nr_less_digits_than(void* element, int i, void* x) {
    Student* s = (Student*)element; // converts type of element to a pointer to Student and saves is as s
    int* a = (int*)x; // converts type of x to a pointer to int and saves is as a
	int counter = 0; // initializes counter as 0 to count how many digits the matriculation number has got
	for(int i = s->mat_nr; i > 0; i = i / 10 ) // int i is initialized as mat_nr and after each loop devided by 10 which is equal to erasing the last digit (exacly one digit). The loop ends after i is a one-digit-number and devided by 10, since this results in 0. Therefore the code is executed once for each digit.
		counter++; // increases counter by one
    return (counter < (*a)); // returns wether counter (length of matriculation number) is smaller than the value a points to
}

// // // // d) // // // //
// Student* -> String
// Maps a student to its name.
void* student_name(void* element, int i, void* x) {
	Student* s = (Student*)element;
    return s->name;
}

// // // // f) // // // //
// Student*, int, double* -> Student*
// Creates a new student with less debts. x is in range of [0, 1].
void* pay_debts(void* element, int i, void* x){
    double* factor = (double*)x;
    require("factor in range", *factor >= 0 && *factor <= 1);
    void* element_copy = copy_student(element);
    Student* s = (Student*)element_copy;
    
    s->debts = s->debts * (1 - *factor);

    return element_copy;
}

// // // // h) // // // //
// double*, Student*, int -> void
// Adds students debts to state.
void add_debts(void* state, void* element, int index) {
    double* a = (double*)state; // converts type of state to a pointer to double and saves is as a
    Student* s = (Student*)element; // converts type of element to a pointer to Student and saves is as s
    *a = *a + s->debts; // increases the value a points to by the debts of the given student
}

typedef struct {
	int n;
	double debts;
}Student_stats;

// Student_stats**, Student*, int -> void
// Computes the average debts for students.
void student_stats(void* state, void* element, int index) {
    Student_stats** s = (Student_stats**) state; // converts type of state to a pointer to a pointer to Student_stats and saves is as s
    Student* e = (Student*) element; // converts type of element to a pointer to Student and saves is as e
    if(*s == NULL){ // if s points to NULL there is no Student_stats -> create one:
		*s = xmalloc(sizeof(Student_stats)); // dynamically allocation for Student_stats
		(*s)->n = 0; // initialize n of Student_stats as 0
		(*s)->debts = 0.0; // initialize debts of Student_stats as 0
	}
	(*s)->n++; // increase n (number of students) by one
	(*s)->debts += e->debts; // increase the debts saved in Student_stats by the debts of the given student
}

// // // // i) // // // //
// Student*, Student* -> { <0, 0, >0 }
// Returns =0 if x and y are equal, <0 if x smaller than y, >0 otherwise.
int cmp_student_mat_nr(void* x, void* y) {
    Student* s1 = (Student*)x;
    Student* s2 = (Student*)y;
    
    if (s1 == s2) return true;  // same adress, can be NULL
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;
    
    return s1->mat_nr - s2->mat_nr;
}

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// String -> void
// Releases a string.
void free_string(void* x) {
    free(x);
}


/*  e)
Durch Zeigerlisten kann eine Grundlegende Listen-Struktur implementiert werden, die von verschiedenen speziellen Listenarten benutzt werden kann. Diese Funktionen müssen also nicht für jede Listenart neu implementiert werden.
Es ist zwar möglich eine Zeigerliste mit z.B. Zeigern auf Zahlen und auf Zeichketten zu erstellen, dies ist allerdings nicht sinnvoll, da man dann immer überprüfen muss um welchen Datentypen es sich handelt. Denn die Funktionen von pointer_list sind oft allgemein gehalten und erwarten ein void*, man müsste also z.B. immer durch "ausprobieren" mit "try" herausfinden welcher Datentyp vorliegt. Wenn man nur einen Datentypen hat, ist die Implementierung also deutlich einfacher.
*/

int main(void) {
    report_memory_leaks(true);
	
	Student* s1 = new_student("Mina", "not binary", 2090, 15000.00);
    Student* s2 = new_student("Mike", "male", 208080, 23607.56);
	Student* s3 = new_student("Anna", "female", 42, 406.26);
	Student* s4 = new_student("Jimmy", "male", 133, 8000.90);
	
    Node* list = new_node(s1, new_node(s2, new_node(s3, new_node(s4, NULL))));
    println_list(list, student_to_string);
    
    
    // // // // b) // // // //
    // find first poor student, use find_list
    // print result, if any
    printsln("\nfirst poor student:");
    Student* found_student = find_list(list, poor_student, NULL);
    if(found_student != NULL) {
        String found_student_text = student_to_string(found_student);
        printf("%s\n", found_student_text);
        free(found_student_text);
    }
    
    
    // // // // c) // // // //
    // find the first student with a matriculation number with a length less than max_digits, use find_list
    // print result, if any
    printsln("\nfirst student with mat_nr digit count less than max_digits:");
    int max_digits = 8;
    printf("Max digits: %d\n", max_digits);
    found_student = find_list(list, mat_nr_less_digits_than, &max_digits);
    if(found_student != NULL) {
        String found_student_text = student_to_string(found_student);
        printf("%s\n", found_student_text);
        free(found_student_text);
    }
    
    
    // map the list of students to a list of student names
    printsln("\nstudent names:");
    Node* names = map_list(list, student_name, NULL);
    println_list(names, string_to_string);
    free_list(names, NULL);
    
    
    // reduce the amount of debts for all students by 15%
    // new list, do not modify original list elements, use map_list
    printsln("\nreduce debts:");
    double factor = 0.15;
    
    // todo: implement
    Node* list2 = map_list(list, pay_debts, &factor);
    println_list(list2, student_to_string);
    free_list(list2, free_student);
    
    
    // // // // g) // // // //
    // find all students with matriculation numbers with less than 4 digits, use filter_list
    printsln("\nshort matriculation numbers:");
	int max_mat_nr_len = 4;
    Node* selected_students = filter_list(list, mat_nr_less_digits_than, &max_mat_nr_len);
    println_list(selected_students, student_to_string);
    free_list(selected_students, NULL);
    
    // produce a list of the names students with short matricultion numbers, use filter_map_list
    printsln("\nnames of students with short matriculation numbers:");
    Node* selected_students2 = filter_map_list(list, mat_nr_less_digits_than, student_name, &max_mat_nr_len);
    println_list(selected_students2, string_to_string);
    free_list(selected_students2, NULL);
    
    
    
    // compute the sum of the debts of all students, use reduce_list
    printsln("\ntotal debts:");
    double total_debts = 0;
    reduce_list(list, add_debts, &total_debts);
    printdln(total_debts);
    
	
    // calculate the average debts, use reduce_list
    Student_stats* stats = NULL;
    reduce_list(list, student_stats, &stats);
    if (stats != NULL) {
        printf("\nThe average debts are: %.2f\n", stats->debts/stats->n);
        free(stats);
    }
    
    
    // sort the students by their matriculation number, in increasing order
    // use insert_ordered, do not modify the original list, do not copy the students
    Node* sorted_list = NULL;
    for (Node* n = list; n != NULL; n = n->next) {
        sorted_list = insert_ordered(sorted_list, n->value, cmp_student_mat_nr);
    }
    printsln("\nsorted students:");
    if (sorted_list != NULL) {
        println_list(sorted_list, student_to_string);
        free_list(sorted_list, NULL);
    }
    
    
    // free all memory
    free_list(list, free_student);
    
    return 0;
}
