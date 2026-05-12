/**
 * @file lab_QuickSort.c
 * @brief Benchmark del algoritmo Quick Sort con visualización mejorada.
 *
 * @author Gonzalo Solis
 * @date 2026-05-12
 * @version 0.0.3
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quickSort.h"
#include "lab_QuickSort.h"
#include "util.h"

/* =========================================================
 * COLORES ANSI Y ESTILOS
 * ========================================================= */

#define RESET  "\x1b[0m"
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE   "\x1b[34m"
#define CYAN   "\x1b[36m"
#define WHITE  "\x1b[37m"
#define BOLD   "\x1b[1m"

/* =========================================================
 * CONFIGURACIÓN
 * ========================================================= */

static const int sizes[] = {
    100, 500, 1000, 2000, 5000, 10000, 20000, 
    50000, 100000, 200000, 500000, 1000000
};

static const int TOTAL_SIZES = sizeof(sizes) / sizeof(sizes[0]);

typedef void (*GeneratorFunction)(int *, int);

/* =========================================================
 * FUNCIONES DE APOYO VISUAL
 * ========================================================= */

/**
 * @brief Dibuja una barra de progreso en la misma línea.
 */
void printProgress(int current, int total) {
    int width = 20;
    float progress = (float)current / total;
    int pos = width * progress;

    printf(WHITE "  [" RESET);
    for (int i = 0; i < width; ++i) {
        if (i < pos) printf(CYAN "=" RESET);
        else if (i == pos) printf(CYAN ">" RESET);
        else printf(" ");
    }
    printf(WHITE "] %d%%\r" RESET, (int)(progress * 100));
    fflush(stdout);
}

/* =========================================================
 * BENCHMARKS INDIVIDUALES
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
    // Seguridad: QuickSort en LinkedList es extremadamente lento para N grandes
    if (n > 50000) return -1.0; 

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
        printf(RED BOLD "\n[ERROR] No se pudo crear %s\n" RESET, filename);
        return 1;
    }

    fprintf(file, "size,array_time,arraylist_time,linkedlist_time\n");

    printf(BOLD CYAN "\n>> ESCENARIO: %s\n" RESET, title);
    printf(BOLD WHITE "%-12s | %-12s | %-12s | %-12s\n" RESET, 
           "Elementos", "Array (s)", "ArrayList(s)", "LinkedList(s)");
    printf("-------------|--------------|--------------|--------------\n");

    for (int s = 0; s < TOTAL_SIZES; s++) {
        int n = sizes[s];
        int *base = malloc(sizeof(int) * n);
        if (!base) return 1;

        generator(base, n);
        printProgress(s + 1, TOTAL_SIZES);

        double tArr = benchmarkArray(base, n);
        double tAL  = benchmarkArrayList(base, n);
        double tLL  = benchmarkLinkedList(base, n);

        fprintf(file, "%d,%f,%f,%f\n", n, tArr, tAL, tLL);

        // Limpiar la línea de la barra de progreso y escribir la fila de la tabla
        printf("\r%-12d | %-12.6f | %-12.6f | ", n, tArr, tAL);
        if (tLL < 0) printf("%-12s\n", "SALTADO");
        else printf("%-12.6f\n", tLL);

        free(base);
    }

    fclose(file);
    printf(GREEN "  [OK] Resultados exportados a %s\n" RESET, filename);
    return 0;
}

/* =========================================================
 * MAIN
 * ========================================================= */

int main(void) {
    srand((unsigned int)time(NULL));

    printf(BOLD WHITE
           "\n==========================================================\n"
           "                QUICK SORT BENCHMARK V0.0.3\n"
           "==========================================================\n" RESET);

    runBenchmark("DATOS ALEATORIOS", "quick-aleatorio.csv", generateRandom);
    runBenchmark("DATOS ORDENADOS",   "quick-ordenado.csv",  generateSorted);
    runBenchmark("DATOS INVERTIDOS",  "quick-invertido.csv", generateReversed);

    printf(BOLD GREEN "\nBenchmark finalizado correctamente.\n" RESET);

    return 0;
}