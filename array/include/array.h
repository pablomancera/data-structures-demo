#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    unsigned int size;
    unsigned int capacity;
} array;

array new_array();
char array_get(array*, unsigned int);
void array_set(array*, unsigned int, char);
char array_push_back(array*, char);
void array_remove(array*, unsigned int);
unsigned int array_size(array*);
char *array_to_string(array*);