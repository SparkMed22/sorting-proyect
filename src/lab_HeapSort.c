/**
 * @file lab_HeapSort.c
 * @brief Benchmark del algoritmo Heap Sort para distintas estructuras.
 *
 * Evalúa el rendimiento de:
 * - Arrays
 * - ArrayList
 * - LinkedList
 *
 * Tipos de datos evaluados:
 * - Aleatorios
 * - Ordenados
 * - Invertidos
 *
 * Los resultados se exportan en formato CSV.
 *
 * @author Francisco Medina
 * @date 2026-05-12
 * @version 0.0.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heapSort.h"
#include "lab_HeapSort.h"
#include "util.h"
#include "config.h"


static const int sizes[] = {
    100,
    500,
    1000,
    2000,
    5000,
    10000,
    20000,
    50000,
    100000,
    200000,
    500000,
    1000000,
    2000000};

static const int TOTAL_SIZES = sizeof(sizes) / sizeof(sizes[0]);


typedef void (*GeneratorFunction)(int *, int);

/**
 * @brief Copia un arreglo.
 *
 * @param dest Arreglo destino.
 * @param src  Arreglo origen.
 * @param n    Cantidad de elementos.
 */
static void copyArray(int *dest, const int *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

/**
 * @brief Obtiene el tiempo de ejecución de HeapSort para arrays.
 *
 * @param data Arreglo a ordenar.
 * @param n    Cantidad de elementos.
 * @return Tiempo en segundos.
 */
static double benchmarkArray(int *data, int n)
{
    clock_t start = clock();
    heapSortArray(data, n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/**
 * @brief Obtiene el tiempo de ejecución de HeapSort para ArrayList.
 *
 * @param data Datos base.
 * @param n    Cantidad de elementos.
 * @return Tiempo en segundos.
 */
static double benchmarkArrayList(const int *data, int n)
{
    ArrayList *list = arraylist_create(n);
    for (int i = 0; i < n; i++) 
        arraylist_push(list, data[i]);
    
    clock_t start = clock();
    heapSortArrayList(list, n);
    clock_t end = clock();
    arraylist_free(list);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

/**
 * @brief Obtiene el tiempo de ejecución de HeapSort para LinkedList.
 *
 * @param data Datos base.
 * @param n    Cantidad de elementos.
 * @return Tiempo en segundos.
 */
static double benchmarkLinkedList(const int *data, int n)
{

    LinkedList *list = linkedlist_create();

    for (int i = 0; i < n; i++)
    {
        linkedlist_add(list, data[i]);
    }

    clock_t start = clock();

    heapSortLinkedList(list, n);

    clock_t end = clock();

    linkedlist_free(list);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

/**
 * @brief Ejecuta un benchmark completo.
 *
 * @param title      Nombre descriptivo.
 * @param filename   Archivo CSV de salida.
 * @param generator  Función generadora de datos.
 *
 * @return 0 si todo salió correctamente.
 */
static int runBenchmark(
    const char *title,
    const char *filename,
    GeneratorFunction generator)
{

    FILE *file = fopen(filename, "w");

    if (!file)
    {
        printf(RED BOLD "\n[ERROR]" RESET RED
                        " No se pudo crear el archivo %s\n" RESET,
               filename);
        return 1;
    }

    fprintf(file, "size,array_time,arraylist_time,linkedlist_time\n");

    printf(BOLD CYAN "\n==================================================\n" RESET);
    printf(BOLD BLUE " %s\n" RESET, title);
    printf(BOLD CYAN "==================================================\n\n" RESET);

    for (int s = 0; s < TOTAL_SIZES; s++)
    {

        int n = sizes[s];

        printf(YELLOW "[%2d/%2d]" RESET
                      " Procesando %s%d%s elementos...\n",
               s + 1,
               TOTAL_SIZES,
               CYAN,
               n,
               RESET);

        int *base = malloc(sizeof(int) * n);
        int *array = malloc(sizeof(int) * n);

        if (!base || !array)
        {

            printf(RED BOLD "\n[ERROR]" RESET RED
                            " Memoria insuficiente para n=%d\n" RESET,
                   n);

            free(base);
            free(array);
            fclose(file);

            return 1;
        }

        generator(base, n);

        copyArray(array, base, n);

        double timeArray = benchmarkArray(array, n);

        double timeArrayList = benchmarkArrayList(base, n);

        double timeLinkedList = benchmarkLinkedList(base, n);

        fprintf(file,
                "%d,%f,%f,%f\n",
                n,
                timeArray,
                timeArrayList,
                timeLinkedList);

        printf(
            GREEN "  Array      :" RESET " %.6f s\n" BLUE "  ArrayList  :" RESET " %.6f s\n" CYAN "  LinkedList :" RESET " %.6f s\n\n",
            timeArray,
            timeArrayList,
            timeLinkedList);

        free(base);
        free(array);
    }

    fclose(file);

    printf(GREEN BOLD
           "[OK] Resultados guardados en %s\n" RESET,
           filename);

    return 0;
}

int main(void)
{

    srand((unsigned int)time(NULL));

    printf(BOLD WHITE
           "\n========================================\n"
           "         HEAP SORT BENCHMARK\n"
           "========================================\n" RESET);

    runBenchmark(
        "DATOS ALEATORIOS",
        "heap-aleatorio-results.csv",
        generateRandom);

    runBenchmark(
        "DATOS ORDENADOS",
        "heap-ordenado-results.csv",
        generateSorted);

    runBenchmark(
        "DATOS INVERTIDOS",
        "heap-invertido-results.csv",
        generateReversed);

    printf(BOLD GREEN
           "\nBenchmark finalizado correctamente.\n" RESET);

    return 0;
}