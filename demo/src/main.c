#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	while (chr != WEOF) {
		chr = getwc(charptr);
		//wprintf(L"%lc", chr);
		array_push_back(&a, chr);
	}

	fclose(charptr);

	wprintf(L"aray size: %d", a.size);

	clock_t begin = clock();

	unsigned int longest_char = 0;
	for (int i = 0; i < a.size - 1; i++) {
		if (a.data[i] > longest_char) {
			longest_char = a.data[i];
		}
	}

	bool *chars = calloc(longest_char, sizeof(bool));

	// array nodup = new_array();
	for (int i = 0; i < a.size-1; i++) {
		if (!chars[a.data[i]]) {
			chars[a.data[i]] = true;
			// array_push_back(&nodup, a.data[i]);
			continue;
		}
		a.data[i] = '\0';
	}

	wchar_t *start_addr = NULL;
	int start_index = 0;
	for (int i = 0; i < a.size; i++) {
		if (a.data[i] == '\0' && !start_addr) {
			start_addr = &a.data[i];
			start_index = i;
			continue;
		}
		if (a.data[i] != '\0' && start_addr) {
			wmemcpy(start_addr, &a.data[i], (a.size) - i);
			a.size -= i - start_index;
			i -= start_index;
			start_addr = NULL;
		}
	}

	

	clock_t end = clock();

	// wprintf(L"\nNo dup array: %ls\nTime elapsed: %fs\n", array_to_string(&nodup), (double)(end-begin)/CLOCKS_PER_SEC);
	wprintf(L"No dup array: %ls\nTime elapsed: %fs\n", array_to_string(&a), (double)(end-begin)/CLOCKS_PER_SEC);

	return 0;
}