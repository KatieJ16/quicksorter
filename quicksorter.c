/* Quicksort.
 * Takes input from the command-line, 
 * and sorts the numbers using quicksort and a linked list.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"
#include "memcheck.h"

/* Sorts the list using quicksort.
 * This is a recursive function.
 * Arguement is a pointer to the first node of a linked list.
 * Return value is a pointer to the sorter linked list. 
 */

node* quicksort(node* list) {
    int first;
    node* larger = NULL;
    node* smaller = NULL;
    node* equal = NULL;

    /* Return when there are 0 nodes. */
    if (list == NULL) {
        return list;
    }
    if(list->next == NULL) {
        return list;
    }


    /* Copy of first node */
    first = list->data;
    
    /* Break into two linked lists. 
     * One for elements that are >= and one for less than. */
    while(list != NULL) {
        if(list->data == first) {
            equal = create_node(list->data, equal);
        } else if(list->data > first) {
            larger = create_node(list->data, larger);
        } else {
            smaller = create_node(list->data, smaller);
        }
        list = list->next;
    }
    
    /* recusively sort larger and smaller lists. */
    smaller = quicksort(smaller);
    larger = quicksort(larger);

    smaller = append_lists(smaller, equal);
    free_list(equal);

    /* merege lists. */
    list = append_lists(smaller, larger);
    
    /* free all lists. */
    free_list(smaller);
    free_list(larger);

    /* check that list is sorter. */
    assert(is_sorted(list) == 1);

    /* Return sorted list. */
    return list;
}

int main(int argc, char *argv[]) {
    int index;
    int to_print = 1;
    node *list = NULL;

    /* make sure there is some command line input. */
    if(argc < 2) {
        fprintf(stderr, \
                "usage: %s must have at least one input number\n", argv[0]);
    }

    for(index = 1; index < argc; index ++) { 
        /* Reading numbers and flags from command line. */
        if(strcmp(argv[index], "-q") == 0) {
            to_print = 0;
        } else {
            list = create_node(atoi(argv[index]), list);
        } 
    }

    list = quicksort(list);

    if(to_print == 1) { /* Printing elements unless -q flag is used. */
        print_list(list);
    }
   
    free_list(list);
    
    print_memory_leaks();
    return 0;
}
