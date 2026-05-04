#ifndef LISTAS_H
#define LISTAS_H

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum { FALSE = 0, TRUE = 1 } Bool;

typedef struct _ArrayList {
    int size;
    int cap;
    void **arr;
} ArrayList;

ArrayList* initArrayList(int cap);
Bool push(ArrayList *list, void *element);
void* pop(ArrayList *list);
void* get(ArrayList *list, int index);
Bool freeArrayList(ArrayList *list);

/**
 * Macro para verificar que un puntero no sea NULL
 */
#define MACRO_NOT_NULL(ptr)                                    \
    {                                                          \
        assert(ptr != NULL && "ERROR AL RECERVAR LA MEMORIA"); \
    }

#define MACRO_LinkedList_NOT_NULL(ptr)                  \
    {                                                   \
        assert(ptr != NULL && "EL LinkedList ES NULL"); \
    }
/**
 * Implementacion de listas Ligadas
 */

typedef struct _nodo
{
    int valor;
    struct _nodo *sig;
} Nodo;

typedef struct _linkedList
{
    Nodo *head;
    int size;
    Nodo *ultimo;
} LinkedList;

LinkedList *createLinkedList();
Nodo *createNodo(int valor);
void addLinkedList(LinkedList *list, int valor);
void printLinkedList(LinkedList *list);
void freeMemory(LinkedList *list);

#endif