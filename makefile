CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -O2

SRC_DIR = src
OBJ_DIR = obj

BASE_SRCS = src/listas.c src/util.c

HEAP_SRCS = src/heapSort.c src/lab_HeapSort.c
RADIX_SRCS = src/radixSort.c src/lab_RadixSort.c
QUICK_SRCS = src/quickSort.c src/lab_QuickSort.c 
MAIN_SRCS = src/main.c  src/heapSort.c src/radixSort.c

.PHONY: all clean lab_heap lab_radix run_main

programa.exe: $(MAIN_SRCS) $(BASE_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

all: programa.exe

lab_heap: $(BASE_SRCS) $(HEAP_SRCS)
	@echo ">>> Compilando pruebas de HeapSort..."
	$(CC) $(CFLAGS) $(HEAP_SRCS) $(BASE_SRCS) -o lab_heap.exe
	@echo ">>> Ejecutando lab_heap.exe..."
	./lab_heap.exe

lab_radix: $(BASE_SRCS) $(RADIX_SRCS)
	@echo ">>> Compilando pruebas de RadixSort..."
	$(CC) $(CFLAGS) $(RADIX_SRCS) $(BASE_SRCS) -o lab_radix.exe
	@echo ">>> Ejecutando lab_radix.exe..."
	./lab_radix.exe

lab_Quick: $(BASE_SRCS) $(QUICK_SRCS)
	@echo ">>> Compilando pruebas de QuickSort..."
	$(CC) $(CFLAGS) $(QUICK_SRCS) $(BASE_SRCS) -o lab_Quick.exe
	@echo ">>> Ejecutando lab_Quick.exe..."
	./lab_Quick.exe


run_main: programa.exe
	@echo ">>> Ejecutando programa principal (main.c)..."
	./programa.exe

clear:
	rm -f *.exe
	rm -rf obj
	rm -f *.csv
	@echo "Limpieza completada."