#include "listas.h"


static bool arraylist_resize(ArrayList *list, int new_capacity) {
    NOT_NULL(list);

    int *new_data = realloc(list->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        return false;
    }

    list->data = new_data;
    list->capacity = new_capacity;
    return true;
}

ArrayList* arraylist_create(int capacity) {
    if (capacity <= 0) capacity = 4; // tamaño mínimo razonable

    ArrayList *list = (ArrayList*) malloc(sizeof(ArrayList));
    NOT_NULL(list);

    list->data = (int*) malloc(capacity * sizeof(int));
    NOT_NULL(list->data);

    list->size = 0;
    list->capacity = capacity;

    return list;
}


bool arraylist_push(ArrayList *list, int value) {
    NOT_NULL(list);

    // si está lleno → duplicar capacidad
    if (list->size >= list->capacity) {
        if (!arraylist_resize(list, list->capacity * 2)) {
            return false;
        }
    }

    list->data[list->size] = value;
    list->size++;

    return true;
}

void arraylist_print(ArrayList *list) {
    if (list == NULL) {
        printf("[NULL]\n");
        return;
    }

    printf("[ ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("]\n");
}

void arraylist_free(ArrayList *list) {
    if (list == NULL) return;

    free(list->data);
    free(list);
}


LinkedList* linkedlist_create() {
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
    NOT_NULL(list);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

Nodo* nodo_create(int value) {
    Nodo *node = (Nodo*) malloc(sizeof(Nodo));
    NOT_NULL(node);

    node->value = value;
    node->next = NULL;

    return node;
}

void linkedlist_add(LinkedList *list, int value) {
    NOT_NULL(list);

    Nodo *new_node = nodo_create(value);

    if (list->head == NULL) {
        // lista vacía
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

void linkedlist_print(LinkedList *list) {
    NOT_NULL(list);

    Nodo *current = list->head;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("]\n");
}

void linkedlist_free(LinkedList *list) {
    if (list == NULL) return;

    Nodo *current = list->head;
    while (current != NULL) {
        Nodo *temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}