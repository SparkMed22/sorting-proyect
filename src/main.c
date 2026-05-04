#include "listas.h"
#include "heapSort.h"


int main() {
    // Ejemplo con LinkedList
    LinkedList *L = createLinkedList();
    addLinkedList(L, 50);
    addLinkedList(L, 10);
    addLinkedList(L, 30);

    printf("Lista original: ");
    printLinkedList(L);
    
    heapSortLinkedList(L);
    
    printf("Lista ordenada: ");
    printLinkedList(L);

    // Ejemplo con ArrayList
    ArrayList *A = initArrayList(5);
    int v1 = 100, v2 = 20, v3 = 80;
    push(A, &v1);
    push(A, &v2);
    push(A, &v3);

    heapSortArrayList(A);
    
    printf("ArrayList ordenado: %d, %d, %d\n", 
            *(int*)get(A, 0), *(int*)get(A, 1), *(int*)get(A, 2));

    return 0;
}