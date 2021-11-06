#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list new_list() {
    list a = {NULL, NULL};
    return a;
}

void list_push_front(list *a, char chr) {
    struct node *newData = malloc(sizeof(struct node));
    if (!newData) {
        fprintf(stderr, "malloc() @ list push_front failed. Exiting...\n");
        abort();
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list push_front\n");
        return;
    }
    newData->key = chr;
    newData->nextNode = a->head;

    if (!a->head) {
        a->head = a->tail = newData;
    } else {
        a->head = newData;
    }
}

char *list_top_front(list *a) {
    if (!a->head) {
        fprintf(stderr, "List point to nothing @ list top_front\n");
        return NULL;
    } else {
        struct node *data = a->head;
        return &data->key;
    }
}

void list_pop_front(list *a) {
    if (!a->head) {
        fprintf(stderr, "List point to nothing @ list pop_front\n");
        return;
    }
    struct node *old_data = a->head;
    struct node *new_data = old_data->nextNode;
    
    a->head = a->head == a->tail ? a->tail = NULL : new_data;

    free(old_data);
}

void list_push_back(list *a, char chr) {
    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list push_back failed. Exiting...\n");
        abort();
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list push_back\n");
        return;
    }

    new_data->key = chr;
    new_data->nextNode = NULL;

    if (!a->head) {
        a->head = a->tail = new_data;
    } else {
        struct node *old_data = a->tail;
        old_data->nextNode = new_data;
        a->tail = new_data;        
    }
}

void list_pop_back(list *a) {
    if (!a->tail) {
        fprintf(stderr, "List point to nothing @ list pop_back\n");
        return;
    }
    struct node *old_data = a->tail;
    struct node *new_data = a->head;

    if (old_data == new_data) {
        a->head = a->tail = NULL;
        free(old_data);
    } else {
        while (new_data->nextNode->nextNode) {
            new_data = new_data->nextNode;
        }
        new_data->nextNode = NULL;
        a->tail = new_data;
        free(old_data);
    }
}

bool list_find_key(list *a, char chr) {
    if (!a->head) {
        return false;
    }

    struct node *data = a->head;

    while (data) {
        if (data->key == chr) {
            return true;
        }
        data = data->nextNode;
    }
    return false;
}

void list_erase_key(list *a, char chr) {
    if (!a->head) {
        return;
    }
    
    struct node *old_data, *new_data;
    old_data = new_data = a->head;

    //Pop front while header match
    while (old_data->key == chr) {
        list_pop_front(a);
        new_data = old_data = a->head;
        if (!a->head) return;
    }
    //Pop next matching node
    while (new_data->nextNode) {
        old_data = new_data->nextNode;
        if (old_data->key == chr) {
            if (old_data == a->tail) {
                new_data->nextNode = NULL;
                a->tail = new_data;
                free(old_data);
                return;
            } else {
                new_data->nextNode = old_data->nextNode;
                free(old_data);
                continue;
            }
        }
        new_data = new_data->nextNode;
    }
}

void list_print_all(list *a) {
    if (!a->head) {
        printf("List is empty\n");
    } else {
        struct node *data = a->head;
        printf("The values on the list are: [");
        while (data->nextNode) {
            printf("'%c', ", data->key);
            data = data->nextNode;
        }
        printf("'%c']\n", data->key);
    }
}