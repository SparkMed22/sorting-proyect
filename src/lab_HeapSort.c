#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Simulación de las cabeceras del proyecto
#include "heapSort.h"
#include "lab_HeapSort.h"
#include "util.h"
#include "config.h"

// Configuración del benchmark
#define ITERACIONES_POR_PRUEBA 3

static const int sizes[] = {
    100, 500, 1000, 2000, 5000, 10000, 20000, 
    50000, 100000, 200000, 500000, 1000000};

static const int TOTAL_SIZES = sizeof(sizes) / sizeof(sizes[0]);

typedef void (*GeneratorFunction)(int *, int);

/**
 * @brief Dibuja una barra de progreso simple en la terminal.
 */
void printProgress(int current, int total) {
    int width = 20;
    float progress = (float)current / total;
    int pos = width * progress;

    printf(WHITE "  Progreso: [" RESET);
    for (int i = 0; i < width; ++i) {
        if (i < pos) printf(CYAN "=" RESET);
        else if (i == pos) printf(CYAN ">" RESET);
        else printf(" ");
    }
    printf(WHITE "] %d%%\r" RESET, (int)(progress * 100));
    fflush(stdout);
}

static void copyArray(int *dest, const int *src, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

static double benchmarkArray(const int *data, int n) {
    int *temp = malloc(sizeof(int) * n);
    copyArray(temp, data, n);
    
    clock_t start = clock();
    heapSortArray(temp, n);
    clock_t end = clock();
    
    free(temp);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static double benchmarkArrayList(const int *data, int n) {
    ArrayList *list = arraylist_create(n);
    for (int i = 0; i < n; i++) arraylist_push(list, data[i]);
    
    clock_t start = clock();
    heapSortArrayList(list, n);
    clock_t end = clock();
    
    arraylist_free(list);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static double benchmarkLinkedList(const int *data, int n) {
    LinkedList *list = linkedlist_create();
    for (int i = 0; i < n; i++) linkedlist_add(list, data[i]);

    clock_t start = clock();
    heapSortLinkedList(list, n);
    clock_t end = clock();

    linkedlist_free(list);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

static int runBenchmark(const char *title, const char *filename, GeneratorFunction generator) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf(RED "\n[ERROR] No se pudo crear %s\n" RESET, filename);
        return 1;
    }

    fprintf(file, "size,array_time,arraylist_time,linkedlist_time\n");

    printf(BOLD CYAN "\n>> %s\n" RESET, title);
    printf(BOLD WHITE "%-12s | %-12s | %-12s | %-12s\n" RESET, 
           "Elementos", "Array (s)", "ArrayList(s)", "LinkedList(s)");
    printf("-------------|--------------|--------------|--------------\n");

    for (int s = 0; s < TOTAL_SIZES; s++) {
        int n = sizes[s];
        int *base = malloc(sizeof(int) * n);
        if (!base) return 1;
        
        generator(base, n);

        double tArr = 0, tAL = 0, tLL = 0;

        // Promediamos para mayor precisión
        for (int i = 0; i < ITERACIONES_POR_PRUEBA; i++) {
            printProgress(s + 1, TOTAL_SIZES);
            tArr += benchmarkArray(base, n);
            tAL  += benchmarkArrayList(base, n);
            // Ojo: LinkedList puede ser muy lento en n grandes, podrías omitirlo en n > 100k
            if (n <= 100000) tLL += benchmarkLinkedList(base, n); 
        }

        tArr /= ITERACIONES_POR_PRUEBA;
        tAL  /= ITERACIONES_POR_PRUEBA;
        tLL  /= ITERACIONES_POR_PRUEBA;

        fprintf(file, "%d,%f,%f,%f\n", n, tArr, tAL, tLL);
        
        // Limpiar la línea de la barra de progreso y escribir la fila de la tabla
        printf("\r%-12d | %-12.6f | %-12.6f | %-12.6f\n", n, tArr, tAL, tLL);

        free(base);
    }

    fclose(file);
    printf(GREEN "  [OK] Resultados guardados en %s\n" RESET, filename);
    return 0;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf(BOLD WHITE
           "\n==========================================================\n"
           "                BENCHMARK: HEAP SORT V0.0.2\n"
           "==========================================================\n" RESET);

    runBenchmark("ESCENARIO: DATOS ALEATORIOS", "heap-aleatorio.csv", generateRandom);
    runBenchmark("ESCENARIO: DATOS ORDENADOS", "heap-ordenado.csv", generateSorted);
    runBenchmark("ESCENARIO: DATOS INVERTIDOS", "heap-invertido.csv", generateReversed);

    printf(BOLD GREEN "\nPruebas completadas con éxito.\n" RESET);

    return 0;
}