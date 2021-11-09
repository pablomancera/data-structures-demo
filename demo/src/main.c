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

int main() {
	setlocale(LC_ALL, "");
	array a = new_array();
	wchar_t chr = '\n';

	FILE *charptr = fopen("chars.txt", "r");

	if (!charptr) {
		wprintf(L"file failed to open");
		abort();
	}

	// Stores all the file in a dynamic array
	while ((chr = getwc(charptr)) != WEOF) {
		array_push_back(&a, chr);
	}

	fclose(charptr);

	wprintf(L"aray size: %d\n", a.size);

	clock_t begin = clock();

	// Find the longest char in the file
	unsigned int longest_char = 0;
	for (int i = 0; i < a.size; i++) {
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
	wchar_t *arr_start_wchar = NULL; //The adress at the start of a string.
	wchar_t *arr_start_null = NULL; //The address at the start of null chars.
	bool is_reading_wchar = false;
	unsigned int arr_size = a.size;
	for (int i = 0; i <= arr_size; i++) {

		//Finds and saves the addres of a string in array to arr_start_wchar
		if (a.data[i] && !is_reading_wchar && arr_wchar_cursor) {
			is_reading_wchar = true;
			arr_start_wchar = &a.data[i];
			continue;
		}

		//Copy memory pointed by arr_start_wchar to arr_wchar_cursor
		if (is_reading_wchar && (!a.data[i] || i == arr_size)) {
			unsigned int bytes_to_copy = (unsigned int) (&a.data[i] - arr_start_wchar);
			unsigned int array_size_offset = (unsigned int) (arr_start_wchar - arr_start_null);
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
			unsigned int array_size_offset = (unsigned int) (&a.data[i] - arr_start_null);
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

	// wprintf(L"\nNo dup array: %ls\nTime elapsed: %fs\n", array_to_string(&nodup), (double)(end-begin)/CLOCKS_PER_SEC);
	wprintf(L"No dup array: %ls\nTime elapsed: %fs\nArray size: %d\n", array_to_string(&a), (double)(end-begin)/CLOCKS_PER_SEC, a.size);

	return 0;
}