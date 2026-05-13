CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -O2

SRC_DIR = src

BASE_SRCS = $(SRC_DIR)/lists.c $(SRC_DIR)/util.c

HEAP_SRCS  = $(SRC_DIR)/heapSort.c $(SRC_DIR)/lab_HeapSort.c
RADIX_SRCS = $(SRC_DIR)/radixSort.c $(SRC_DIR)/lab_RadixSort.c
QUICK_SRCS = $(SRC_DIR)/quickSort.c $(SRC_DIR)/lab_QuickSort.c

MAIN_SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/heapSort.c \
	$(SRC_DIR)/radixSort.c \
	$(SRC_DIR)/quickSort.c \
	$(BASE_SRCS)

.PHONY: all clear lab_heap lab_radix lab_quick run_main

all: programa.exe

programa.exe: $(MAIN_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

lab_heap: $(BASE_SRCS) $(HEAP_SRCS)
	@echo ">>> Compilando pruebas de HeapSort..."
	$(CC) $(CFLAGS) $^ -o lab_heap.exe
	@echo ">>> Ejecutando lab_heap.exe..."
	./lab_heap.exe

lab_radix: $(BASE_SRCS) $(RADIX_SRCS)
	@echo ">>> Compilando pruebas de RadixSort..."
	$(CC) $(CFLAGS) $^ -o lab_radix.exe
	@echo ">>> Ejecutando lab_radix.exe..."
	./lab_radix.exe

lab_quick: $(BASE_SRCS) $(QUICK_SRCS)
	@echo ">>> Compilando pruebas de QuickSort..."
	$(CC) $(CFLAGS) $^ -o lab_quick.exe
	@echo ">>> Ejecutando lab_quick.exe..."
	./lab_quick.exe

run_main: programa.exe
	@echo ">>> Ejecutando programa principal..."
	./programa.exe

clear:
	rm -f *.exe
	rm -f *.csv
	@echo "Limpieza completada."