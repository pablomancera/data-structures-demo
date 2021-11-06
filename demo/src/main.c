#include <stdio.h>
#include <string.h>
#include "list.h"

int main() {
    list a = new_list();
    char *string1 = "esto es una prueba";
    struct node *nodes_back[strlen(string1)];
    for (int i = 0; i < strlen(string1); i++) {
        nodes_back[i] = list_push_back(&a, string1[i]);
    }
    char *string2 = (" ,eyO");
    struct node *nodes_front[strlen(string2)];
    for (int i = 0; i < strlen(string2); i++) {
        nodes_front[i] = list_push_front(&a, string2[i]);
    }
    list_print_all(&a);
    for (int i = 0; i < strlen(string1); i++) {
        list_add_before(&a, nodes_back[i], '.');
        list_add_after(&a, nodes_back[i], ',');
    }
    for (int i = 0; i < strlen(string2); i++) {
        list_add_before(&a, nodes_front[i], ':');
        list_add_after(&a, nodes_front[i], ';');
    }
    list_to_string(&a);
    return 0;
}