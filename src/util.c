#include "util.h"
#include <stdio.h>
#include <stdlib.h>

/* =======================
      GENERADOR DE DATOS
   ======================= */

/**
 * Genera un arreglo con valores aleatorios
 */
void generateRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

/**
 * Genera un arreglo ordenado ascendentemente
 */
void generateSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

/**
 * Genera un arreglo de orden inverso
 */
void generateReversed(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}