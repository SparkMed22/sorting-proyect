#include "listas.h"


#define CONFIRM_NOTNULL(ptr, ret) if (!(ptr)) return ret

ArrayList* initArrayList(int cap) {
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    CONFIRM_NOTNULL(list, NULL);

    int cap_seg = (cap <= 0) ? 5 : cap;
    list->arr = (void **)malloc(sizeof(void *) * cap_seg);
    
    if (!list->arr) {
        free(list);
        return NULL;
    }

    list->cap = cap_seg;
    list->size = 0;
    return list;
}

static Bool _expand(ArrayList *list) {
    int new_cap = list->cap * 2;
    void **new_arr = realloc(list->arr, sizeof(void *) * new_cap);
    CONFIRM_NOTNULL(new_arr, FALSE);
    
    list->arr = new_arr;
    list->cap = new_cap;
    return TRUE;
}

Bool push(ArrayList *list, void *element) {
    CONFIRM_NOTNULL(list, FALSE);

    if (list->size == list->cap) {
        if (!_expand(list)) return FALSE;
    }

    list->arr[list->size] = element;
    list->size++;
    return TRUE;
}

void* pop(ArrayList *list) {
    if (!list || list->size == 0) return NULL;
    
    list->size--;
    return list->arr[list->size];
}

void* get(ArrayList *list, int index) {
    if (!list || index < 0 || index >= list->size) return NULL;
    return list->arr[index];
}

Bool freeArrayList(ArrayList *list) {
    CONFIRM_NOTNULL(list, FALSE);
    
    // Nota: Esta función libera el arreglo, pero NO los datos 
    // contenidos si estos fueron reservados dinámicamente fuera.
    free(list->arr);
    free(list);
    return TRUE;
}



/**
 * Implementacion de LinkeList
 */

LinkedList *createLinkedList()
{
  LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
  MACRO_NOT_NULL(linkedList);
  linkedList->head = NULL;
  linkedList->size = 0;
  linkedList->ultimo = NULL;
  return linkedList;
}

Nodo *createNodo(int valor)
{
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  MACRO_NOT_NULL(nodo);
  nodo->valor = valor;
  nodo->sig = NULL;
  return nodo;
}

void addLinkedList(LinkedList *list, int valor)
{

  Nodo *nuevo = createNodo(valor);

  if (list->head == NULL)
  {
    list->head = nuevo;
    list->ultimo = nuevo;
  }
  else
  {
    list->ultimo->sig = nuevo;
    list->ultimo = nuevo;
  }
  list->size += 1;
}

void printLinkedList(LinkedList *list)
{
  if (list->head == NULL)
  {
    printf("Lista sin elemento...\n");
  }
  else
  {
    Nodo *nodo = list->head;
    for (int i = 0; i < list->size; i++)
    {
      printf("\nValor agregado es: %d", nodo->valor);
      nodo = nodo->sig;
    }
  }
}


void freeMemory(LinkedList *list) {
    Nodo *actual = list->head;
    while (actual != NULL) {
        Nodo *temp = actual->sig;
        free(actual);
        actual = temp;
    }
    free(list);
}





