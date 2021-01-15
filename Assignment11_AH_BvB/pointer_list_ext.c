/*
Compile: make pointer_list_ext
Run: ./pointer_list_ext
make pointer_list_ext && ./pointer_list_ext
*/

#include "pointer_list.h"

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

// Create a list consisting of the first n nodes of list.
Node* take_list(Node* list, int n) {
	require("n must be larger than 0", n > 0);
	Node* temp = copy_list(list, NULL);
	int length = length_list(temp);
	for (int i = n; i < length; i++) {
		temp = remove_list(temp, n, NULL);
	}
	list = temp;
    return list; // todo; implement (a)
}

// Create a list consisting of nodes of list, except the first n.
Node* drop_list(Node* list, int n) {
	require("n must be larger than 0", n > 0);
	Node* temp = copy_list(list, NULL);
	//int length = length_list(temp);
	for (int i = 0; i < n; i++) {
		temp = remove_list(temp, 0, NULL);
	}
	list = temp;
    return list; // todo; implement (a)
}

// Take alternatingly from list1 and list2 until all data is collected in the result.
Node* interleave(Node* list1, Node* list2) {
	Node* result = NULL;
	Node* l1 = list1;
	Node* l2 = list2;

	while(l1 != NULL && l2 != NULL) {
		result = new_node(l1->value, result);
		l1 = l1->next;
		result = new_node(l2->value, result);
        l2 = l2->next;
	}
	while(l1 != NULL) {
		result = new_node(l1->value, result);
		l1 = l1->next;
	}
	while(l2 != NULL) {
		result = new_node(l2->value, result);
		l2 = l2->next;
	}
    return reverse_list(result); // todo; implement (c)
}

// typedef bool (*EqualFun)(void* element1, void* element2);

bool group_by_length(void* element1, void* element2) {
    String s1 = (String)element1;
    String s2 = (String)element2;
    return s_length(s1) == s_length(s2);
}

bool equal_int(void* element1, void* element2) {
    int* i1 = (int*)element1;
    int* i2 = (int*)element2;
    return *i1 == *i2;
}

/*
nicht komplett !!!
*/


// Group elements in list. Equivalent elements (for which equivalent is true) are put
// in the same group. The result is a list of groups. Each group is itself a list.
// Each group contains items that are equivalend.
Node* group_list(Node* list, EqualFun equivalent) {
    Node* l = copy_list(list, NULL);
    Node* group_list = NULL;

    // loop through l
    for (Node* node = l; node != NULL; node = node->next) {
        printf("current node: %s\n", node->value);
        if(group_list == NULL) {
            printf("group_list was NULL\n");
            Node* new_group = new_node(node->value, NULL);
            group_list = new_node(new_group, group_list);
            continue;   // go to next element in l
        }
        bool node_added_to_group = false;
        // loop through group_list
        for (Node* group = group_list; group != NULL; group = group->next) {
            printf("current group: ");
            println_list(group->value, string_to_string);
            printf("first node of group: %s\n", ((Node*)(group->value))->value);
            // check whether a group for the current element already exists
            if(equivalent(node->value, group->value)) {
                printf("node added to current group\n");
                //group->value = new_node(node->value, group->value); // add element to group
                ((Node*)(group->value))->value = new_node(node->value, ((Node*)(group->value))->value); // add element to group
                node_added_to_group = true;
                break;
            }
        }
        if(!node_added_to_group) { // no group for the current element found
            printf("!node_added_to_group\n");
            Node* new_group = new_node(node->value, NULL);
            group_list = new_node(new_group, group_list);
        }
    }

    return group_list;
}











void free_group(void* x) {
    Node* list = x;
    free_list(list, NULL);
}

int main(void) {
    report_memory_leaks(true);

    Node* list = new_node("a", new_node("bb", new_node("ccc", new_node("dd", new_node("e", NULL)))));
    println_list(list, string_to_string);

    prints("take_list: ");
    Node* list2 = take_list(list, 3);
    println_list(list2, string_to_string);

    prints("drop_list: ");
    Node* list3 = drop_list(list, 3);
    println_list(list3, string_to_string);

    prints("interleave: ");
    Node* list4 = interleave(list2, list3);
    println_list(list4, string_to_string);

    Node* groups = group_list(list, group_by_length);
    printf("%d groups:\n", length_list(groups));
    for (Node* n = groups; n != NULL; n = n->next) {
        if (n->value != NULL) {
           println_list(n->value, string_to_string);
        }
    }

   free_list(list, NULL);
   free_list(list2, NULL);
   free_list(list3, NULL);
   free_list(list4, NULL);
//    free_list(groups, free_group);

    return 0;
}
