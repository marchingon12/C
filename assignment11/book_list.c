/*
Compile: make book_list_solution
Run: ./book_list_solution
make book_list_solution && ./book_list_solution
*/

#include "pointer_list.h"

typedef struct {
    String title;
    String authors;
    int year;
} Book;

// String, String, int -> Book*
// Create a book.
Book* new_book(String authors, String title, int year) {
    Book* b = xcalloc(1, sizeof(Book));
    b->authors = s_copy(authors);
    b->title = s_copy(title);
    b->year = year;
    return b;
}

// Book* -> Book*
// Create a copy of a book.
void* copy_book(void* x) {
    Book* b = (Book*)x;
    return new_book(b->authors, b->title, b->year);
}

// Book* -> String
// String representation of book in the form:
// authors: title, year.
String book_to_string(void* x) {
    Book* b = (Book*)x;
    String year = s_of_int(b->year);
    int n = s_length(b->authors) + 2 + s_length(b->title) + 2 + s_length(year) + 1 + 1;
    String s = xmalloc(n);
    snprintf(s, n, "%s: %s, %s.", b->authors, b->title, year);
    free(year);
    return s;
}

// Book* -> void
// Free the memory of a book.
void free_book(void* x) {
    Book* b = (Book*)x;
    free(b->title);
    free(b->authors);
    free(b);
}

// Book*, Book* -> bool
// Check if two books are equal.
bool books_equal(void* x, void* y) {
    Book* a = (Book*)x;
    Book* b = (Book*)y;
    if (a == b) return true;
    if (a == NULL || b == NULL) return false;
    return s_equals(a->authors, b->authors) && s_equals(a->title, b->title) && (a->year == b->year);
}

// Book*, Book* -> { -1, 0, 1 }
// Returns =0 if x and y are equal, <0 if x smaller than y, >0 otherwise.
int compare_books(void* x, void* y) {
    Book* a = (Book*)x;
    Book* b = (Book*)y;
    if (a == b) return 0;
    if (a == NULL) return -1;
    if (b == NULL) return 1;
    return a->year - b->year;
}

// Book* -> String
// Maps a book to its title.
void* book_title(void* element, int i, void* x) {
    Book* b = (Book*)element;
    return b->title;
}

// Book*, int, void* -> bool
// Check if book was published in or after 1990.
bool book_criterion(void* element, int i, void* x) {
    Book* b = (Book*)element;
    return b->year >= 1990;
}

// Book*, int, int* -> bool
// Check if book was published in or after the given year.
bool published_in_or_after(void* element, int i, void* x) {
    Book* b = (Book*) element;
    int* year = (int*) x;
    return b->year >= *year;
}

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// int*, Book*, int -> void
// Add year of book to state.
void sum_years(void* state, void* element, int index) {
    int* i = (int*)state;
    Book* b = (Book*)element;
    *i = *i + b->year;
}

int main(void) {
    report_memory_leaks(true);
    
    Book* b1 = new_book("Alice, Bob", "Cryptography for Dummies", 1987);
    Book* b2 = new_book("Doris Doe", "C-Programming in 3 hours", 1999);
    Book* b3 = new_book("Emma Erlang", "PostFix-Programming for Experts", 2018);
    Book* b4 = new_book("Carl Haskell", "New Methods in Programming", 1957);

    Node* list = new_node(b1, new_node(b2, new_node(b3, NULL)));
    println_list(list, book_to_string);

    Book* b4copy = copy_book(b4);
    list = append_list(list, b4);
    println_list(list, book_to_string);

    printsln("find:");
    Book* found_book = find_list(list, book_criterion, NULL);
    if (found_book != NULL) {
        String s = book_to_string(found_book);
        printsln(s);
        free(s);
    }
    int year = 1990;
    found_book = find_list(list, published_in_or_after, &year);
    if (found_book != NULL) {
        String s = book_to_string(found_book);
        printsln(s);
        free(s);
    }
    
    Node* list2 = copy_list(list, copy_book);
    free_list(list, free_book);

    Book* b5 = new_book("Wirth", "Algorithms and Data Structures", 2005);
    list2 = insert_list(list2, 1, b5);
    
    printbln(contains_list(list2, b5, NULL));
    printbln(contains_list(list2, b4copy, NULL));
    printbln(contains_list(list2, b4copy, books_equal));
    
    println_list(list2, book_to_string);

    printsln("map:");
    Node* titles = map_list(list2, book_title, NULL);
    println_list(titles, string_to_string);
    free_list(titles, NULL);
    
    printsln("filter:");
    Node* selected_books = filter_list(list2, book_criterion, NULL);
    println_list(selected_books, book_to_string);
    free_list(selected_books, NULL);
    
    printsln("filter_map:");
    Node* selected_books2 = filter_map_list(list2, book_criterion, book_title, NULL);
    println_list(selected_books2, string_to_string);
    free_list(selected_books2, NULL);

    printsln("reduce:");
    int years = 0;
    reduce_list(list2, sum_years, &years);
    printf("average year: %d\n", years / length_list(list2));
    
    Node* sorted_list = NULL;
    for (Node* n = list2; n != NULL; n = n->next) {
        sorted_list = insert_ordered(sorted_list, copy_book(n->value), compare_books);
    }
    println_list(sorted_list, book_to_string);
    
    sorted_list = reverse_list(sorted_list);
    println_list(sorted_list, book_to_string);
    
    free_list(sorted_list, free_book);
    free_list(list2, free_book);
    free_book(b4copy);
    
    return 0;
}
