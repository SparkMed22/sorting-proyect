#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "listas.h"

/* =======================
	ARRAY y ARRAY LIST
   ======================= */
// Funcion para obtener el valor maximo del Array o Array List
int getMaxA(int arr[], int n);

// CountingSort basado en el digito actual
void countingSort(int arr[], int n, int exp);

// Funcion Radix Sort Array
void radixSortArray(int arr[], int n);

// Funcion Radix Sort ArrayList
void radixSortArrayList(ArrayList* list, int n);

/* =============
	LINKED LIST
   ============= */
// Funcion para obtener el valor maximo de la Linked List
int getMaxL(Nodo* head);

// Funcion para encolar
void enqueue(Nodo** head, Nodo** tail, int value);

// Funcion Radix Sort LinkedList
void radixSortLinkedList(LinkedList* list, int n);

#endif