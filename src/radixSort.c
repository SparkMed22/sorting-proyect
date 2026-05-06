#include "radixSort.h"
#include <stdlib.h>


/* ==========================
    AUXILIARES ARRAY
   ========================== */

// Obtiene el valor numero de un array
int getMaxA(int arr[], int n) {
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

/* ===================
    RADIX SORT ARRAY
   =================== */

void radixSortArray(int arr[], int n) {
    if (n <= 1) return;

    int max = getMaxA(arr, n);

    // Aplicar countingSort para cada digito
    for (int exp = 1; (max /exp) > 0; exp *= 10) {
    	countingSort(arr, n, exp);
    }
}


/* =======================
    RADIX SORT ARRAYLIST
   ======================= */
void radixSortArrayList(ArrayList* list, int n) {
    NOT_NULL(list);

    if (n <= 1) return;

    radixSortArray(list->data, n);
}


/* ======================
   RADIX SORT LINKEDLIST
   ====================== */

int getMaxL(Nodo* head) {
    int max = head->value;

    while( head != NULL) {
        if ( head->value > max ) {
            max = head->value;
        }
        head = head->next;
    }
    return max;
}

void enqueue(Nodo** head, Nodo** tail, int value) {
    Nodo* new_nodo = nodo_create(value);

    if (*head == NULL) {
        *head = new_nodo;
    } else {
        (*tail)->next = new_nodo;
    }
    *tail = new_nodo;
}


void radixSortLinkedList(LinkedList* list, int n){
    NOT_NULL(list);

    if( n <= 1) return;

    int max = getMaxL(list->head);

    for (int exp = 1;  (max / exp) > 0; exp *= 10) {

        Nodo* buckets[10] = {NULL};
        Nodo* tails[10] = {NULL};

        Nodo* curr = list->head;

        // Distribuir en buckets
        while (curr != NULL) {
            int digit = (curr->value / exp) % 10;

            enqueue(&buckets[digit], &tails[digit], curr->value);

            Nodo* temp = curr;
            curr = curr->next;
            free(temp);
        }

        list->head = NULL;
        list->tail = NULL;

        for (int i = 0; i < 10; i++) {
            if(buckets[i] != 0) {
                if(list->head == NULL) {
                    list->head = buckets[i];
                } else {
                    list->tail->next = buckets[i];
                }
                list->tail = buckets[i];
            }
        }
    }
}