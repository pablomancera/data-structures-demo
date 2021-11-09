#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "array.h"

int main() {
	list a = new_list();
	array arr = new_array();
	char *string1 = "esto es una prueba";
	struct node **nodes_back = malloc(strlen(string1) * sizeof(struct node *));

	for (int i = 0; i < strlen(string1); i++) {
		nodes_back[i] = list_push_back(&a, string1[i]);
		array_push_back(&arr, string1[i]);
	}

	char *string2 = (" ,eyO");
	struct node **nodes_front = malloc(strlen(string2) * sizeof(struct node *));

	for (int i = 0; i < strlen(string2); i++) {
		nodes_front[i] = list_push_front(&a, string2[i]);
	}

	char *arrstr = array_to_string(&arr);

	printf("Dynamic array string: %s\n", arrstr);
	printf("Dynamic array size: %d\n", array_size(&arr));
	printf("Dynamic array capacity: %d\n", arr.capacity);
	list_print_all(&a);

	free(arrstr);

	for (int i = 0; i < strlen(string1); i++) {
		list_add_before(&a, nodes_back[i], '<');
		list_add_after(&a, nodes_back[i], '>');
	}
	for (int i = 0; i < strlen(string2); i++) {
		list_add_before(&a, nodes_front[i], '[');
		list_add_after(&a, nodes_front[i], ']');
	}

	printf("The string in the list is: ");
	list_to_string(&a);

	printf("Let's print each string's char, one by one: ");
	for (int i = 0; i <= array_size(&arr); i++) {
		printf("%c", array_get(&arr, i));
	}
	printf("\nNow let's set everything to 'e': ");

	for (int i = 0; i <= array_size(&arr); i++) {
		array_set(&arr, i, 'e');
	}
	arrstr = array_to_string(&arr);
	printf("%s\nOk, now back to the original string: ", arrstr);
	free(arrstr);

	for (int i = 0; i < strlen(string1); i++) {
		array_set(&arr, i, string1[i]);
	}

	arrstr = array_to_string(&arr);
	printf("%s\nFinally, let's remove each char one by one: \n", arrstr);

	printf("String content: %s\n", arrstr);
	printf("Array size: %d\n", array_size(&arr));

	free(arrstr);

	int len = array_size(&arr);

	for (int i = 0; i <= len; i++) {
		array_remove(&arr, 0);
		arrstr = array_to_string(&arr);
		printf("String content: %s\n", arrstr);
		printf("Array size: %d\n", array_size(&arr));
		free(arrstr);
	}

	free(nodes_back);
	free(nodes_front);
	return 0;
}