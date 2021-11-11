#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "list.h"
#include "array.h"

void array_exercise(char *filename);
void list_exercise(char *filename);

int main() {
	setlocale(LC_ALL, "");

	array_exercise("test_1k.txt");
	array_exercise("test_10k.txt");
	array_exercise("test_100k.txt");
	array_exercise("test_1m.txt");
	array_exercise("test_10m.txt");

	list_exercise("test_1k.txt");
	list_exercise("test_10k.txt");
	list_exercise("test_100k.txt");
	list_exercise("test_1m.txt");
	list_exercise("test_10m.txt");

	return 0;
}

void array_exercise(char *filename) {
	array tmp_file_arr = new_array();
	wchar_t *tmp_file_str = L"";
	wchar_t chr = '\n';

	FILE *fileptr = fopen(filename, "r");

	if (!fileptr) {
		fwprintf(stderr, L"file \"%s\" failed to open. Exiting...\n", filename);
		abort();
	}

	chr = fgetwc(fileptr);

	if (chr == WEOF) {
		fwprintf(stderr, L"file \"%s\" is empty. Exiting...\n", filename);
		abort();
	}

	ungetwc(chr, fileptr);

	// Stores all the file in a dynamic array
	while ((chr = fgetwc(fileptr)) != WEOF) {
		array_push_back(&tmp_file_arr, chr);
	}

	fclose(fileptr);

	for (int i = 0; i <= 100; i++) {
		wprintf(L"-");
	}

	wprintf(L"\n\n-- Array test --");

	wprintf(L"\n\nFile: \"%s\"\n", filename);
	wprintf(L"Array size: %d\n", tmp_file_arr.size);

	tmp_file_str = array_to_string(&tmp_file_arr);

	clock_t begin = clock();

	array a = new_array();

	for (unsigned int i = 0; tmp_file_str[i]; i++) {
		array_push_back(&a, tmp_file_str[i]);
	}

	// Find the longest char in the file
	unsigned int longest_char = 0;
	for (unsigned int i = 0; i < a.size; i++) {
		if (a.data[i] > longest_char) {
			longest_char = a.data[i];
		}
	}

	bool *chars = calloc(longest_char, sizeof(bool));

	//Sets NULL to duplicated chars
	for (int i = 0; i < a.size; i++) {
		if (!chars[a.data[i]]) {
			chars[a.data[i]] = true;
			continue;
		}
		a.data[i] = '\0';
	}

	wchar_t *arr_wchar_cursor = NULL; //Cursor that will override the array.
	wchar_t *arr_start_wchar = NULL;  //The adress at the start of a string.
	wchar_t *arr_start_null = NULL;	  //The address at the start of null chars.
	bool is_reading_wchar = false;
	unsigned int arr_size = a.size;
	for (unsigned int i = 0; i <= arr_size; i++) {

		//Finds and saves the addres of a string in array to arr_start_wchar
		if (a.data[i] && !is_reading_wchar && arr_wchar_cursor &&
				i < arr_size) {
			is_reading_wchar = true;
			arr_start_wchar = &a.data[i];
			continue;
		}

		//Copy memory pointed by arr_start_wchar to arr_wchar_cursor
		if (is_reading_wchar && (!a.data[i] || i == arr_size)) {
			unsigned int bytes_to_copy =
					(unsigned int)(&a.data[i] - arr_start_wchar);
			unsigned int array_size_offset =
					(unsigned int)(arr_start_wchar - arr_start_null);
			wmemcpy(arr_wchar_cursor, arr_start_wchar, bytes_to_copy);
			a.size -= array_size_offset;
			arr_wchar_cursor += bytes_to_copy;
			arr_start_wchar = NULL;
			arr_start_null = &a.data[i];
			is_reading_wchar = false;
			continue;
		}

		//Adjust the size of the dynamic array when no unique chars remains
		if (i == arr_size) {
			unsigned int array_size_offset =
					(unsigned int)(&a.data[i] - arr_start_null);
			a.size -= array_size_offset;
			continue;
		}

		//Finds and saves the addres of a null char
		if (!arr_wchar_cursor && !a.data[i]) {
			arr_wchar_cursor = &a.data[i];
			arr_start_null = &a.data[i];
			continue;
		}
	}

	clock_t end = clock();

	wchar_t *string = array_to_string(&a);

	wprintf(L"No dup array: %ls\n", string);
	wprintf(L"Time elapsed: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
	wprintf(L"Array final size: %d\n", a.size);
	wprintf(L"\n");
	for (int i = 0; i <= 100; i++) {
		wprintf(L"-");
	}
	wprintf(L"\n\n");

	array_free(&a);
	free(chars);
	free(string);
}

void list_exercise(char *filename) {
	array tmp_file_arr = new_array();
	wchar_t *tmp_file_str = L"";
	wchar_t chr = '\n';

	FILE *fileptr = fopen(filename, "r");

	if (!fileptr) {
		fwprintf(stderr, L"file \"%s\" failed to open. Exiting...\n", filename);
		abort();
	}

	chr = fgetwc(fileptr);

	if (chr == WEOF) {
		fwprintf(stderr, L"file \"%s\" is empty. Exiting...\n", filename);
		abort();
	}

	ungetwc(chr, fileptr);

	// Stores all the file in a dynamic array
	while ((chr = fgetwc(fileptr)) != WEOF) {
		array_push_back(&tmp_file_arr, chr);
	}

	fclose(fileptr);

	for (int i = 0; i <= 100; i++) {
		wprintf(L"-");
	}

	wprintf(L"\n\n-- List test --");

	wprintf(L"\n\nFile: \"%s\"\n", filename);
	wprintf(L"Number of characters: %d\n", tmp_file_arr.size);

	tmp_file_str = array_to_string(&tmp_file_arr);

	clock_t begin = clock();

	list l = new_list();

	for (unsigned int i = 0; tmp_file_str[i]; i++) {
		list_push_back(&l, tmp_file_str[i]);
	}

	struct node *data = l.head;

	// Find the longest char in the file
	unsigned int longest_char = 0;
	while (data) {
		if (data->key > longest_char) {
			longest_char = data->key;
		}
		data = data->next_node;
	}

	data = l.head;

	bool *chars = calloc(longest_char, sizeof(bool));

	//Remove nodes with duplicated keys
	chars[data->key] = true;
	while (data->next_node) {
		if (!chars[data->next_node->key]) {
			chars[data->next_node->key] = true;
			data = data->next_node;
			continue;
		}
		struct node *old_data = data->next_node;
		data->next_node = data->next_node->next_node;
		if (old_data == l.tail)
			l.tail = data;
		free(old_data);
	}

	clock_t end = clock();

	wchar_t *string = list_to_string(&l);
	wprintf(L"No dup list: %ls\n", string);
	wprintf(L"Time elapsed: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
	wprintf(L"\n");
	for (int i = 0; i <= 100; i++) {
		wprintf(L"-");
	}
	wprintf(L"\n\n");

	list_free(&l);
	free(chars);
	free(string);
}