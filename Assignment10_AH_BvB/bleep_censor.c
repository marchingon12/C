/*
August Ho und Benjamin von Behren
Assignment 10
Aufgabe 3: Bleep Censor
*/

/*
    make bleep_censor
    ./bleep_censor
    make bleep_censor && ./bleep_censor
*/

#include "base.h"


typedef struct Token{
    char* start;
    char* end;
}Token;

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    Token* token;
}TreeNode;

Token* new_token(char* start, char* end){
    Token* t = xmalloc(sizeof(Token));
    t->start = start;
    t->end = end;
    return t;
}

/*  a)
    Prints the token. When censored is true, the first char followed by '*' is printed.
*/
void print_token(Token* t, bool censored) {
    int len_token = t->end - t->start;
    if (censored) {
        printf("%c", *(t->start));
        for (int i = 1; i < len_token; i++) {
            printf("*");
        }
    } else {
        for (int i = 0; i < len_token; i++) {
            printf("%c", *(t->start+i));
        }
    }
}

void print_tokenln(Token* t, bool censored) {
    print_token(t, censored);
    printc('\n');
}

TreeNode* new_tree_node(TreeNode* left, Token* token, TreeNode* right){
    TreeNode* tree_node = xmalloc(sizeof(TreeNode));
    tree_node->token = token;
    tree_node->left = left;
    tree_node->right = right;
    return tree_node;
}


/*  g)
    Releases the memory used by a tree and also frees the included element.
*/
void free_tree(TreeNode* tree){
    if(tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree->token);
        free(tree);
    }
}


TreeNode* new_leaf(Token* token){
    return new_tree_node(NULL, token, NULL);
}

void print_tree(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    print_tree(tree->left);
    printc(' ');
    print_token(tree->token, false);
    printc(' ');
    print_tree(tree->right);
}


/*  b)
    Returns the lowercase of the character.
*/
char lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}
/*  b)
    Compares the lexicographical order of the given token. Returns
    0  if t1 is equal to t2
    -1 if t1 is before of t2
    1  if t1 is after of t2
*/
int compare_token(Token* t1, Token* t2){
    require("valid t1", t1 != NULL && t1->start != NULL && t1->end != NULL);
    require("valid t2", t2 != NULL && t2->start != NULL && t2->end != NULL);

    int len_t1 = t1->end - t1->start;
    int len_t2 = t2->end - t2->start;
    int len = (len_t1 < len_t2) ? len_t1 : len_t2;  // minimum of both

    for (int i = 0; i < len; i++) {
        char c1 = lowercase(*(t1->start+i));
        char c2 = lowercase(*(t2->start+i));
        if (c1 < c2) {
            return -1;
        } else if (c1 > c2) {
            return 1;
        }
    }

    // t1 and t2 are the same for the first len characters but one might be longer
    if (len_t1 < len_t2) {
        return -1;
    } else if (len_t1 > len_t2) {
        return 1;
    } else {
        return 0;
    }
}

void test_token_compare(){
    char* s = "hallo huhu hall HALLO";

    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo, false);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu, true);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall, false);
    Token hallo_2 = {s + 16, s + 21};
    //print_tokenln(&hallo_2, true);

    test_equal_i(compare_token(&hallo, &hallo), 0);
    test_equal_i(compare_token(&huhu, &huhu), 0);
    test_equal_i(compare_token(&huhu, &hallo), 1);
    test_equal_i(compare_token(&hallo, &huhu), -1);
    test_equal_i(compare_token(&hall, &hallo), -1);
    test_equal_i(compare_token(&hallo, &hall), 1);
    test_equal_i(compare_token(&hallo, &hallo_2), 0);
    test_equal_i(compare_token(&hallo_2, &hallo), 0);
}

bool contains(TreeNode* tree, Token* token){
    if(tree == NULL){
        return false;
    }

    int cmp_result = compare_token(token, tree->token);
    if(cmp_result == 0){
        return true;
    }
    else if(cmp_result < 0){
        return contains(tree->left, token);
    }else{
        return contains(tree->right, token);
    }
}


/*  c)
    Inserts the token into the tree at the correct position (ordered lexicographically).
    Returns wether token was inserted into the tree or not.
*/
bool insert_in_tree(TreeNode** tree, Token* token){
    if (*tree == NULL) {
        *tree = new_leaf(token);
        return true;
    } else {
        int cmp_result = compare_token(token, (*tree)->token);
        if(cmp_result < 0){
            insert_in_tree(&((*tree)->left), token);
            return true;
        }
        else if (cmp_result > 0) {
            insert_in_tree(&((*tree)->right), token);
            return true;
        } else {    // token is already in tree
            // since the token is not inserted into the tree it cannot be freed by free_tree
            return false;
        }
    }
}

void test_insert_token(){
    char* s = "hallo huhu hall HALLO";

    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall);

    TreeNode* tree = NULL;

    insert_in_tree(&tree, &hallo);

    test_equal_i(compare_token(tree->token, &hallo), 0);

    insert_in_tree(&tree, &hallo);
    test_equal_i(compare_token(tree->token, &hallo), 0);

    insert_in_tree(&tree, &hall);
    test_equal_i(compare_token(tree->left->token, &hall), 0);

    insert_in_tree(&tree, &huhu);
    test_equal_i(compare_token(tree->right->token, &huhu), 0);


    free(tree->left);
    free(tree->right);
    free(tree);
}

/*  d)
    Returns the length of the first token in the string.
*/
int token_length(char* s) {
    int i = 0;
    while(*(s+i) != ' ' && *(s+i) != '\n' && *(s+i) != '\t' && *(s+i) != '\0') {
        i++;
    }
    return i;
}
/*  d)
    Creates a tree from the tokens in bleep_words.
*/
TreeNode* create_bleep_tree(char* bleep_words){
    require_not_null(bleep_words);
    TreeNode* tree = NULL;
    //Token* token = NULL;
    // loop throug bleep_words
    for (char* c = bleep_words; *c != '\0'; c++) {
        if (*c == ' ' || *c == '\n' || *c == '\t') {
            continue;
        } else {
            int token_len = token_length(c);
            //token = new_token(c, c + token_len);
            Token* token = new_token(c, c + token_len);
            bool inserted = insert_in_tree(&tree, token);

            if (!inserted) {
                free(token);
            }

            //free(token);



            c += token_len - 1; // - 1 due to c++ in for loop
        }
    }
    return tree;
}


void test_create_bleep_tree(){
    //char* s = "hallo huhu hall HALLO";
    char* s = "hallo huhu hall HALLO";

    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall);

    TreeNode* tree = create_bleep_tree(s);

    //printf("test tree:\n");
    //print_tree(tree);
    //printf("\n");

    test_equal_i(compare_token(tree->token, &hallo), 0);
    test_equal_i(compare_token(tree->left->token, &hall), 0);
    test_equal_i(compare_token(tree->right->token, &huhu), 0);

    free_tree(tree);
}


/*  e)
    Censors the words from the tree in the string.
*/
void bleep_censor(char* text, TreeNode* bleep_tree) {
    // loop through text
    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == ' ') {
            i++;
        } else {
            int token_len = token_length(&text[i]);
            Token* token = new_token(&text[i], &text[i+token_len]);

            // bleep tokens if in bleep_tree
            if (contains(bleep_tree, token)) {
                for (int j = 1; j < token_len; j++) {
                    text[i+j] = '*';
                }
            }

            free(token);
            i += token_len;
        }
    }
}

int main(void){
    report_memory_leaks(true);
    test_token_compare();
    test_insert_token();
    test_create_bleep_tree();

    char* bleep_words = "schwein affe dumm bloed bloedmann idiot";
    TreeNode* tree = create_bleep_tree(bleep_words);

    printf("tree:\n");
    print_tree(tree);
    printc('\n');


    char buffer[256];
    printf("Input:\n>");
    get_line(buffer, 256);
    printf("Original String: %s\n", buffer);
    bleep_censor(buffer, tree);
    printf("Bleeped String:  %s\n", buffer);


    free_tree(tree);
    return 0;
}
