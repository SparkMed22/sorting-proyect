#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "lists.h"

int getMaxA(int arr[], int n);
void countingSort(int arr[], int n, int exp);
void radixSortArray(int arr[], int n);
void radixSortArrayList(ArrayList* list, int n);

/**
 * LINKED LIST
 */
int getMaxL(Nodo* head);
void enqueue(Nodo** head, Nodo** tail, int value);
void radixSortLinkedList(LinkedList* list, int n);
#endif