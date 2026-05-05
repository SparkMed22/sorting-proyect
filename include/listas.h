#ifndef LISTAS_H
#define LISTAS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int size;
    int capacity;
    int *data;
} ArrayList;

ArrayList* arraylist_create(int capacity);

void arraylist_print(ArrayList *list);

bool arraylist_push(ArrayList *list, int value);

void arraylist_free(ArrayList *list);


/* ===========================
   LINKED LIST (simple)
   =========================== */

typedef struct Nodo {
    int value;
    struct Nodo *next;
} Nodo;

typedef struct {
    Nodo *head;
    Nodo *tail;
    int size;
} LinkedList;

LinkedList* linkedlist_create();
Nodo* nodo_create(int value);

void linkedlist_add(LinkedList *list, int value); 

void linkedlist_print(LinkedList *list);

void linkedlist_free(LinkedList *list);

#define NOT_NULL(ptr) assert((ptr) != NULL)

#define CHECK_INDEX(i, size) \
    assert((i) >= 0 && (i) < (size))

#endif