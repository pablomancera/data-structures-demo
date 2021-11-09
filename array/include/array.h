#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef struct {
    wchar_t *data;
    unsigned int size;
    unsigned int capacity;
} array;

array new_array();
wchar_t array_get(array*, unsigned int);
void array_set(array*, unsigned int, wchar_t);
wchar_t array_push_back(array*, wchar_t);
void array_remove(array*, unsigned int);
unsigned int array_size(array*);
wchar_t *array_to_string(array*);