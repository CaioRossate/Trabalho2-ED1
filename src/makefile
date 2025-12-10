# Nome do executável
TARGET = ted

# Nome do aluno
ALUNO = CaioER

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

# Diretórios
SRC_DIR = .
BUILD_DIR = ./build

# Lista de arquivos de origem e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(TARGET)

# Regra de compilação dos arquivos de objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de compilação do executável
$(TARGET): $(OBJS)
	@echo "Linkando $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm 

# Limpeza de arquivos intermediários e o executável
clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean