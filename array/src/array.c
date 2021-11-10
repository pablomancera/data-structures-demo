#include "array.h"

array new_array() {
	array a;
	a.data = malloc(sizeof(wchar_t));
	a.size = 0;
	a.capacity = 1;

	return a;
}

wchar_t array_get(array *a, unsigned int index) {
	if (!a || !a->data) {
		fprintf(stderr, "NULL array @ array get\n");
		return '\0';
	}
	if (index > a->size) {
		fprintf(stderr, "Index out of range @ array get\n");
		return '\0';
	}

	return a->data[index];
}

void array_set(array *a, unsigned int index, wchar_t chr) {
	if (!a || !a->data) {
		fprintf(stderr, "NULL array @ array set\n");
		return;
	}
	if (index > a->size) {
		fprintf(stderr, "Index out of range @ array set\n");
		return;
	}

	a->data[index] = chr;
}

wchar_t array_push_back(array *a, wchar_t chr) {
	if (!a || !a->data) {
		fprintf(stderr, "NULL array @ array push_back\n");
		return '\0';
	}
	if (a->size <= a->capacity) {
		a->data[a->size] = chr;
		a->size++;
		return chr;
	}

	a->capacity *= 2;

	wchar_t *tmp_array = realloc(a->data, a->capacity * sizeof(wchar_t));

	if (!tmp_array) {
		fprintf(stderr, "realloc() @ array push_back failed. Exiting...\n");
		abort();
	} else {
		a->data = tmp_array;
	}

	return array_push_back(a, chr);
}

void array_remove(array *a, unsigned int index) {
	if (!a || !a->data) {
		fprintf(stderr, "NULL array @ array remove\n");
		return;
	}

	if (index > a->size || a->size == 0) {
		fprintf(stderr, "Index out of range @ array remove\n");
		return;
	}

	for (unsigned int i = index; i <= a->size; i++) {
		a->data[i] = a->data[i + 1];
	}

    a->size--;
}

unsigned int array_size(array *a) {
    return a->size;
}

wchar_t *array_to_string(array *a) {
	if (!a || !a->data) {
		fprintf(stderr, "NULL array @ array to_string\n");
		return NULL;
	}

	wchar_t *str = malloc((a->size + 1) * sizeof(wchar_t));

	if (!str) {
		fprintf(stderr, "malloc() @ array to_string failed. Exiting...\n");
		abort();
	}

	wmemcpy(str, a->data, a->size);
	str[a->size] = '\0';

	return str;
}

void array_free(array *a) {
	free(a->data);
}