# Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN = main

# Fontes e objetos
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/TAD_GeradorMapa.c \
      $(SRC_DIR)/TAD_Mapa.c \
      $(SRC_DIR)/TAD_Nave.c

OBJ = $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/TAD_GeradorMapa.o \
      $(OBJ_DIR)/TAD_Mapa.o \
      $(OBJ_DIR)/TAD_Nave.o

# Detecta sistema operacional (para nome do executável)
ifeq ($(OS),Windows_NT)
    EXE = $(BIN).exe
else
    EXE = $(BIN)
endif

# Regra padrão
all: $(EXE)

# Linkagem final
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compilação dos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza (Linux e Windows)
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJ_DIR)\*.o $(EXE)
else
	rm -f $(OBJ_DIR)/*.o $(EXE)
endif

# Recompila tudo
rebuild: clean all
