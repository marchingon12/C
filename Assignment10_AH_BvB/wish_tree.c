/*
August Ho und Benjamin von Behren
Assignment 10
Aufgabe 4: Wunschbaum
*/

/*
    make wish_tree
    ./wish_tree
    make wish_tree && ./wish_tree
*/

#include "base.h"


typedef struct Element Element;

void free_element(Element* element);


typedef struct Node{
    struct Node* next;
    char* value;
}Node;

/*
    Returns a pointer to a dynamically allocated node.
*/
Node* new_node(char* value, Node* next){
    Node* node = xmalloc(sizeof(Node));
    node->next = next;
    node->value = s_copy(value);
    return node;
}

/* 
    Releases the memory used by node. 
*/
Node* free_node(Node* node){
    Node* next = node->next;
    free(node->value);
    free(node);
    return next;
}
/*  g)
    Releases the memory used by a list of nodes. 
*/
void free_node_list(Node* list){
    while(list != NULL) {
        list = free_node(list);
    }
}

/*
    Returns the length of a list of nodes.
*/
int length(Node* node){
    int count = 0;
    while(node != NULL){
        count++;
        node = node->next;
    }
    return count;
}

/*
    Returns true if the list of nodes contains find.
*/
bool contains(Node* node, char* find){
    while(node != NULL){
        if(strcmp(node->value, find) == 0){
            return true;
        }
        node = node->next;
    }
    return false;
}


/* 
    A TreeNode has a left and right successor of type TreeNode. A successor TreeNode is a TreeNode or NULL
        
            TreeNode root
           /          \
          /            \
    TreeNode left      TreeNode right
    /       \       /           \
   ...      ...    ...          ...
*/

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    struct Element* element;
}TreeNode;

/*
    Returns a pointer to a dynamically allocated tree_node.
*/
TreeNode* new_tree_node(Element* element){
    TreeNode* bnode = xmalloc(sizeof(TreeNode));
    bnode->left = NULL;
    bnode->right = NULL;
    bnode->element = element;
    return bnode;
}

void free_element(Element* element);
/*  g)
    Releases the memory used by a tree and also frees the included element.
*/
void free_tree(TreeNode* tree){
    if(tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free_element(tree->element);
        free(tree);
    }
}


/*  b)
    Element of the binary tree which contains the wish, the amount of children who have the wish and the amount of them.
*/
struct Element{
    char* wish;
    int count;
    Node* children;
};

/*  b)
    Returns a pointer to a dynamically allocated element of the given wish and child.
*/
Element* new_element(char* wish, char* child){
    Element* e = xmalloc(sizeof(Element));
    e->wish = s_copy(wish);
    e->count = 1;
    e->children = new_node(child, NULL);
    return e;
}

/*  g)
    Releases the memory used by the element.
*/
void free_element(Element* element){
    free(element->wish);
    free_node_list(element->children);
    free(element);
}


/*  c)
    Appends a value a list of nodes.
*/
void append(Node* children, char* value) {
    if(children == NULL) {
        children = new_node(value, NULL);
    } else if(children->next == NULL) {
        children->next = new_node(value, NULL);
    } else {
        append(children->next, value);
    }
}
/*  c)
    Adds the given wish to the tree.
*/
TreeNode* add_wish(TreeNode* tree, char* wish, char* child){
    if (tree == NULL) {
        return new_tree_node(new_element(wish, child));
    } else {
        int wishes_compare = strcmp(wish, tree->element->wish);
        if (wishes_compare > 0) {   // wish > tree->element->wish
            tree->right = add_wish(tree->right, wish, child);
        } else if (wishes_compare < 0) {    // wish < tree->element->wish
            tree->left = add_wish(tree->left, wish, child);
        } else {    // same wish (wish found)
            tree->element->count++;
            append(tree->element->children, child);
        }
        return tree;
    }
}

typedef struct ElementNode{
    struct ElementNode* next;
    Element* element;
}ElementNode;

ElementNode* new_element_node(Element* element, ElementNode* next){
    ElementNode* en = xmalloc(sizeof(ElementNode));
    en->next = next;
    en->element = element;
    return en;
}


/*  g)
    Releases the memory used by ElementNode. 
*/
 ElementNode* free_element_node(ElementNode* en, bool bool_free_element){
    ElementNode* next = en->next;
    if (bool_free_element) {
        free_element(en->element);
    }
    free(en);
    return next;
}
/*  g)
    Releases the memory used by the list of elements.
*/
void free_element_list(ElementNode* list, bool bool_free_element){
    while(list != NULL) {
        list = free_element_node(list, bool_free_element);
    }
}


void print_element_list(ElementNode* list, int n){
    printf("%55s\t%6s\n", "Wunsch", "Anzahl");
    while(n > 0 && list != NULL){
        printf("%55s\t%6d\n", list->element->wish, list->element->count); 
        n--;
        list = list->next;
    }
}


/*  e)
    Inserts the element to the list of elements (ordered by count).
*/
ElementNode* insert_element(ElementNode* list, Element* element) {
    if (list == NULL) {
        return new_element_node(element, NULL);
    } else {
        if (list->element->count < element->count) {
            list = new_element_node(element, list);
        } else {
            list->next = insert_element(list->next, element);
        }
        return list;
    }
}
/*  e)
    Returns a pointer to a list of the elements in the tree in ascending order of count.
*/
ElementNode* insert_ordered_by_count(ElementNode* result, TreeNode* tree){
    if (tree == NULL) {
        return result;
    } else {
        result = insert_element(result, tree->element);
        
        result = insert_ordered_by_count(result, tree->right);
        result = insert_ordered_by_count(result, tree->left);
        
        return result;
    }
}


/*  d)
    Prints the children of the given list.
*/
void print_list(Node* list) {
    if (list != NULL) {
        printf("%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %s", n->value);
        }
    }
}

/*  d)
    Prints the tree as a list (in alphabetical order).
*/
void print_tree_as_list(TreeNode* tree){
    // print left sub tree, print current node, print right sub tree
    if (tree != NULL) {
        print_tree_as_list(tree->left);
        
        Element* current_element = tree->element;
        printf("%55s\t%6d\t", current_element->wish, current_element->count);
        print_list(current_element->children);
        printf("\n");
        
        print_tree_as_list(tree->right);
    }
}
/*  d)
    Prints the tree as a list (in alphabetical order) with header.
*/
void print_tree_as_list_with_header(TreeNode* tree){
    printf("%55s\t%6s\t%s\n", "Wunsch", "Anzahl", "Kinder");
    print_tree_as_list(tree);
}


// Skips the rest of the current line.
char* skip_line(char* s) {
    while (*s != '\n' && *s != '\0') s++;
    if (*s == '\n') s++;
    return s;
}

// Skips the current token.
char* skip_token(char* s) {
    while (*s != ',' && *s != '\n' && *s != '\0') s++;
    return s;
}

// Skips spaces.
char* skip_spaces_and_commas(char* s) {
    while (*s == ' ' || *s == ',') s++;
    return s;
}


// Create a new token from s (inclusive) to t (exclusive).
char* new_token(char* s, char* t) {
    char* token = xmalloc(t - s + 1);
    int i = 0;
    while (s < t) {
        token[i] = *s;
        i++;
        s++;
    }
    token[i]= '\0';
    return token;
}

// Returns a new token by first skipping spaces and commas and then reading the token. 
// Sets *s to the first character after the token.
char* next_token(/*INOUT*/char** s) {
    *s = skip_spaces_and_commas(*s);
    char* t = skip_token(*s);
    char* token = new_token(*s, t);
    *s = t; // set *s to the character after the token
    return token;
}


/* 
    This function reads in one line of the wish text file and adds the wishes of a child to tree.
*/
TreeNode* read_wish_list(char** s, TreeNode* tree){
    char* child = next_token(s);
    
    while(**s != '\0' && **s != '\n'){
        char* wish = next_token(s);
        *s = skip_spaces_and_commas(*s);
        tree = add_wish(tree, wish, child); 
        free(wish);
    }
    
    free(child);
    return tree;
}

/*  
    This function reads the whole file and uses the read_wish_list function to parse a single line.
*/
TreeNode* read_wishes(char* filename, TreeNode* tree){
    char* file = s_read_file(filename);
    char* s = file;
    s = skip_line(s);
    while(*s != '\0'){
        tree = read_wish_list(&s, tree);
        s = skip_line(s);
    }
    free(file);
    return tree;
}


/*  f)
    Proofs wether each child gets at least one gift.
*/
void are_all_children_happy(ElementNode* sorted_by_count, int number_of_children, int number_of_gifts) {
    Node* happy_children = NULL;
    // loop through the first number_of_gifts elements of sorted_by_count
    ElementNode* en = sorted_by_count;
    for (int i = 0; i < number_of_gifts; i++) {
        // loop through children
        for (Node* n = en->element->children; n != NULL; n = n->next) {
            // add child if it is not already in the list
            if (!contains(happy_children, n->value)) {
                happy_children = new_node(n->value, happy_children);
            }
        }
        
        en = en->next;
    }
    
    int number_of_sad_children = number_of_children - length(happy_children);
    if (number_of_sad_children == 0) {
        printf("All children get at least one gift.\n");
    } else {
        printf("Not all children get a gift, only the following:\n");
        print_list(happy_children);
    }
    
    free_node_list(happy_children);
}


int main(int argc, char** argv){
    report_memory_leaks(true);
    
    printf("\n");
    
    TreeNode* tree = read_wishes("wishes.txt", NULL);
    
    //print_tree_as_list(tree);
    print_tree_as_list_with_header(tree);
    
    printf("\n");
    
    ElementNode* sorted_by_count = insert_ordered_by_count(NULL, tree);
    
    print_element_list(sorted_by_count, 11);
    
    
    
    
    printf("\n");
    
    // f)
    const int number_of_children = 29;
    const int number_of_gifts = 11;
    are_all_children_happy(sorted_by_count, number_of_children, number_of_gifts);
    
    printf("\n");
    
    //g)
    free_tree(tree);
    free_element_list(sorted_by_count, false);
    
    return 0;
}