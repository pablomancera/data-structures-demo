#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include "array.h"

typedef struct {
    struct node *head, *tail;
} list;

struct node {
    wchar_t key;
    struct node *next_node;
};

list new_list();
struct node *list_push_front(list*, wchar_t);
struct node *list_top_front(list*);
void list_pop_front(list*);
struct node *list_push_back(list*, wchar_t);
struct node *list_top_back(list*);
void list_pop_back(list*);
bool list_find_key(list*, wchar_t);
void list_erase_key(list*, wchar_t);
bool list_is_empty(list*);
struct node *list_add_before(list*, struct node*, wchar_t);
struct node *list_add_after(list*, struct node*, wchar_t);
void list_print_all(list*);
wchar_t *list_to_string(list*);
void list_free(list*);