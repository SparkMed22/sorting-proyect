#include "heapSort.h"

void swapArray(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyArray(ArrayList *list, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && *(int*)list->arr[left] > *(int*)list->arr[largest])
        largest = left;

    if (right < n && *(int*)list->arr[right] > *(int*)list->arr[largest])
        largest = right;

    if (largest != i) {
        swapArray(&list->arr[i], &list->arr[largest]);
        heapifyArray(list, n, largest);
    }
}

void heapSortArrayList(ArrayList *list) {
    if (!list || list->size <= 1) return;

    for (int i = list->size / 2 - 1; i >= 0; i--)
        heapifyArray(list, list->size, i);

    for (int i = list->size - 1; i > 0; i--) {
        swapArray(&list->arr[0], &list->arr[i]);
        heapifyArray(list, i, 0);
    }
}



void heapSortLinkedList(LinkedList *list) {
    if (!list || list->size <= 1) return;

    int *tempArr = (int *)malloc(sizeof(int) * list->size);
    Nodo *actual = list->head;
    for (int i = 0; i < list->size; i++) {
        tempArr[i] = actual->valor;
        actual = actual->sig;
    }

    heapSort(tempArr, list->size); 

    actual = list->head;
    for (int i = 0; i < list->size; i++) {
        actual->valor = tempArr[i];
        actual = actual->sig;
    }

    free(tempArr);
}