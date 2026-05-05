/**
 * Laboratorio de Radix 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listas.h"
#include "radixSort.h"
#include "util.h"

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

int benchmark_radix_sort() {
	srand(time(NULL));


	FILE *file = fopen("radix-results.csv", "w");
    if (!file) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Header CSV
    fprintf(file, "size, array_time, arraylist_time, linkedlist_time\n");

    for (int s = 0; s < size; s++) {
    	int n = sizes[s];

    	//int* data = malloc(n * sizeof(int));
   		//generarAleatorio(data, n);
    	
    	/* =========
			 ARRAY
   	   	   ========= */    	
    	int array[n];
    	generarAleatorio(array, n);

    	clock_t start = clock();
    	radixSortArray(array, n);
    	clock_t end = clock();

    	double time_array = (double)(end - start) / CLOCKS_PER_SEC;


        /* ==============
             ARRAY LIST
           ============== */
    	int* data = malloc(n * sizeof(int));
   		generarAleatorio(data, n);

   		ArrayList* arrayList = arraylist_create(n);

   		for (int i = 0; i < n; i++) {
   			arraylist_push(arrayList, data[i]);
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
            linkedlist_add(list, data[i]);
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
        free(data);
    }

    fclose(file);

    printf("\nResultados guardados en radix-results.csv\n");

    return 0;
}

int main(){
	return benchmark_radix_sort();
}