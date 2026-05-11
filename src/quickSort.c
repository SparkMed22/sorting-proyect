#include "quickSort.h"
#include "listas.h"
#include <stdlib.h>

// ==================== AUXILIAR ====================

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Insertion sort para subarreglos pequeños.
 * Cuando el subarreglo es menor a UMBRAL, es mas rapido que seguir dividiendo.
 */
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
 * Mediana de tres: ordena arr[low], arr[mid], arr[high] entre si
 * y deja el mayor en arr[high] como pivote.
 * Garantiza que el pivote divide bien en arreglos ordenados e invertidos.
 */
static int mediana_de_tres(int *arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid])  swap(&arr[low],  &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low],  &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid],  &arr[high]);

    return arr[high];
}

/**
 * Particion Lomuto con pivote = mediana de tres.
 */
static int partition(int *arr, int low, int high) {
    int pivot = mediana_de_tres(arr, low, high);
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
 * QuickSort recursivo con umbral: subarreglos pequenos se resuelven
 * con insertion sort para evitar overhead de recursion excesiva.
 */
static void quickSortRecursive(int *arr, int low, int high) {
    while (low < high) {
        // Subarreglo pequeno: insertion sort es mas eficiente
        if (high - low < UMBRAL) {
            insertionSort(arr, low, high);
            break;
        }
        int pi = partition(arr, low, high);

        // Recursion desde el lado mas pequeno, iteracion en el grande
        // Esto limita la profundidad maxima del stack a O(log n)
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
    // (QuickSort necesita acceso aleatorio; LinkedList no lo tiene ni lo tendra)
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
