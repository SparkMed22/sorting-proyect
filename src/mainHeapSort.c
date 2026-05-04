#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listas.h"
#include "heapSort.h"

int sizes[] = {
    100,       // Micro: Sobrecarga de inicialización
    500,       // Pequeño
    1000,      // Pequeño/Mediano
    2000,      // Mediano (inicio de divergencia clara)
    5000,      // Mediano/Grande
    10000,     // Grande
    20000,     // Grande
    50000,     // Muy Grande (aquí la diferencia debe ser evidente)
    100000,    // Enorme
    200000,    // Muy Enorme
    500000,    // Límite de rendimiento
    1000000,   // 1 Millón (Prueba de estrés)
    2000000    // 2 Millones (Si tu máquina lo aguanta)
};
int num_sizes = 13;

void fill_random_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    srand(time(NULL));

    FILE *file = fopen("results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Header CSV
    fprintf(file, "size,arraylist_time,linkedlist_time\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        int *data = malloc(n * sizeof(int));
        fill_random_array(data, n);

        /* ===========================
           ARRAY LIST
           =========================== */
        ArrayList *arr = arraylist_create(n);

        for (int i = 0; i < n; i++) {
            arraylist_push(arr, data[i]);
        }

        clock_t start = clock();
        heapSortArrayList(arr);
        clock_t end = clock();

        double time_array = (double)(end - start) / CLOCKS_PER_SEC;

        /* ===========================
           LINKED LIST
           =========================== */
        LinkedList *list = linkedlist_create();

        for (int i = 0; i < n; i++) {
            linkedlist_add(list, data[i]);
        }

        start = clock();
        heapSortLinkedList(list);
        end = clock();

        double time_list = (double)(end - start) / CLOCKS_PER_SEC;

        /* ===========================
           GUARDAR CSV
           =========================== */
        fprintf(file, "%d,%f,%f\n", n, time_array, time_list);

        printf("n=%d | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_list);

        /* liberar memoria */
        arraylist_free(arr);
        linkedlist_free(list);
        free(data);
    }

    fclose(file);

    printf("\nResultados guardados en results.csv\n");

    return 0;
}