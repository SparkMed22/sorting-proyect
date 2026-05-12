#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "radixSort.h"
#include "util.h"
#include "lab_RadixSort.h"
#include "config.h"

int sizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000};
int total_sizes = 13;

void print_header(const char* title) {
    printf("\n" BOLD MAGENTA "=== %s ===" RESET "\n", title);
    printf(CYAN "%-10s | %-12s | %-12s | %-12s" RESET "\n", "Tamaño", "Array (s)", "ArrayList(s)", "LinkedList(s)");
    printf(BLUE "-------------------------------------------------------------" RESET "\n");
}

// Función genérica para ejecutar las pruebas y evitar repetir código
int run_test(const char* filename, const char* test_name, void (*gen_func)(int*, int)) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf(RED "Error al abrir el archivo %s" RESET "\n", filename);
        return 1;
    }

    print_header(test_name);
    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < total_sizes; s++) {
        int n = sizes[s];
        int* base = malloc(n * sizeof(int));
        gen_func(base, n);

        // --- ARRAY ---
        int* array = malloc(n * sizeof(int)); // Mejor malloc para evitar Stack Overflow en n grandes
        for (int i = 0; i < n; i++) array[i] = base[i];
        
        clock_t start = clock();
        radixSortArray(array, n);
        double time_array = (double)(clock() - start) / CLOCKS_PER_SEC;
        free(array);

        // --- ARRAY LIST ---
        ArrayList* arrayList = arraylist_create(n);
        for (int i = 0; i < n; i++) arraylist_push(arrayList, base[i]);

        start = clock();
        radixSortArrayList(arrayList, n);
        double time_arrayList = (double)(clock() - start) / CLOCKS_PER_SEC;
        arraylist_free(arrayList);

        // --- LINKED LIST ---
        LinkedList *list = linkedlist_create();
        for (int i = 0; i < n; i++) linkedlist_add(list, base[i]);

        start = clock();
        radixSortLinkedList(list, n);
        double time_linkedList = (double)(clock() - start) / CLOCKS_PER_SEC;
        linkedlist_free(list);

        // Guardar y Mostrar con colores
        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);
        
        printf(YELLOW "%-10d" RESET " | " GREEN "%-12.6f" RESET " | " GREEN "%-12.6f" RESET " | " GREEN "%-12.6f" RESET "\n",
               n, time_array, time_arrayList, time_linkedList);

        free(base);
    }

    fclose(file);
    printf(BOLD CYAN "✔ Resultados guardados en: %s" RESET "\n", filename);
    return 0;
}

int main() {
    srand(time(NULL));

    printf(BOLD WHITE "\nINICIANDO BENCHMARK DE RADIX SORT" RESET "\n");
    printf(BOLD WHITE "=================================" RESET "\n");

    run_test("radix-aleatorio-results.csv", "TEST: DATOS ALEATORIOS", generateRandom);
    run_test("radix-ordenado-results.csv", "TEST: DATOS ORDENADOS", generateSorted);
    run_test("radix-invertido-results.csv", "TEST: DATOS INVERTIDOS", generateReversed);

    printf(BOLD GREEN "\n[!] Pruebas finalizadas con éxito.\n" RESET);

    return 0;
}