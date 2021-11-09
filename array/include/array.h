#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    uint size;
    uint capacity;
} array;

array new_array();
char array_get(array*, uint);
void array_set(array*, uint, char);
char array_push_back(array*, char);
void array_remove(array*, uint);
uint array_size(array*);
char *array_to_string(array*);