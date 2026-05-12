#include "quickSort.h"
#include <stdlib.h>
#include <time.h>

// ==================== AUXILIAR ====================

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#define UMBRAL 16

static void insertionSort(int *arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/**
 * Particion con pivote ALEATORIO.
 * Se elige un indice al azar entre low y high para evitar
 * el peor caso O(n^2) en arreglos ya ordenados o invertidos.
 */
static int partition(int *arr, int low, int high) {
    // Pivote aleatorio: evita O(n^2) en ordenados e invertidos
    int rand_idx = low + rand() % (high - low + 1);
    swap(&arr[rand_idx], &arr[high]);

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
 * QuickSort con optimizacion de recursion de cola:
 * recursa en el lado mas pequeno e itera en el grande.
 * Limita la profundidad del stack a O(log n).
 */
static void quickSortRecursive(int *arr, int low, int high) {
    while (low < high) {
        if (high - low < UMBRAL) {
            insertionSort(arr, low, high);
            break;
        }
        int pi = partition(arr, low, high);

        if (pi - low < high - pi) {
            quickSortRecursive(arr, low, pi - 1);
            low = pi + 1;
        } else {
            quickSortRecursive(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

// ==================== ARRAY ====================
void quickSortArray(int *datos, int cant) {
    if (datos == NULL || cant <= 1) return;
    srand((unsigned int)time(NULL)); // Inicializa semilla para pivote aleatorio
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
