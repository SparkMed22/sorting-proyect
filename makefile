# Nombre del ejecutable final
TARGET = programa

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Listar todos los archivos .c en src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generar la lista de archivos .o a partir de los .c
# Los pondremos en una carpeta 'obj' para mantener limpio el proyecto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla principal: Compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar los archivos objeto (.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio 'obj' si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run