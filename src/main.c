#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listas.h"
#include "heapSort.h"

int main() {
    /* Inicializar generador de números aleatorios */
    srand((unsigned int)time(NULL));

    /* ===========================
       TEST ARRAY LIST
       =========================== */
    printf("=== ArrayList ===\n");

    ArrayList *arr = arraylist_create(2); // Capacidad inicial pequeña para forzar resize

    // Insertar 100 elementos aleatorios entre 1 y 1000
    printf("Insertando 100 elementos aleatorios en ArrayList...\n");
    for (int i = 0; i < 100; i++) {
        int valor = rand() % 1000 + 1;
        if (!arraylist_push(arr, valor)) {
            printf("Error al insertar en ArrayList\n");
            arraylist_free(arr);
            return 1;
        }
    }

    printf("Elementos en ArrayList (antes de ordenar): ");
    arraylist_print(arr);

    // Ordenar el ArrayList
    heapSortArrayList(arr);

    printf("\nElementos en ArrayList (ordenados): ");
    arraylist_print(arr);
    printf("\nSize: %d | Capacity: %d\n", arr->size, arr->capacity);

    arraylist_free(arr);

    /* ===========================
       TEST LINKED LIST
       =========================== */
    printf("\n=== LinkedList ===\n");

    LinkedList *list = linkedlist_create();

    // Insertar 100 elementos aleatorios entre 1 y 1000
    printf("Insertando 100 elementos aleatorios en LinkedList...\n");
    for (int i = 0; i < 100; i++) {
        int valor = rand() % 1000 + 1;
        linkedlist_add(list, valor);
    }

    printf("Elementos en LinkedList (antes de ordenar): ");
    linkedlist_print(list);

    printf("Size: %d\n", list->size);

    // Ordenar la LinkedList
    heapSortLinkedList(list);

    printf("Elementos en LinkedList (ordenados): ");
    linkedlist_print(list);

    linkedlist_free(list);

    return 0;
}
