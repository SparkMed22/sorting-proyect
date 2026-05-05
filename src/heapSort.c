#include "heapSort.h"
#include "listas.h"

// ==================== AUXILIAR ====================
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(int *arr, int n, int i) {
    int largest = i;        // raíz
    int left = 2 * i + 1;  // hijo izquierdo
    int right = 2 * i + 2; // hijo derecho

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// ==================== ARRAY ====================
void heapSortArray(int *datos, int cant) {
    if (datos == NULL || cant <= 1) return;

    for (int i = cant / 2 - 1; i >= 0; i--) {
        heapify(datos, cant, i);
    }

    for (int i = cant - 1; i > 0; i--) {
        swap(&datos[0], &datos[i]); 
        heapify(datos, i, 0);       
    }
}

// ==================== ARRAYLIST ====================
void heapSortArrayList(ArrayList *list, int cant) {
    if (list == NULL || list->data == NULL || cant <= 1) return;

    if (cant > list->size) cant = list->size;

    heapSortArray(list->data, cant);
}

// ==================== LINKEDLIST ====================
void heapSortLinkedList(LinkedList *list, int cant) {
    if (list == NULL || cant <= 1) return;

    if (cant > list->size) cant = list->size;

    int *temp = (int*) malloc(sizeof(int) * cant);
    NOT_NULL(temp);

    Nodo *current = list->head;
    for (int i = 0; i < cant && current != NULL; i++) {
        temp[i] = current->value;
        current = current->next;
    }

    heapSortArray(temp, cant);

    current = list->head;
    for (int i = 0; i < cant && current != NULL; i++) {
        current->value = temp[i];
        current = current->next;
    }

    free(temp);
}