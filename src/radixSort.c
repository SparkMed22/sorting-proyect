#include "radixSort.h"

// Obtiene el valor maximo dentro de un array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n;i++) {
        if (arr[i] > max) {
	    max = arr[i];
	}
    }
    return max;
}

// Algoritmo Counting sort basado en el digito actual
void countingSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int)); // Arreglo auxiliar
    if (!output) return;
    int count[10] = {0}; // base 10 (0-9)
    
    // Contar ocurrencias de cada digito
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
	count[digit]++;
    }

    // Convertir count[] en posiciones acumuladas
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Construir el arreglo ordenado (recorrer alrevez para estabilidad)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
	output[count[digit] - 1] = arr[i];
    	count[digit]--;
    }

    // Copiar al arreglo original
    for (int i = 0; i < n; i++) {
    	arr[i] = output[i];
    }
    free(output);
}


void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    // Aplicar countingSort para cada digito
    for (int exp = 1; (max /exp) > 0; exp *= 10) {
    	countingSort(arr, n, exp);
    }
}
