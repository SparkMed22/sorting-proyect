/**
 * @file heapSort.c
 * @brief Implementación del algoritmo Heap Sort para distintos tipos de estructuras.
 *
 * Este módulo permite ordenar:
 * - Arrays de enteros
 * - ArrayList
 * - LinkedList
 *
 * El algoritmo Heap Sort tiene una complejidad temporal de:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 *
 * Complejidad espacial:
 * - Arrays y ArrayList: O(1)
 * - LinkedList: O(n), debido al uso de un arreglo temporal
 *
 * @author Francisco Medina
 * @date 2026-05-04
 * @version 0.0.2
 */

#include "heapSort.h"
#include <stdlib.h>

/**
 * FUNCIONES AUXILIARES
 * @brief Intercambia el valor de dos enteros.
 * 
 * @param a Puntero al primer entero.
 * @param b Puntero al segundo entero.
 */
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Convierte un subárbol en un Max-Heap.
 *
 * Reorganiza el árbol cuya raíz está en el índice `i`
 * para mantener la propiedad de Max-Heap.
 *
 * @param arr Arreglo de enteros.
 * @param n Cantidad de elementos válidos en el heap.
 * @param i Índice de la raíz del subárbol.
 */
static void heapify(int *arr, int n, int i) {
    int largest = i;
    int left  = (2 * i) + 1;
    int right = (2 * i) + 2;

    // Verificar hijo izquierdo 
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Verificar hijo derecho
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Si la raíz no es el mayor elemento, se intercambia y se continúa ajustando.
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

/**  
 * HEAP SORT PARA ARRAY
 * 
 * @brief Ordena un arreglo utilizando Heap Sort.
 *
 * El ordenamiento se realiza de menor a mayor.
 *
 * @param datos Arreglo de enteros.
 * @param cant Cantidad de elementos a ordenar.
 */
void heapSortArray(int *datos, int cant) {

    if (datos == NULL || cant <= 1) return;

    // Construcción del Max-Heap 
    for (int i = (cant / 2) - 1; i >= 0; i--) {
        heapify(datos, cant, i);
    }

    ///Extraer elementos del heap 
    for (int i = cant - 1; i > 0; i--) {
        swap(&datos[0], &datos[i]);
        heapify(datos, i, 0);
    }
}

/** 
 * HEAP SORT PARA ARRAYLIST
 * 
 * @brief Ordena un ArrayList utilizando Heap Sort.
 *
 * @param list Puntero al ArrayList.
 * @param cant Cantidad de elementos a ordenar.
 */
void heapSortArrayList(ArrayList *list, int cant) {

    if (list == NULL || list->data == NULL || cant <= 1)  return;
    
    if (cant > list->size) cant = list->size;

    heapSortArray(list->data, cant);
}


/** 
 *  HEAP SORT PARA LINKED LIST
 * 
 * @brief Ordena una LinkedList utilizando Heap Sort.
 *
 * Debido a que Heap Sort requiere acceso aleatorio,
 * los datos de la lista se copian temporalmente
 * a un arreglo.
 * 
 * @param list Puntero a la LinkedList.
 * @param cant Cantidad de elementos a ordenar.
 */
void heapSortLinkedList(LinkedList *list, int cant) {

    if (list == NULL || cant <= 1) {
        return;
    }

    if (cant > list->size) {
        cant = list->size;
    }

    int *temp = (int *) malloc(sizeof(int) * cant);
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