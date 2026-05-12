/**
 * @file main.c
 * @brief Benchmark comparativo: Heap vs Radix vs Quick (Arrays y LinkedLists)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapSort.h"
#include "radixSort.h"
#include "quickSort.h"
#include "util.h"
#include "config.h"

static int sizes[] = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 2000000};
static int num_sizes = 9;


void print_progress_bar(int current, int total) {
    int width = 25;
    float ratio = (float)current / total;
    int pos = (int)(width * ratio);
    
    printf(WHITE "  Progreso: [" RESET);
    for (int i = 0; i < width; i++) {
        if (i < pos) printf(CYAN "■" RESET);
        else printf(" ");
    }
    printf(WHITE "] %d%%\r" RESET, (int)(ratio * 100));
    fflush(stdout);
}

void ejecutar_comparativa(const char* nombre_archivo, const char* titulo, int tipo_dato) {
    FILE *file = fopen(nombre_archivo, "w");
    if (!file) {
        printf(RED BOLD "[ERROR] No se pudo crear el archivo %s\n" RESET, nombre_archivo);
        return;
    }

    fprintf(file, "size,heap_arr,radix_arr,quick_arr,heap_ll,radix_ll,quick_ll\n");

    printf(BOLD MAGENTA "\n>>> %s <<<\n" RESET, titulo);
    
    printf(BOLD WHITE "%-10s | %-25s | %-25s\n" RESET, "Tam (n)", "ARRAYS (s)", "LINKED LISTS (s)");
    printf(WHITE "           | %-7s %-7s %-7s | %-7s %-7s %-7s\n" RESET, 
           "Heap", "Radix", "Quick", "Heap", "Radix", "Quick");
    printf("-----------|-------------------------|-------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *base = malloc(n * sizeof(int));

        if (tipo_dato == 1) generateRandom(base, n);
        else if (tipo_dato == 2) generateSorted(base, n);
        else generateReversed(base, n);

        print_progress_bar(i + 1, num_sizes);

        int *arr = malloc(n * sizeof(int));

        for(int j=0; j<n; j++) arr[j] = base[j];
        clock_t start = clock(); heapSortArray(arr, n);
        double t_ha = (double)(clock() - start) / CLOCKS_PER_SEC;

        for(int j=0; j<n; j++) arr[j] = base[j];
        start = clock(); radixSortArray(arr, n);
        double t_ra = (double)(clock() - start) / CLOCKS_PER_SEC;

        for(int j=0; j<n; j++) arr[j] = base[j];
        start = clock(); quickSortArray(arr, n);
        double t_qa = (double)(clock() - start) / CLOCKS_PER_SEC;
        free(arr);

        // --- Benchmarks LinkedList ---
        double t_hl = 0, t_rl = 0, t_ql = 0;

        // Nota: Solo ejecutamos LL si n no es excesivamente grande (opcional)
        // Heap LL
        LinkedList *l = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(l, base[j]);
        start = clock(); heapSortLinkedList(l, n);
        t_hl = (double)(clock() - start) / CLOCKS_PER_SEC;
        linkedlist_free(l);

        // Radix LL
        l = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(l, base[j]);
        start = clock(); radixSortLinkedList(l, n);
        t_rl = (double)(clock() - start) / CLOCKS_PER_SEC;
        linkedlist_free(l);

        // Quick LL
        l = linkedlist_create();
        for(int j=0; j<n; j++) linkedlist_add(l, base[j]);
        start = clock(); quickSortLinkedList(l, n);
        t_ql = (double)(clock() - start) / CLOCKS_PER_SEC;
        linkedlist_free(l);

        // --- Salida de Resultados ---
        fprintf(file, "%d, %f, %f, %f, %f, %f, %f\n", n, t_ha, t_ra, t_qa, t_hl, t_rl, t_ql);

        // Limpiar línea de progreso e imprimir fila de tabla
        printf("\r%-10d | " YELLOW "%-7.4f " GREEN "%-7.4f " BLUE "%-7.4f " RESET "| " YELLOW "%-7.4f " GREEN "%-7.4f " BLUE "%-7.4f\n" RESET, 
               n, t_ha, t_ra, t_qa, t_hl, t_rl, t_ql);

        free(base);
    }

    fclose(file);
    printf(BOLD GREEN "[OK] Datos guardados en %s\n" RESET, nombre_archivo);
}

int main() {
    srand((unsigned int)time(NULL));

    printf(BOLD WHITE "\n============================================================\n" RESET);
    printf(BOLD WHITE "          COMPARATIVA FINAL DE ALGORITMOS DE ORDENAMIENTO\n" RESET);
    printf(BOLD WHITE "============================================================\n" RESET);

    ejecutar_comparativa("vs-aleatorio.csv", "ESCENARIO: DATOS ALEATORIOS", 1);
    ejecutar_comparativa("vs-ordenado.csv",  "ESCENARIO: DATOS ORDENADOS", 2);
    ejecutar_comparativa("vs-invertido.csv", "ESCENARIO: DATOS INVERTIDOS", 3);

    printf(BOLD CYAN "\nBenchmark finalizado. Visualice los archivos .csv para gráficas.\n" RESET);
    return 0;
}