#include "util.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void generarAleatorio(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

void probarAlgoritmo(void (*sort)(int[], int), int arr[], int n, char* nombre) {
    clock_t inicio = clock();

    sort(arr, n);

    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("%s -> Tiempo: %f segundos\n", nombre, tiempo);
}
