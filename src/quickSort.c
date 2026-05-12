/**
 * @file quickSort.c
 * @brief Implementación optimizada del algoritmo Quick Sort.
 *
 * Este módulo permite ordenar:
 * - Arrays de enteros
 * - ArrayList
 * - LinkedList
 *
 * Características de la implementación:
 * - Pivote aleatorio para evitar peores casos frecuentes.
 * - Optimización con Insertion Sort para subarreglos pequeños.
 * - Optimización de recursión de cola.
 * - Profundidad máxima del stack cercana a O(log n).
 *
 * Complejidad temporal:
 * - Mejor caso:    O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso:     O(n²)
 *
 * Complejidad espacial:
 * - Arrays / ArrayList: O(log n)
 * - LinkedList: O(n) por arreglo temporal
 *
 * @author Gonzalo Solis
 * @date 2026-05-12
 * @version 0.0.1
 */

#include "quickSort.h"

#include <stdlib.h>
#include <time.h>

/**
 * CONFIGURACIÓN
 * 
 * @brief Tamaño mínimo para usar Insertion Sort.
 *
 * Para arreglos pequeños, Insertion Sort suele ser
 * más eficiente que Quick Sort debido al menor overhead.
 */
#define INSERTION_THRESHOLD 16

/**
 * FUNCIONES AUXILIARES
 * 
 * @brief Intercambia dos enteros.
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
 * @brief Ordena un subarreglo usando Insertion Sort.
 *
 * Se utiliza como optimización para arreglos pequeños.
 *
 * @param arr  Arreglo de enteros.
 * @param low  Índice inicial.
 * @param high Índice final.
 */
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
 * @brief Realiza la partición del arreglo.
 *
 * Selecciona un pivote aleatorio para reducir la
 * probabilidad del peor caso en arreglos ya ordenados
 * o invertidos.
 *
 * @param arr  Arreglo de enteros.
 * @param low  Índice inicial.
 * @param high Índice final.
 *
 * @return Posición final del pivote.
 */
static int partition(int *arr, int low, int high) {

    /* Selección de pivote aleatorio */
    int randomIndex = low + rand() % (high - low + 1);

    swap(&arr[randomIndex], &arr[high]);

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
 * @brief Implementación recursiva optimizada de Quick Sort.
 *
 * Características:
 * - Usa Insertion Sort para particiones pequeñas.
 * - Reduce profundidad del stack mediante
 *   recursión de cola.
 *
 * Estrategia:
 * - Se recursa primero sobre la partición más pequeña.
 * - La partición más grande se procesa iterativamente.
 *
 * @param arr  Arreglo de enteros.
 * @param low  Índice inicial.
 * @param high Índice final.
 */
static void quickSortRecursive(int *arr, int low, int high) {

    while (low < high) {
        if ((high - low) < INSERTION_THRESHOLD) {
            insertionSort(arr, low, high);
            break;
        }
        int pivotIndex = partition(arr, low, high);
        if ((pivotIndex - low) < (high - pivotIndex)) {
            quickSortRecursive(arr, low, pivotIndex - 1);
            low = pivotIndex + 1;
        } else {
            quickSortRecursive(arr, pivotIndex + 1, high);
            high = pivotIndex - 1;
        }
    }
}

/**
 * QUICK SORT PARA ARRAY
 * 
 * @brief Ordena un arreglo utilizando Quick Sort.
 *
 * @param datos Arreglo de enteros.
 * @param cant  Cantidad de elementos.
 */
void quickSortArray(int *datos, int cant) {

    if (datos == NULL || cant <= 1) return;
    quickSortRecursive(datos, 0, cant - 1);
}

/**
 * QUICK SORT PARA ARRAYLIST
 * 
 * @brief Ordena un ArrayList utilizando Quick Sort.
 *
 * @param list Puntero al ArrayList.
 * @param cant Cantidad de elementos a ordenar.
 */
void quickSortArrayList(ArrayList *list, int cant) {

    if (list == NULL || list->data == NULL || cant <= 1)  return;
    
    if (cant > list->size) cant = list->size;
    
    quickSortArray(list->data, cant);
}

/**
 * QUICK SORT PARA LINKED LIST
 * 
 * @brief Ordena una LinkedList utilizando Quick Sort.
 *
 * Debido a que Quick Sort requiere acceso aleatorio,
 * los datos de la lista se copian temporalmente
 * a un arreglo.
 *
 * Proceso:
 * 1. Copiar lista a arreglo temporal.
 * 2. Ordenar arreglo.
 * 3. Copiar datos ordenados nuevamente.
 *
 * @param list Puntero a la LinkedList.
 * @param cant Cantidad de elementos a ordenar.
 */
void quickSortLinkedList(LinkedList *list, int cant) {

    if (list == NULL || cant <= 1)  return;
    

    if (cant > list->size) cant = list->size;

    int *temp = (int *) malloc(sizeof(int) * cant);

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