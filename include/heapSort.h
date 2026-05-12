/**
 * @file heapSort.h
 * @brief Firma de los metodos para HeapSort
 * @author Francisco Medina 
 * @date 2026-05-04            
 * @version 0.0.1              
 */

#ifndef HEAPSORT_H
#define HEAPSORT_H
/**
 * Estructura externa 
 */
#include "lists.h"

void heapSortArray(int *datos, int cant);

void heapSortArrayList(ArrayList *list, int cant);

void heapSortLinkedList(LinkedList *list, int cant);
#endif