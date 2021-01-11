/*
August Ho und Benjamin von Behren

Compile: make wolf_goat_cabbage
Run: ./wolf_goat_cabbage
make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"

// Represents a single list node. The value is dynamically allocated. The node
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // todo: implement (Aufgabe 1)
	// (there will be memory leaks if this function is not yet implemented)
	if (list != NULL){
		if (list->next != NULL){
			Node* new_list = list->next;
			free_list(new_list);
		}
		free(list->value);
		free(list);
	}
}


bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
	prints("~ test_equal_list_tests:\n");
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // todo: implement (Aufgabe 1)
	int count = 0;	//node number starting from 0
	//check if both lists are NULL (empty lists)
	if (list1 == NULL && list2 == NULL){
		printf("Line %d: The lists are equal.\n", line);
		return true;
	//else check if both values from both lists are the same
	}else if (s_equals(list1->value, list2->value)){
		while(s_equals(list1->value, list2->value)) {
			if(list1 == NULL){
				printf("Line %d: The lists are equal.\n", line);
				return true;
			}
			count++;	//count how many nodes there are in the lists
			list1 = list1->next;	//set 1st listNode to next listNode
			list2 = list2->next;	//set 2nd listNode to next listNode
			//check if either listNode are empty or not
			if (list1 == NULL || list2 == NULL){
				//check if both listNode are identical
				if(list1 == list2) {
					printf("Line %d: The lists are equal.\n",line);
					return true;
				}else{
					break;
				}
			}
		}
	}
	//listNode from 1st list is empty, length of 1st list shorter
	if (list1 == NULL){
		printf("Line %d: list1 is shorter than list2\n",line);
	//listNode from 2nd list is empty, length of 2nd list shorter
	}else if (list2 == NULL){
		printf("Line %d: list1 is longer than list2\n",line);
	//listNode from 1st and 2nd list is empty, both list length same, values different
	}else{
		printf("Line %d: The values at node %d differ: %s <-> %s.\n", line, count, list1->value, list2->value);
	}
    return false;
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    // todo: implement (Aufgabe 1)
	prints("\n~ length_list_tests:\n");

	Node* list1 = NULL;
	test_equal_i(length_list(list1), 0);

	list1 = new_node("hello", NULL);
	test_equal_i(length_list(list1), 1);
	free_list(list1);

	list1 = new_node("one", new_node("two", new_node("three", NULL)));
	test_equal_i(length_list(list1), 3);
	free_list(list1);
    // todo: at least 3 checks, with test_equal_i(actual, expected);
}

// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    // todo: implement (Aufgabe 1)
	prints("\n~ index_list_tests:\n");
	Node* list1 = NULL;
	test_equal_i(index_list(list1, "oi"), -1);
	free_list(list1);

	list1 = new_node("hello", NULL);
	test_equal_i(index_list(list1, "hello"), 0);
	free_list(list1);

	list1 = new_node("one", new_node("two", new_node("three", NULL)));
	test_equal_i(index_list(list1,"zero"), -1);
    test_equal_i(index_list(list1,"two"), 1);
	test_equal_i(index_list(list1,"three"), 2);
    free_list(list1);
    // todo: at least 3 checks, with test_equal_i(actual, expected);
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    // todo: implement (Aufgabe 1)
	require("s is not NULL", s != NULL);
	int count = 0;
	while(list != NULL){
		if(s_equals(list->value, s)){
			return count;
		}
		count++;
		list = list->next;
	}
    return -1;
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_lists(__LINE__, actual, expected);
	prints("\n~ remove_list_tests:\n");
	//empty list
	Node* list1 = NULL;
	list1 = remove_list(list1, 1);
	test_equal_i(length_list(list1), 0);

	// 1--->2--->3--->4--->NULL
	list1 = new_node("one", new_node("two", new_node("three", new_node( "four",NULL))));
	//list1 = remove_list(list1, -1);			//remove nonexistent node
	//test_equal_i(length_list(list1), 4);	//no change

	// 1--->2--->3--->4--->NULL
	list1 = remove_list(list1, 0);			//remove 1st node
	// 2--->3--->4--->NULL
	test_equal_i(contains_list(list1, "one"), 0);	//check if node containing "one" is removed
	list1 = remove_list(list1, 2);
	// 2--->3--->NULL
	test_equal_i(contains_list(list1, "four"), 0);	//check if node containing "four" is removed
	free_list(list1);

	Node* list2 = NULL;
	list2 = new_node("one", new_node("two", new_node("three", new_node( "four",NULL))));
	list2 = remove_list(list2, 1);
	test_equal_i(length_list(list2), 3);
	free_list(list2);
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement (Aufgabe 1)
	require("valid index", index >= 0);
	//return listNode if reached end of list or index smaller than 0 or listNode empty
	if (index < 0 || list == NULL || index >= length_list(list)) return list;
	ensure_code(int oldLength = length_list(list));

	Node* list_last = list;
	//set list_last as last node
	while(list_last != NULL) {
		list_last = list_last->next;
	}

	//from first node
	if (index == 0) {
		Node* del = list;
		free(list->value);
		list = del->next;
		free(del);
		if (list == NULL) {
			list_last = NULL;
		}
		return list;
	}

	Node* node = list;
	int k = 1;
	while (node != NULL && k < index) {
		node = node->next;
		k++;
	}

	if (node != NULL && node->next != NULL) {
		Node* del = node->next;
		free(del->value);
		node->next = del->next;
		free(del);
		if (node->next == NULL) {
			list_last = node;
		}
	}
	ensure("correct list length", oldLength == length_list(list) + 1);
    return list;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank.
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    Puzzle p = {new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT};
    return p;
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
	print_list(p->left);
	if (p->position == LEFT){
		print_list(p->boat);
		printf("       ");
	}else if (p->position == RIGHT){
		printf("       ");
		print_list(p->boat);
	}
	print_list(p->right);
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
	free_list(p->left);
	free_list(p->right);
	free_list(p->boat);
	exit(0);
}

void evaluate_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
	/* Condition 1:
		If
		RIGHT contains Wolf, Ziege, Kohl
		LEFT is empty = NULL
		Player wins and finish_puzzle.
	*/
	if (contains_list(p->right,"Wolf") && contains_list(p->right,"Ziege") && contains_list(p->right,"Kohl") && (p->left == NULL)){
		print_puzzle(p);
		printf("\nGlückwünsch! Flussueberquerungsraetsel geloest!\n");
		finish_puzzle(p);
	}

	/* Condition 2:
		If
		LEFT/RIGHT contains Wolf, Ziege
		RIGHT/LEFT contains Kohl
		Player loses, print "Der Wolf frisst die Ziege."
		finish_puzzle, Quit game
	*/
	else if ((contains_list(p->left,"Wolf") && contains_list(p->left,"Ziege") && !contains_list(p->left,"Kohl") && p->position == RIGHT) || (contains_list(p->right,"Wolf") && contains_list(p->right,"Ziege") && !contains_list(p->right,"Kohl") && p->position == LEFT)){
		print_puzzle(p);
		prints("\nDer Wolf frisst die Ziege.");
		finish_puzzle(p);
	}

	/* Condition 3:
		If
		LEFT/RIGHT contains Ziege, Kohl
		RIGHT/LEFT contains Wolf
		Player loses, print "Die Ziege frisst den Kohl."
		finish_puzzle, Quit game
	*/
	else if ((contains_list(p->left,"Ziege") && contains_list(p->left,"Kohl") && !contains_list(p->left,"Wolf") && p->position == RIGHT) || (contains_list(p->right,"Ziege") && contains_list(p->right,"Kohl") && !contains_list(p->right,"Wolf") && p->position == LEFT)){
		print_puzzle(p);
		prints("\nDie Ziege frisst den Kohl.");
		finish_puzzle(p);
	}

	/* Condition 4:
		Do nothing if none of the conditions above are fufilled.
	*/
}

void play_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    print_puzzle(p);
	println();
	String s = s_input(100);

	if(s_equals(s, "q")){
		prints("Quit game");
		free(s);
		finish_puzzle(p);

	}else if(s_equals(s, "r")){
		p->position = RIGHT;

	}else if(s_equals(s, "l")){
		p->position = LEFT;

	}else if (p->position == LEFT && p->boat == NULL){
		int i = index_list(p->left, s);
		//if Wolf/Ziege/Kohl is present in left list,
		if(i != -1){
			//assign new node with Wolf/Ziege/Kohl -> NULL
			p->boat = new_node(s, NULL);
			// if next of left list is not pointing to NULL (end of list)
			if(p->left->next != NULL){
				if(i == 0){
					//p->left is first node of left list
					//printf("%s\n", p->left->value);
					Node* a = p->left;
					free(p->left->value);
					//a->next is rest of list after node 1
					p->left = a->next;
					free(a);
				}else{
					remove_list(p->left, i);
				}
			//if next of left is NULL then free and empty left list
			}else{
				free_list(p->left);
				p->left = NULL;
			}
		}else{
			printsln("^");
			printsln("\nFalsche Eingabe: ");
			printsln("# <q> - Quit game");
			printsln("# <l> - Move boat left");
			printsln("# <r> - Move boat right");
			printsln("# <Wolf> - Load/unload the Wolf on/off the boat");
			printsln("# <Ziege> - Load/unload the Ziege on/off the boat");
			printsln("# <Kohl> - Load/unload the Kohl on/off the boat");
			println();
			printsln("Versuch nochmal.\n");
		}
		//else do nothing and print_puzzle again

	}else if (p->position == RIGHT && p->boat == NULL){
		int i = index_list(p->right, s);
		if(i != -1){
			p->boat = new_node(s, NULL);
			if(p->right->next != NULL){
				if(i == 0){
					Node* a = p->right;
					free(p->right->value);
					p->right = a->next;
					free(a);
				}else {
					remove_list(p->right, i);
				}
			}else{
				free_list(p->right);
				p->right = NULL;
			}
		}else{
			printsln("^");
			printsln("\nFalsche Eingabe: ");
			printsln("# <q> - Quit game");
			printsln("# <l> - Move boat left");
			printsln("# <r> - Move boat right");
			printsln("# <Wolf> - Load/unload the Wolf on/off the boat");
			printsln("# <Ziege> - Load/unload the Ziege on/off the boat");
			printsln("# <Kohl> - Load/unload the Kohl on/off the boat");
			println();
			printsln("Versuch nochmal.\n");
		}

	//free the boat after assigning animal
	}else if(s_equals(p->boat->value, s)){
		if(p->position == LEFT){
			p->left = new_node(s, p->left);
		}else{
			p->right = new_node(s, p->right);
		}
		free_list(p->boat);
		p->boat = NULL;

	// }else if(s_equals(s, "Wolf")){
	// 	//if LEFT has Wolf and boat position = LEFT and Boat is empty = NULL then
	// 	if (contains_list(p->left,"Wolf") && p->position == LEFT && p->boat == NULL) {
	// 		p->boat = new_node("Wolf", NULL);
	// 		remove_list(p->left, index_list(p->left, "Wolf"));
	// 	//if boat position = RIGHT and Boat contains Wolf, then
	// 	}else if (p->position == RIGHT && contains_list(p->boat,"Wolf")){
	// 		p->right = new_node("Wolf", p->right);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	//if RIGHT has Wolf and boat position = RIGHT and Boat is empty = NULL then
	// 	}else if (contains_list(p->right,"Wolf") && p->position == RIGHT && p->boat == NULL){
	//		p->boat = new_node("Wolf", NULL);
	// 		remove_list(p->right, index_list(p->right, "Wolf"));
	// 	//if boat position = LEFT and Boat contains Wolf, then
	// 	}else if (p->position == LEFT && contains_list(p->boat,"Wolf")){
	// 		p->left = new_node("Wolf", p->left);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	}
	//
	// }else if(s_equals(s, "Ziege")){
	// 	//if LEFT has Ziege and boat position = LEFT and Boat is empty = NULL then
	// 	if (contains_list(p->left,"Ziege") && p->position == LEFT && p->boat == NULL) {
	// 		remove_list(p->left, index_list(p->left, "Ziege"));
	// 		p->boat = new_node("Ziege", NULL);
	// 	//if boat position = RIGHT and Boat contains Ziege, then
	// 	}else if (p->position == RIGHT && contains_list(p->boat,"Ziege")){
	// 		remove_list(p->boat, 0);
	// 		p->right = new_node("Ziege", NULL);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	//if RIGHT has Ziege and boat position = RIGHT and Boat is empty = NULL then
	// 	}else if (contains_list(p->right,"Ziege") && p->position == RIGHT && p->boat == NULL){
	// 		remove_list(p->right, index_list(p->right, "Ziege"));
	// 		p->boat = new_node("Ziege", NULL);
	// 	//if boat position = LEFT and Boat contains Ziege, then
	// 	}else if (p->position == LEFT && contains_list(p->boat,"Ziege")){
	// 		remove_list(p->boat, 0);
	// 		p->left = new_node("Ziege", NULL);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	}
	//
	// }else if(s_equals(s, "Kohl")){
	// 	//if LEFT has Kohl and boat position = LEFT and Boat is empty = NULL then
	// 	if (contains_list(p->left,"Kohl") && p->position == LEFT && p->boat == NULL) {
	// 		remove_list(p->left, index_list(p->left, "Kohl"));
	// 		p->boat = new_node("Kohl", NULL);
	// 	//if boat position = RIGHT and Boat contains Kohl, then
	// 	}else if (p->position == RIGHT && contains_list(p->boat,"Kohl")){
	// 		remove_list(p->boat, 0);
	// 		p->right = new_node("Kohl", NULL);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	//if RIGHT has Kohl and boat position = RIGHT and Boat is empty = NULL then
	// 	}else if (contains_list(p->right,"Kohl") && p->position == RIGHT && p->boat == NULL){
	// 		remove_list(p->right, index_list(p->right, "Kohl"));
	// 		p->boat = new_node("Kohl", NULL);
	// 	//if boat position = LEFT and Boat contains Kohl, then
	// 	}else if (p->position == LEFT && contains_list(p->boat,"Kohl")){
	// 		remove_list(p->boat, 0);
	// 		p->left = new_node("Kohl", NULL);
	// 		free_list(p->boat);
	// 		p->boat = NULL;
	// 	}
	}
	free(s);
	evaluate_puzzle(p);
	play_puzzle(p);
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    report_memory_leaks(true);

	prints("Aufgabe 1: Operationen auf Listen\n\n");
    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();

	prints("\nAufgabe 2: Der Wolf, die Ziege und der Kohlkopf\n\n");
    Puzzle p = make_puzzle();
    play_puzzle(&p);
    return 0;
}
