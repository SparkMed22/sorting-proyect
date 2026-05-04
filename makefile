# Nombre del ejecutable final
TARGET = programa.exe

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -g
LDFLAGS = 

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Archivos origen y objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Reglas generales
.PHONY: all clean test test_heap

all: $(TARGET)

# Compilación de objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Enlazado del ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Crear directorio de objetos si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpieza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Tests específicos
test: clean all
	@echo "Compilando test de listas..."
	$(CC) $(CFLAGS) src/main.c src/listas.c -I$(INC_DIR) -o test_listas.exe
	./test_listas.exe

test_heap: clean all
	@echo "Compilando test de heapSort..."
	$(CC) $(CFLAGS) src/mainHeapSort.c src/listas.c src/heapSort.c -I$(INC_DIR) -O2 -o test_heap.exe
	./test_heap.exe

# Depuración (opcional)
debug: CFLAGS += -DDEBUG
debug: clean all