#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "list.h"
#include "array.h"

int main() {
	setlocale(LC_ALL, "");
	list a = new_list();
	array arr = new_array();
	wchar_t *string1 = L"¿Qué te parece si mañana jugamos fútbol?";
	struct node **nodes_back = malloc(wcslen(string1) * sizeof(struct node *));

	for (int i = 0; i < wcslen(string1); i++) {
		nodes_back[i] = list_push_back(&a, string1[i]);
		array_push_back(&arr, string1[i]);
	}

	wchar_t *string2 = L" ,eyO";
	struct node **nodes_front = malloc(wcslen(string2) * sizeof(struct node *));

	for (int i = 0; i < wcslen(string2); i++) {
		nodes_front[i] = list_push_front(&a, string2[i]);
	}

	wchar_t *arrstr = array_to_string(&arr);

	wprintf(L"Dynamic array string: %ls\n", arrstr);
	wprintf(L"Dynamic array size: %d\n", array_size(&arr));
	wprintf(L"Dynamic array capacity: %d\n", arr.capacity);
	list_print_all(&a);

	free(arrstr);

	for (int i = 0; i < wcslen(string1); i++) {
		list_add_before(&a, nodes_back[i], '<');
		list_add_after(&a, nodes_back[i], '>');
	}
	for (int i = 0; i < wcslen(string2); i++) {
		list_add_before(&a, nodes_front[i], '[');
		list_add_after(&a, nodes_front[i], ']');
	}

	wprintf(L"The string in the list is: ");
	list_to_string(&a);

	wprintf(L"Let's print each string's char, one by one: ");
	for (int i = 0; i <= array_size(&arr); i++) {
		wprintf(L"%lc", array_get(&arr, i));
	}
	wprintf(L"\nNow let's set everything to 'e': ");

	for (int i = 0; i <= array_size(&arr); i++) {
		array_set(&arr, i, 'e');
	}
	arrstr = array_to_string(&arr);
	wprintf(L"%ls\nOk, now back to the original string: ", arrstr);
	free(arrstr);

	for (int i = 0; i < wcslen(string1); i++) {
		array_set(&arr, i, string1[i]);
	}

	arrstr = array_to_string(&arr);
	wprintf(L"%ls\nFinally, let's remove each char one by one: \n", arrstr);

	wprintf(L"String content: %ls\n", arrstr);
	wprintf(L"Array size: %d\n", array_size(&arr));

	free(arrstr);

	int len = array_size(&arr);

	for (int i = 0; i <= len; i++) {
		array_remove(&arr, 0);
		arrstr = array_to_string(&arr);
		wprintf(L"String content: %ls\n", arrstr);
		wprintf(L"Array size: %d\n", array_size(&arr));
		free(arrstr);
	}

	free(nodes_back);
	free(nodes_front);
	return 0;
}