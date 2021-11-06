#include <stdio.h>
#include <string.h>
#include "list.h"

int main() {
    list a = new_list();
    char *string1 = "esto es una prueba";
    for (int i = 0; i < strlen(string1); i++) {
        list_push_back(&a, string1[i]);
    }
    char *string2 = (" ,eyO");
    for (int i = 0; i < strlen(string2); i++) {
        list_push_front(&a, string2[i]);
    }
    list_print_all(&a);
    list_erase_key(&a, 'e');
    list_pop_front(&a);
    list_pop_back(&a);
    list_print_all(&a);
    return 0;
}