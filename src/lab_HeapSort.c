#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listas.h"
#include "heapSort.h"
#include "lab_HeapSort.h"
#include "util.h"

static int sizes[] = {
    100, 500, 1000, 2000, 5000,
    10000, 20000, 50000,
    100000, 200000, 500000,
    1000000, 2000000
};

static int size = 13;

// =========================
// ALEATORIO
// =========================
int heap_sort_random() {
    srand(time(NULL));

    FILE *file = fopen("heap-aleatorio-results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
        int n = sizes[s];

        int* base = malloc(n * sizeof(int));
        generateRandom(base, n);

        // ===== ARRAY =====
        int *array = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) array[i] = base[i];

        clock_t start = clock();
        heapSortArray(array, n);
        clock_t end = clock();

        double time_array = (double)(end - start) / CLOCKS_PER_SEC;

        // ===== ARRAYLIST =====
        ArrayList* arrayList = arraylist_create(n);
        for (int i = 0; i < n; i++) arraylist_push(arrayList, base[i]);

        start = clock();
        heapSortArrayList(arrayList, n);
        end = clock();

        double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;

        // ===== LINKED LIST =====
        LinkedList *list = linkedlist_create();
        for (int i = 0; i < n; i++) linkedlist_add(list, base[i]);

        start = clock();
        heapSortLinkedList(list, n);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);

        free(array);
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);
    printf("\nResultados guardados en heap-aleatorio-results.csv\n");

    return 0;
}

// =========================
// ORDENADO
// =========================
int heap_sort_sorted() {
    srand(time(NULL));

    FILE *file = fopen("heap-ordenado-results.csv", "w");
    if (!file) return 1;

    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
        int n = sizes[s];

        int* base = malloc(n * sizeof(int));
        generateSorted(base, n);

        int *array = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) array[i] = base[i];

        clock_t start = clock();
        heapSortArray(array, n);
        clock_t end = clock();

        double time_array = (double)(end - start) / CLOCKS_PER_SEC;

        ArrayList* arrayList = arraylist_create(n);
        for (int i = 0; i < n; i++) arraylist_push(arrayList, base[i]);

        start = clock();
        heapSortArrayList(arrayList, n);
        end = clock();

        double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;

        LinkedList *list = linkedlist_create();
        for (int i = 0; i < n; i++) linkedlist_add(list, base[i]);

        start = clock();
        heapSortLinkedList(list, n);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);

        free(array);
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);
    printf("\nResultados guardados en heap-ordenado-results.csv\n");

    return 0;
}

// =========================
// INVERTIDO
// =========================
int heap_sort_reversed() {
    srand(time(NULL));

    FILE *file = fopen("heap-invertido-results.csv", "w");
    if (!file) return 1;

    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
        int n = sizes[s];

        int* base = malloc(n * sizeof(int));
        generateReversed(base, n);

        int *array = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) array[i] = base[i];

        clock_t start = clock();
        heapSortArray(array, n);
        clock_t end = clock();

        double time_array = (double)(end - start) / CLOCKS_PER_SEC;

        ArrayList* arrayList = arraylist_create(n);
        for (int i = 0; i < n; i++) arraylist_push(arrayList, base[i]);

        start = clock();
        heapSortArrayList(arrayList, n);
        end = clock();

        double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;

        LinkedList *list = linkedlist_create();
        for (int i = 0; i < n; i++) linkedlist_add(list, base[i]);

        start = clock();
        heapSortLinkedList(list, n);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);

        free(array);
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);
    printf("\nResultados guardados en heap-invertido-results.csv\n");

    return 0;
}

int main() {
    printf("=== HeapSort Benchmark ===\n");

    heap_sort_random();
    heap_sort_sorted();
    heap_sort_reversed();

    return 0;
}