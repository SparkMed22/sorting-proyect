#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapSort.h"
#include "radixSort.h"
#include "quickSort.h"
#include "util.h"

// Tamaños de prueba definidos según tus implementaciones previas
static int sizes[] = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 2000000};
static int num_sizes = 9;

void ejecutar_comparativa(const char* nombre_archivo, int tipo_dato) {
    FILE *file = fopen(nombre_archivo, "w");
    if (!file) {
        printf("Error al crear el archivo %s\n", nombre_archivo);
        return;
    }

    fprintf(file, "size,heap_array,radix_array,quick_array,heap_linkedlist,radix_linkedlist,quick_linkedlist\n");
    printf("\n--- Comparativa: %s ---\n", nombre_archivo);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *base = malloc(n * sizeof(int));

        // Generación de datos
        if (tipo_dato == 1) generateRandom(base, n);
        else if (tipo_dato == 2) generateSorted(base, n);
        else generateReversed(base, n);

        // --- Benchmark HeapSort (Array) ---
        int *arr_heap = malloc(n * sizeof(int));
        for(int j=0; j<n; j++) arr_heap[j] = base[j];
        clock_t start = clock();
        heapSortArray(arr_heap, n);
        double t_heap_arr = (double)(clock() - start) / CLOCKS_PER_SEC;

        // --- Benchmark RadixSort (Array) ---
        int *arr_radix = malloc(n * sizeof(int));
        for(int j=0; j<n; j++) arr_radix[j] = base[j];
        start = clock();
        radixSortArray(arr_radix, n);
        double t_radix_arr = (double)(clock() - start) / CLOCKS_PER_SEC;

        // --- Benchmark QuickSort (Array) ---
        int *arr_quick = malloc(n * sizeof(int));
        for(int j=0; j<n; j++) arr_quick[j] = base[j];
        start = clock();
        quickSortArray(arr_quick, n);
        double t_quick_arr = (double)(clock() - start) / CLOCKS_PER_SEC;

        // --- Benchmark HeapSort (LinkedList) ---
        LinkedList *list_heap = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(list_heap, base[j]);
        start = clock();
        heapSortLinkedList(list_heap, n);
        double t_heap_ll = (double)(clock() - start) / CLOCKS_PER_SEC;

        // --- Benchmark RadixSort (LinkedList) ---
        LinkedList *list_radix = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(list_radix, base[j]);
        start = clock();
        radixSortLinkedList(list_radix, n);
        double t_radix_ll = (double)(clock() - start) / CLOCKS_PER_SEC;

        // --- Benchmark QuickSort (LinkedList) ---
        LinkedList *list_quick = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(list_quick, base[j]);
        start = clock();
        quickSortLinkedList(list_quick, n);
        double t_quick_ll = (double)(clock() - start) / CLOCKS_PER_SEC;

        // Guardar y mostrar resultados
        fprintf(file, "%d, %f, %f, %f, %f, %f, %f\n",
                n, t_heap_arr, t_radix_arr, t_quick_arr,
                t_heap_ll, t_radix_ll, t_quick_ll);

        printf("n=%7d | Heap: %f | Radix: %f | Quick: %f (Array)\n",
               n, t_heap_arr, t_radix_arr, t_quick_arr);
        printf("n=%7d | Heap: %f | Radix: %f | Quick: %f (LinkedList)\n",
               n, t_heap_ll, t_radix_ll, t_quick_ll);
        printf("-------------------------------------------------------------\n");

        // Liberar memoria para la siguiente iteración
        free(base);
        free(arr_heap);
        free(arr_radix);
        free(arr_quick);
        linkedlist_free(list_heap);
        linkedlist_free(list_radix);
        linkedlist_free(list_quick);
    }

    fclose(file);
}

int main() {
    srand((unsigned int)time(NULL));

    // 1=Aleatorio, 2=Ordenado, 3=Invertido
    ejecutar_comparativa("vs-aleatorio.csv", 1);
    ejecutar_comparativa("vs-ordenado.csv", 2);
    ejecutar_comparativa("vs-invertido.csv", 3);

    printf("\nEnfrentamiento finalizado. Revisa los archivos .csv generados.\n");
    return 0;
}
