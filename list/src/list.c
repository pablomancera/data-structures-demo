#include "list.h"
#include "array.h"
#include <wchar.h>

list new_list() {
    list l = {NULL, NULL};
    return l;
}

struct node *list_push_front(list *l, wchar_t chr) {
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null wchar_t @ list push_front\n");
        return NULL;
    }

    struct node *newData = malloc(sizeof(struct node));
    if (!newData) {
        fprintf(stderr, "malloc() @ list push_front failed. Exiting...\n");
        abort();
    }
    newData->key = chr;
    newData->next_node = l->head;

    if (list_is_empty(l)) {
        l->head = l->tail = newData;
    } else {
        l->head = newData;
    }

    return newData;
}

struct node *list_top_front(list *l) {
    if (list_is_empty(l)) {
        fprintf(stderr, "List is empty @ list top_front\n");
        return NULL;
    }

    struct node *data = l->head;
    return data;
}

void list_pop_front(list *l) {
    if (list_is_empty(l)) {
        fprintf(stderr, "List point to nothing @ list pop_front\n");
        return;
    }
    struct node *old_data = l->head;
    struct node *new_data = old_data->next_node;
    
    l->head = (l->head == l->tail) ? l->tail = NULL : new_data;

    free(old_data);
}

struct node *list_push_back(list *l, wchar_t chr) {
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null wchar_t @ list push_back\n");
        return NULL;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list push_back failed. Exiting...\n");
        abort();
    }

    new_data->key = chr;
    new_data->next_node = NULL;

    if (list_is_empty(l)) {
        l->head = l->tail = new_data;
    } else {
        struct node *old_data = l->tail;
        old_data->next_node = l->tail = new_data;  
    }

    return new_data;
}

struct node *list_top_back(list *l) {
    if (list_is_empty(l)) {
        fprintf(stderr, "List is empty @ list top_front\n");
        return NULL;
    }

    struct node *data = l->tail;
    return data;

}

void list_pop_back(list *l) {
    if (!l->tail) {
        fprintf(stderr, "List point to nothing @ list pop_back\n");
        return;
    }
    struct node *old_data = l->tail;
    struct node *new_data = l->head;

    if (old_data == new_data) {
        l->head = l->tail = NULL;
        free(old_data);
        return;
    }
    
    while (new_data->next_node->next_node) {
        new_data = new_data->next_node;
    }
    new_data->next_node = NULL;
    l->tail = new_data;
    free(old_data);
}

bool list_find_key(list *l, wchar_t chr) {
    if (list_is_empty(l)) {
        return false;
    }

    struct node *data = l->head;

    while (data->key != chr) {
        if (!data) {
            return false;
        }
        data = data->next_node;
    }
    return true;
}

void list_erase_key(list *l, wchar_t chr) {
    if (list_is_empty(l)) {
        return;
    }
    
    struct node *old_data, *new_data;
    old_data = new_data = l->head;

    //Pop front while header match
    while (l->head->key == chr) {
        list_pop_front(l);
        new_data = old_data = l->head;
        if (list_is_empty(l)) return;
    }
    //Pop next matching node
    while (new_data->next_node) {
        old_data = new_data->next_node;
        if (old_data->key == chr) {
            if (old_data == l->tail) {
                new_data->next_node = NULL;
                l->tail = new_data;
                free(old_data);
                return;
            } else {
                new_data->next_node = old_data->next_node;
                free(old_data);
                continue;
            }
        }
        new_data = new_data->next_node;
    }
}

inline bool list_is_empty(list *l) {
    return !l->head;
}

struct node *list_add_before(list *l, struct node *node, wchar_t chr) {
    if (list_is_empty(l)) {
        return NULL;
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null wchar_t @ list add_before\n");
        return NULL;
    }

    if (l->head == node) {
        struct node *new_data = list_push_front(l, chr);
        return new_data;
    }

    struct node *old_data = l->head;

    while (old_data->next_node != node) {
        if (!old_data->next_node) {
            fprintf(stderr, "Node %p does not exist in list %p @ list add_before", node, l);
            return NULL;
        }
        old_data = old_data->next_node;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list add_before failed. Exiting...\n");
        abort();        
    }

    new_data->key = chr;

    new_data->next_node = old_data->next_node;
    old_data->next_node = new_data;

    return new_data;
}

struct node *list_add_after(list *l, struct node *node, wchar_t chr) {
    if (list_is_empty(l)) {
        return NULL;
    }
    if (chr == '\0') {
        fprintf(stderr, "Cannot allocate null wchar_t @ list add_before\n");
        return NULL;
    }

    struct node *old_data = l->head;

    while (old_data != node) {
        if (!old_data) {
            fprintf(stderr, "Node %p does not exist in list %p @ list add_before", node, l);
            return NULL;            
        }
        old_data = old_data->next_node;
    }

    struct node *new_data = malloc(sizeof(struct node));
    if (!new_data) {
        fprintf(stderr, "malloc() @ list add_before failed. Exiting...\n");
        abort();        
    }

    new_data->key = chr;

    if (old_data == l->tail) {
        new_data->next_node = NULL;
        old_data->next_node = l->tail = new_data;
    } else {
        new_data->next_node = old_data->next_node;
        old_data->next_node = new_data;
    }

    return new_data;
}

void list_print_all(list *l) {
    if (list_is_empty(l)) {
        wprintf(L"List is empty\n");
    }
    
    struct node *data = l->head;
    wprintf(L"The values in the list are: [");
    while (data->next_node) {
        wprintf(L"'%lc', ", data->key);
        data = data->next_node;
    }
    wprintf(L"'%lc']\n", data->key);
}

wchar_t *list_to_string(list *l) {
    if (list_is_empty(l)) {
        wprintf(L"List is empty\n");
        return NULL;
    }

    struct node *data = l->head;
    array a = new_array();
    while (data) {
        array_push_back(&a, data->key);
        data = data->next_node;
    }
    wchar_t *str = array_to_string(&a);

    array_free(&a);
    
    return str;
}

void list_free(list *l) {
    while (!list_is_empty(l)) {
        list_pop_back(l);
    }
}