# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Iinclude -Wall -Wextra -O2

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN = main.exe

# Fontes e objetos
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/TAD_Mapa.c $(SRC_DIR)/TAD_Nave.c $(SRC_DIR)/TAD_GeradorMapa.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(BIN)

# Linkagem final
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

# Compilar .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório obj se não existir
$(OBJ_DIR):
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Limpa os arquivos compilados
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN) del $(BIN)

# Executa o programa
run: all
	$(BIN)
