/**
 * Laboratorio de Radix 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listas.h"
#include "radixSort.h"
#include "util.h"
#include "test_RadixSort.h"

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
int size = 13;

int radix_sort_random() {
	srand(time(NULL));

	FILE *file = fopen("radix-aleatorio-results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Header CSV
    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
    	int n = sizes[s];

    	// Base
    	int* base = malloc(n * sizeof(int));
    	generateRandom(base, n);

    	/* =========
			 ARRAY
   	   	   ========= */    	
    	int array[n];
    	for (int i = 0; i < n; i++) {
    		array[i] = base[i];
    	}

    	clock_t start = clock();
    	radixSortArray(array, n);
    	clock_t end = clock();

    	double time_array = (double)(end - start) / CLOCKS_PER_SEC;


        /* ==============
             ARRAY LIST
           ============== */
   		ArrayList* arrayList = arraylist_create(n);

   		for (int i = 0; i < n; i++) {
   			arraylist_push(arrayList, base[i]);
   		}

   	   	start = clock();
    	radixSortArrayList(arrayList, n);
    	end = clock();

    	double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;
    

    	/* ===============
             LINKED LIST
           =============== */
        LinkedList *list = linkedlist_create();

        for (int i = 0; i < n; i++) {
            linkedlist_add(list, base[i]);
        }

        start = clock();
        radixSortLinkedList(list);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        /* ===============
             GUARDAR CSV
           =============== */
        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);


        /* liberar memoria */
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);

    printf("\nResultados guardados en radix-aleatorio-results.csv\n");

    return 0;
}


int radix_sort_sorted() {
	srand(time(NULL));

	FILE *file = fopen("radix-ordenado-results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Header CSV
    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
    	int n = sizes[s];

    	// Base
    	int* base = malloc(n * sizeof(int));
    	generateSorted(base, n);

    	/* =========
			 ARRAY
   	   	   ========= */    	
    	int array[n];
    	for (int i = 0; i < n; i++) {
    		array[i] = base[i];
    	}

    	clock_t start = clock();
    	radixSortArray(array, n);
    	clock_t end = clock();

    	double time_array = (double)(end - start) / CLOCKS_PER_SEC;


        /* ==============
             ARRAY LIST
           ============== */
   		ArrayList* arrayList = arraylist_create(n);

   		for (int i = 0; i < n; i++) {
   			arraylist_push(arrayList, base[i]);
   		}

   	   	start = clock();
    	radixSortArrayList(arrayList, n);
    	end = clock();

    	double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;
    

    	/* ===============
             LINKED LIST
           =============== */
        LinkedList *list = linkedlist_create();

        for (int i = 0; i < n; i++) {
            linkedlist_add(list, base[i]);
        }

        start = clock();
        radixSortLinkedList(list);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        /* ===============
             GUARDAR CSV
           =============== */
        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);


        /* liberar memoria */
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);

    printf("\nResultados guardados en radix-ordenado-results.csv\n");

    return 0;
}


int radix_sort_reversed() {
	srand(time(NULL));

	FILE *file = fopen("radix-invertido-results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Header CSV
    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
    	int n = sizes[s];

    	// Base
    	int* base = malloc(n * sizeof(int));
    	generateReversed(base, n);

    	/* =========
			 ARRAY
   	   	   ========= */    	
    	int array[n];
    	for (int i = 0; i < n; i++) {
    		array[i] = base[i];
    	}

    	clock_t start = clock();
    	radixSortArray(array, n);
    	clock_t end = clock();

    	double time_array = (double)(end - start) / CLOCKS_PER_SEC;


        /* ==============
             ARRAY LIST
           ============== */
   		ArrayList* arrayList = arraylist_create(n);

   		for (int i = 0; i < n; i++) {
   			arraylist_push(arrayList, base[i]);
   		}

   	   	start = clock();
    	radixSortArrayList(arrayList, n);
    	end = clock();

    	double time_arrayList = (double)(end - start) / CLOCKS_PER_SEC;
    

    	/* ===============
             LINKED LIST
           =============== */
        LinkedList *list = linkedlist_create();

        for (int i = 0; i < n; i++) {
            linkedlist_add(list, base[i]);
        }

        start = clock();
        radixSortLinkedList(list);
        end = clock();

        double time_linkedList = (double)(end - start) / CLOCKS_PER_SEC;

        /* ===============
             GUARDAR CSV
           =============== */
        fprintf(file, "%d, %f, %f, %f\n", n, time_array, time_arrayList, time_linkedList);

        printf("n=%d | Array=%.6f | ArrayList=%.6f | LinkedList=%.6f\n",
               n, time_array, time_arrayList, time_linkedList);


        /* liberar memoria */
        arraylist_free(arrayList);
        linkedlist_free(list);
        free(base);
    }

    fclose(file);

    printf("\nResultados guardados en radix-invertido-results.csv\n");

    return 0;
}

int main() {

    printf("\nRadix Sort - Aleatorio\n");
    radix_sort_random();

    printf("\nRadix Sort - Ordenado\n");
    radix_sort_sorted();

    printf("\nRadix Sort - Inverso\n");
    radix_sort_reversed();

    return 0;
}
