# ===== Config =====
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
OPT = -O2

SRC_DIR = src
OBJ_DIR = obj

# ===== Targets =====
.PHONY: all clean test_heap test_radix

# ===== Ejecutable principal (sin tests) =====
MAIN_SRCS = src/main.c src/listas.c src/heapSort.c src/radixSort.c src/util.c

programa.exe: $(MAIN_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

all: programa.exe

# ===== Heap test =====
HEAP_SRCS = src/test_HeapSort.c src/listas.c src/heapSort.c src/util.c

test_heap: clean
	@echo "Compilando test de HeapSort..."
	$(CC) $(CFLAGS) $(OPT) $(HEAP_SRCS) -o test_heap.exe
	./test_heap.exe

# ===== Limpieza =====
clean:
	rm -rf obj *.exe