/**
 * @file lab_QuickSort.c
 * @brief Benchmark del algoritmo Quick Sort con visualización Premium.
 *
 * @author Gonzalo Solis
 * @date 2026-05-12
 * @version 0.0.4
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quickSort.h"
#include "lab_QuickSort.h"
#include "util.h"
#include "config.h"


static const int sizes[] = {
    100, 500, 1000, 2000, 5000, 10000, 20000, 
    50000, 100000, 200000, 500000, 1000000, 2000000
};

static const int TOTAL_SIZES = sizeof(sizes) / sizeof(sizes[0]);
typedef void (*GeneratorFunction)(int *, int);

/* =========================================================
 * APOYO VISUAL MEJORADO
 * ========================================================= */

void printProgress(int current, int total) {
    int width = 25;
    float progress = (float)current / total;
    int pos = width * progress;

    printf("  " WHITE "Status: [" RESET);
    for (int i = 0; i < width; ++i) {
        if (i < pos) printf(CYAN "█" RESET);
        else if (i == pos) printf(WHITE "▒" RESET);
        else printf(" ");
    }
    printf(WHITE "] " BOLD YELLOW "%d%%" RESET " \r", (int)(progress * 100));
    fflush(stdout);
}

/* =========================================================
 * BENCHMARKS
 * ========================================================= */

static void copyArray(int *dest, const int *src, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

static double benchmarkArray(const int *data, int n) {
    int *temp = malloc(sizeof(int) * n);
    copyArray(temp, data, n);
    clock_t start = clock();
    quickSortArray(temp, n);
    clock_t end = clock();
    free(temp);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static double benchmarkArrayList(const int *data, int n) {
    ArrayList *list = arraylist_create(n);
    for (int i = 0; i < n; i++) arraylist_push(list, data[i]);
    clock_t start = clock();
    quickSortArrayList(list, n);
    clock_t end = clock();
    arraylist_free(list);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static double benchmarkLinkedList(const int *data, int n) {
    LinkedList *list = linkedlist_create();
    for (int i = 0; i < n; i++) linkedlist_add(list, data[i]);
    clock_t start = clock();
    quickSortLinkedList(list, n);
    clock_t end = clock();
    linkedlist_free(list);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/* =========================================================
 * NÚCLEO DEL BENCHMARK
 * ========================================================= */

static int runBenchmark(const char *title, const char *filename, GeneratorFunction generator) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf(RED BOLD "\n[✘] ERROR: No se pudo crear %s\n" RESET, filename);
        return 1;
    }

    fprintf(file, "size,array_time,arraylist_time,linkedlist_time\n");

    // Cabecera con fondo y bordes dobles
    printf("\n" BG_CYAN BOLD WHITE " %-64s " RESET "\n", title);
    printf(BOLD WHITE " %-12s │ %-13s │ %-13s │ %-13s \n" RESET, 
           "Elementos", "Array (s)", "ArrayList(s)", "LinkedList(s)");
    printf("─────────────┼───────────────┼───────────────┼───────────────\n");

    for (int s = 0; s < TOTAL_SIZES; s++) {
        int n = sizes[s];
        int *base = malloc(sizeof(int) * n);
        if (!base) return 1;

        generator(base, n);
        printProgress(s + 1, TOTAL_SIZES);

        double tArr = benchmarkArray(base, n);
        double tAL  = benchmarkArrayList(base, n);
        double tLL  = benchmarkLinkedList(base, n); // Se eliminó el "saltado"

        fprintf(file, "%d,%f,%f,%f\n", n, tArr, tAL, tLL);

        // Impresión con colores por columna para diferenciar estructuras
        printf("\r " BOLD "%-12d" RESET " │ " GREEN "%-13.6f" RESET " │ " BLUE "%-13.6f" RESET " │ " MAGENTA "%-13.6f" RESET "\n", 
               n, tArr, tAL, tLL);

        free(base);
    }

    printf("─────────────┴───────────────┴───────────────┴───────────────\n");
    fclose(file);
    printf(BOLD GREEN " [✔] Resultados guardados en: %s\n" RESET, filename);
    return 0;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf(BOLD CYAN "\n╔══════════════════════════════════════════════════════════╗");
    printf("\n║" WHITE "                QUICK SORT PERFORMANCE TOOL                " CYAN "║");
    printf("\n╚══════════════════════════════════════════════════════════╝\n" RESET);

    runBenchmark("ESCENARIO: DATOS ALEATORIOS", "quick-aleatorio.csv", generateRandom);
    runBenchmark("ESCENARIO: DATOS ORDENADOS",   "quick-ordenado.csv",  generateSorted);
    runBenchmark("ESCENARIO: DATOS INVERTIDOS",  "quick-invertido.csv", generateReversed);

    printf(BOLD GREEN "\n[!] Benchmark completado con éxito.\n\n" RESET);

    return 0;
}