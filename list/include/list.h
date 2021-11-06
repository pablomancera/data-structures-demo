#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    struct node *head, *tail;
} list;

struct node {
    char key;
    struct node *nextNode;
};

list new_list();
void list_push_front(list*, char);
char *list_top_front(list*);
void list_pop_front(list*);
void list_push_back(list*, char);
char *list_top_back(list*);
void list_pop_back(list*);
bool list_find_key(list*, char);
void list_erase_key(list*, char);
void list_add_before(list*, char);
void list_print_all(list*);