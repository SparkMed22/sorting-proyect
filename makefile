CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -O2

SRC_DIR = src
OBJ_DIR = obj

BASE_SRCS = src/listas.c src/util.c

HEAP_SRCS = src/heapSort.c src/test_HeapSort.c
RADIX_SRCS = src/radixSort.c src/test_RadixSort.c 
MAIN_SRCS = src/main.c  src/heapSort.c src/radixSort.c

.PHONY: all clean test_heap test_radix run_main

programa.exe: $(MAIN_SRCS) $(BASE_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

all: programa.exe

test_heap: $(BASE_SRCS) $(HEAP_SRCS)
	@echo ">>> Compilando pruebas de HeapSort..."
	$(CC) $(CFLAGS) $(HEAP_SRCS) $(BASE_SRCS) -o test_heap.exe
	@echo ">>> Ejecutando test_heap.exe..."
	./test_heap.exe

test_radix: $(BASE_SRCS) $(RADIX_SRCS)
	@echo ">>> Compilando pruebas de RadixSort..."
	$(CC) $(CFLAGS) $(RADIX_SRCS) $(BASE_SRCS) -o test_radix.exe
	@echo ">>> Ejecutando test_radix.exe..."
	./test_radix.exe

run_main: programa.exe
	@echo ">>> Ejecutando programa principal (main.c)..."
	./programa.exe

clean:
	rm -f *.exe
	rm -rf obj
	rm -f *.csv
	@echo "Limpieza completada."