#include "heapSort.h"

/* ===========================
   AUXILIARES (ARRAY)
   =========================== */

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


/* ===========================
   HEAPSORT ARRAYLIST
   =========================== */

void heapSortArrayList(ArrayList *list) {
    NOT_NULL(list);

    int n = list->size;
    int *arr = list->data;

    // Construir heap (reorganizar array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extraer elementos del heap
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);     // mover raíz al final
        heapify(arr, i, 0);         // re-heapify
    }
}


/* ===========================
   HEAPSORT LINKEDLIST
   =========================== */

void heapSortLinkedList(LinkedList *list) {
    NOT_NULL(list);

    if (list->size <= 1) return;

    int n = list->size;

    // 1. Copiar a array
    int *arr = (int*) malloc(n * sizeof(int));
    NOT_NULL(arr);

    Nodo *current = list->head;
    for (int i = 0; i < n; i++) {
        arr[i] = current->value;
        current = current->next;
    }

    // 2. HeapSort sobre array
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

    // 3. Volver a copiar a la lista
    current = list->head;
    for (int i = 0; i < n; i++) {
        current->value = arr[i];
        current = current->next;
    }

    free(arr);
}