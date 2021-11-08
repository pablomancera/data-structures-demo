#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list new_list() {
    list a = {NULL, NULL};
    return a;
}

struct node *list_push_front(list *a, char chr) {
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list push_front\n");
        return NULL;
    }

    struct node *newData = malloc(sizeof(struct node));
    if (!newData) {
        fprintf(stderr, "malloc() @ list push_front failed. Exiting...\n");
        abort();
    }
    newData->key = chr;
    newData->nextNode = a->head;

    if (list_is_empty(a)) {
        a->head = a->tail = newData;
    } else {
        a->head = newData;
    }

    return newData;
}

struct node *list_top_front(list *a) {
    if (list_is_empty(a)) {
        fprintf(stderr, "List is empty @ list top_front\n");
        return NULL;
    }

    struct node *data = a->head;
    return data;
}

void list_pop_front(list *a) {
    if (list_is_empty(a)) {
        fprintf(stderr, "List point to nothing @ list pop_front\n");
        return;
    }
    struct node *old_data = a->head;
    struct node *new_data = old_data->nextNode;
    
    a->head = (a->head == a->tail) ? a->tail = NULL : new_data;

    free(old_data);
}

struct node *list_push_back(list *a, char chr) {
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list push_back\n");
        return NULL;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list push_back failed. Exiting...\n");
        abort();
    }

    new_data->key = chr;
    new_data->nextNode = NULL;

    if (list_is_empty(a)) {
        a->head = a->tail = new_data;
    } else {
        struct node *old_data = a->tail;
        old_data->nextNode = a->tail = new_data;  
    }

    return new_data;
}

struct node *list_top_back(list *a) {
    if (list_is_empty(a)) {
        fprintf(stderr, "List is empty @ list top_front\n");
        return NULL;
    }

    struct node *data = a->tail;
    return data;

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
    if (list_is_empty(a)) {
        return false;
    }

    struct node *data = a->head;

    while (data->key != chr) {
        if (!data) {
            return true;
        }
        data = data->nextNode;
    }
    return false;
}

void list_erase_key(list *a, char chr) {
    if (list_is_empty(a)) {
        return;
    }
    
    struct node *old_data, *new_data;
    old_data = new_data = a->head;

    //Pop front while header match
    while (a->head->key == chr) {
        list_pop_front(a);
        new_data = old_data = a->head;
        if (list_is_empty(a)) return;
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

inline bool list_is_empty(list *a) {
    return !a->head;
}

struct node *list_add_before(list *a, struct node *node, char chr) {
    if (list_is_empty(a)) {
        return NULL;
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list add_before\n");
        return NULL;
    }

    if (a->head == node) {
        struct node *new_data = list_push_front(a, chr);
        return new_data;
    }

    struct node *old_data = a->head;

    while (old_data->nextNode != node) {
        if (!old_data->nextNode) {
            fprintf(stderr, "Node %p does not exist in list %p @ list add_before", node, a);
            return NULL;
        }
        old_data = old_data->nextNode;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list add_before failed. Exiting...\n");
        abort();        
    }

    new_data->key = chr;

    new_data->nextNode = old_data->nextNode;
    old_data->nextNode = new_data;

    return new_data;
}

struct node *list_add_after(list *a, struct node *node, char chr) {
    if (list_is_empty(a)) {
        return NULL;
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null char @ list add_before\n");
        return NULL;
    }

    if (a->head == node) {
        struct node *new_data = list_push_front(a, chr);
        return new_data;
    }

    struct node *old_data = a->head;

    while (old_data != node) {
        if (!old_data) {
            fprintf(stderr, "Node %p does not exist in list %p @ list add_before", node, a);
            return NULL;            
        }
        old_data = old_data->nextNode;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list add_before failed. Exiting...\n");
        abort();        
    }

    new_data->key = chr;

    if (old_data == a->tail) {
        new_data->nextNode = NULL;
        old_data->nextNode = a->tail = new_data;
    } else {
        new_data->nextNode = old_data->nextNode;
        old_data->nextNode = new_data;
    }

    return new_data;
}

void list_print_all(list *a) {
    if (list_is_empty(a)) {
        printf("List is empty\n");
    } else {
        struct node *data = a->head;
        printf("The values in the list are: [");
        while (data) {
            printf("'%c', ", data->key);
            data = data->nextNode;
        }
        printf("]\n");
    }
}

void list_to_string(list *a) {
    if (list_is_empty(a)) {
        printf("List is empty\n");
    } else {
        struct node *data = a->head;
        while (data) {
            printf("%c", data->key);
            data = data->nextNode;
        }
        printf("\n");
    }
}