#include "quickSort.h"
#include <stdlib.h>
#include "listas.h"


// ==================== AUXILIAR ====================

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Particion con pivote en el ultimo elemento como esquema Lomuto
 * Coloca el pivote en su posicion final y retorna su indice
 */
static int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/**
 * QuickSort recursivo sobre un sub-arreglo [low..high].
 */
static void quickSortRecursive(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

// ==================== ARRAY ====================
void quickSortArray(int *datos, int cant) {
    if (datos == NULL || cant <= 1) return;
    quickSortRecursive(datos, 0, cant - 1);
}

// ==================== ARRAYLIST ====================
void quickSortArrayList(ArrayList *list, int cant) {
    if (list == NULL || list->data == NULL || cant <= 1) return;
    if (cant > list->size) cant = list->size;
    quickSortArray(list->data, cant);
}

// ==================== LINKEDLIST ====================
void quickSortLinkedList(LinkedList *list, int cant) {
    if (list == NULL || cant <= 1) return;
    if (cant > list->size) cant = list->size;

    // Copiar a arreglo temporal, ordenar, y devolver
    int *temp = (int*) malloc(sizeof(int) * cant);
    NOT_NULL(temp);

    Nodo *current = list->head;
    for (int i = 0; i < cant && current != NULL; i++) {
        temp[i] = current->value;
        current = current->next;
    }

    quickSortArray(temp, cant);

    current = list->head;
    for (int i = 0; i < cant && current != NULL; i++) {
        current->value = temp[i];
        current = current->next;
    }

    free(temp);
}
