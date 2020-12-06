/*
Compile: make memory_game
Run: ./memory_game 2 3
Compile & run: make memory_game && ./memory_game 2 3
*/

#include "base.h"
#include "clrscr.h"

// Represents the state of the memory game.
typedef struct {
    char *cards; // array of cards, each card is one character, row-wise
    int ncards; // number of cards in array
    int rows; // number of rows of the board
    int cols; // number of columns of the board
    int points; // number of points the player has earned
    int turns; // number of card turns the player has made
} Board;

static int uniform_z = 1234;

void seed_uniform(int seed) {
    uniform_z = seed;
}

// Uniformly distributed random numbers in the interval [0, limit).
int uniform(int limit) {
    require("positive", limit > 0);
    const int a = 16807;
    const int m = 2147483647;
    const int q = m / a;
    const int r = m % a;
    int z = uniform_z;
    long int gamma = a * (z % q) - r * (z / q);
    if (gamma > 0) z = gamma;
    else z = gamma + m;
    uniform_z = z;
    z %= limit;
    ensure("in range", 0 <= z && z < limit);
    return z;
}

// Shuffles the array.
void shuffle(char *a, int n) {
    require_not_null(a);
    require("not negative", n >= 0);
    // a) todo: explain
    for (int i = n - 1; i > 0; i--) {
        assert("in range", 1 <= i && i <= n - 1);
        int r = uniform(i + 1); // random number in interval [0,i]
        assert("in range", 0 <= r && r <= i);
        char c = a[r];
        a[r] = a[i];
        a[i] = c;
    }
}

// Initializes the board with shuffled cards. Empty places are represented as ' '.
// Open cards are represented as the respective character, e.g., 'A'.
// Backsides of cards are represented as negative characters, e.g., -'A'. 
// The cards are initially with their backside up (negative). 
// This function onnly initializes the elements of the cards array. It assumes 
// that cards points to an existing array and that ncards, rows, cols, points, 
// and turns have already been set.
void init_cards(Board *b) {
    require_not_null(b);
    // b) todo: implement
    // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
}

// Prints the board. Hidden cards are shown as '#'. The following shows an output example:
/*
  1 2 3 4           <-- four columns
1   # #             <-- row 1: 1st and 4th card taken, 2nd and 3rd card hidden
2 # D # #           <-- row 2: 2nd card open
3 # # A #           <-- row 3: 3rd card open
1 points, 2 turns   <-- the player got 1 point in 2 turns
*/
// The row and column numbers are printed to facilitate input.
void print_board(Board *b) {
    require_not_null(b);
    // c) todo: implement
    // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
}

// Returns the array index for row r and column c. Stops the program if r or c are not valid.
int array_index(Board *b, int r, int c) {
    require_not_null(b);
    require("valid position", 0 <= r && r < b->rows && 0 <= c && c < b->cols);
    // d) todo: implement
    // access to board elements: b->rows, b->cols
    return 0;
}

// Gets value at row r, column c. Stops the program if r or c are not valid.
char get(Board *b, int r, int c) {
    // e) todo: implement
    return '#';
}

// Sets value at row r, column c to x. Stops the program if r or c are not valid.
void set(Board *b, int r, int c, char x) {
    // e) todo: implement
}

// Turns over card in row r, column c. Stops the program if r or c are not valid.
void turn(Board *b, int r, int c) {
    // e) todo: implement
}

// Prints a prompt to wait and wait for return key.
void prompt(void) {
    printf("press <return> to continue\n");
    char line[8];
    get_line(line, 8);
}

// Gets user input of the form <row-digit><column-digit> to let the user specify
// the row and column of a card. Example: Input 13 specifies row 0, column 2.
// Because the function returns three values, row and col are pointers to int
// variables to be set by the function. The return value indicates whether the
// position is valid (true) or not (false), given the current board state.
bool input_coords(/*IN*/Board *b, /*OUT*/int *row, /*OUT*/int *col) {
    require_not_null(b);
    require_not_null(row);
    require_not_null(col);
    char line[8];
    get_line(line, 8); // read input from terminal into line array
    int r = line[0] - '1'; // input '1' corresponds to row 0, '2' --> 1, etc.
    int c = line[1] - '1';
    if (r < 0 || r >= b->rows || c < 0 || c >= b->cols || get(b, r, c) == ' ') {
        return false; // position not valid
    }
    *row = r;
    *col = c;
    return true; // position valid
}

// Restricts x to the interval [low, high].
int clamp(int x, int low, int high) {
    require("valid interval", low <= high);
    // f) todo: implement
    ensure("valid result", low <= x && x <= high);
    return x;
}

// Does a single move. It consists of turning over two cards. If they are equal, 
// they get removed from the board and a point for the collected pair is given 
// to the player. Otherwise, they are turned over again (backside up).
// The input format is: 12<return> to open a card in row 0, column 1.
void do_move(Board *b) { // g) todo: explain
    require_not_null(b);
    int r1, c1;
    while (!input_coords(b, &r1, &c1)) {
        printf("Illegal move.\n");
    }
    turn(b, r1, c1);
    b->turns++;
    clear_screen();
    print_board(b);

    int r2, c2;
    while (!input_coords(b, &r2, &c2) || (r1 == r2 && c1 == c2)) {
        printf("Illegal move.\n");
    }
    turn(b, r2, c2);
    b->turns++;
    clear_screen();
    print_board(b);

    prompt();
    char card1 = get(b, r1, c1);
    char card2 = get(b, r2, c2);
    assert("valid cards", card1 > 0 && card2 > 0 && card1 != ' ' && card2 != ' ');
    if (card1 == card2) {
        b->points++;
        set(b, r1, c1, ' ');
        set(b, r2, c2, ' ');
    } else {
        turn(b, r1, c1);
        turn(b, r2, c2);
    }
    clear_screen();
    print_board(b);
}

// Tests.
void tests(void) {
    seed_uniform(1234);

    test_equal_i(clamp(1, 2, 4), 2);
    test_equal_i(clamp(2, 2, 4), 2);
    test_equal_i(clamp(3, 2, 4), 3);
    test_equal_i(clamp(4, 2, 4), 4);
    test_equal_i(clamp(5, 2, 4), 4);
    
    // test with a 3x4 board (3 rows, 4 columns)
    char a[3*4];
    Board b = { a, 12, 3, 4, 10, 20 };
    init_cards(&b);
    
    print_board(&b); // ensure that output is equal to testsout1_want.txt

    test_equal_i(array_index(&b, 0, 0), 0);
    test_equal_i(array_index(&b, 0, 1), 1);
    test_equal_i(array_index(&b, 0, 2), 2);
    test_equal_i(array_index(&b, 1, 0), 4);
    test_equal_i(array_index(&b, 1, 1), 5);
    test_equal_i(array_index(&b, 2, 0), 8);
    test_equal_i(array_index(&b, 2, 1), 9);

    test_equal_i(get(&b, 0, 0), -68);
    test_equal_i(get(&b, 0, 1), -68);
    test_equal_i(get(&b, 0, 2), -69);
    test_equal_i(get(&b, 1, 0), -66);
    test_equal_i(get(&b, 1, 1), -66);
    test_equal_i(get(&b, 2, 0), -67);
    test_equal_i(get(&b, 2, 1), -69);

    turn(&b, 0, 0);
    turn(&b, 0, 2);
    turn(&b, 1, 0);
    turn(&b, 2, 1);

    test_equal_i(get(&b, 0, 0), 68);
    test_equal_i(get(&b, 0, 2), 69);
    test_equal_i(get(&b, 1, 0), 66);
    test_equal_i(get(&b, 2, 1), 69);

    print_board(&b); // ensure that output is equal to testsout2_want.txt or if you use Windows that output is equal to testsout2_want_WIN.txt

    set(&b, 0, 0, '1');
    set(&b, 0, 2, '2');
    set(&b, 1, 0, '3');
    set(&b, 2, 1, '4');
    
    test_equal_i(get(&b, 0, 0), '1');
    test_equal_i(get(&b, 0, 2), '2');
    test_equal_i(get(&b, 1, 0), '3');
    test_equal_i(get(&b, 2, 1), '4');

    print_board(&b); // ensure that output is equal to testsout3_want.txt
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
    if (argc != 3) {
        printf("Usage: memory_game <rows> <cols>\n");
        printf("Example: memory_game 2 3\n");
        exit(1);
    }
    
    tests(); 
    prompt();
    
    seed_uniform(time(NULL));
    Board b;
    b.rows = clamp(atoi(argv[1]), 2, 9); // atoi converts strings to integers (if possible)
    b.cols = clamp(atoi(argv[2]), 2, 9);
    printf("creating a memory board with %d rows and %d cols\n", b.rows, b.cols); 
    int pairs = b.rows * b.cols / 2;
    printf("%d pairs\n", pairs);
    b.ncards = 2 * pairs;
    printf("%d cards\n", b.ncards);
    char cards[b.ncards];
    b.cards = cards;
    b.points = 0;
    b.turns = 0;
    init_cards(&b);

    clear_screen();
    print_board(&b);
    while (2 * b.points < b.ncards) {
        do_move(&b);
    }
    
    return 0;
}

/*
Example sequence:
-----------------

  1 2 3
1 # # #
2 # # #
0 points, 0 turns
11

  1 2 3
1 B # #
2 # # #
0 points, 1 turns
12

  1 2 3
1 B C #
2 # # #
0 points, 2 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 2 turns
21

  1 2 3
1 # # #
2 A # #
0 points, 3 turns
22

  1 2 3
1 # # #
2 A C #
0 points, 4 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 4 turns
12

  1 2 3
1 # C #
2 # # #
0 points, 5 turns
22

  1 2 3
1 # C #
2 # C #
0 points, 6 turns
press <return> to continue

  1 2 3
1 #   #
2 #   #
1 points, 6 turns
23

  1 2 3
1 #   #
2 #   A
1 points, 7 turns
21

  1 2 3
1 #   #
2 A   A
1 points, 8 turns
press <return> to continue

  1 2 3
1 #   #
2      
2 points, 8 turns
11

  1 2 3
1 B   #
2      
2 points, 9 turns
13

  1 2 3
1 B   B
2      
2 points, 10 turns
press <return> to continue

  1 2 3
1      
2      
3 points, 10 turns
*/
