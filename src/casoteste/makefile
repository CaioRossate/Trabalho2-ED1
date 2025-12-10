CC = gcc

CFLAGS = -Wall -Wextra -g -std=c99
INCLUDES = -I.. -I.

# Diretório de build (dentro de testes/)
BUILD_DIR = build

# Diretório dos arquivos fonte (um nível acima)
SRC_DIR = ..

# Alvos dos testes
TARGETS = teste_lista teste_ordenacao

# Objetos dos testes
TEST_OBJS = $(BUILD_DIR)/teste_lista.o \  $(BUILD_DIR)/teste_ordenacao.o

# Objetos das bibliotecas (compilados do diretório pai)
LIB_OBJS = $(BUILD_DIR)/lista.o $(BUILD_DIR)/ordenacao.o 

# Objetos específicos para cada teste
OBJS_LISTA = $(BUILD_DIR)/teste_lista.o $(BUILD_DIR)/lista.o
OBJS_ORDENA = $(BUILD_DIR)/teste_ordenacao.o $(BUILD_DIR)/ordenacao.o

all: $(TARGETS)

# Regra para teste_lista
teste_lista: $(OBJS_LISTA)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para teste_ordenacao
teste_ordenacao: $(OBJS_ORDENA)
	$(CC) $(CFLAGS) $^ -o $@

# Cria o diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para compilar os arquivos de teste (desta pasta)
$(BUILD_DIR)/teste_%.o: teste_%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regra para compilar os arquivos fonte do diretório pai
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean all run_tests help

clean:
	rm -f $(TARGETS)
	rm -rf $(BUILD_DIR)

# Executa todos os testes
run_tests: all
	@echo "========================================="
	@echo "Executando teste_lista..."
	@echo "========================================="
	@./teste_lista
	@echo ""
	@echo "========================================="
	@echo "Executando teste_ordenacao..."
	@echo "========================================="
	@./teste_ordenacao
	@echo ""
	@echo "========================================="
	@echo "TODOS OS TESTES CONCLUÍDOS!"
	@echo "========================================="

# Mostra ajuda
help:
	@echo "Makefile para testes unitários"
	@echo ""
	@echo "Alvos disponíveis:"
	@echo "  make              - Compila todos os testes"
	@echo "  make teste_lista  - Compila apenas teste_lista"
	@echo "  make teste_ordenacao - Compila apenas teste_ordenacao"
	@echo "  make run_tests    - Compila e executa todos os testes"
	@echo "  make clean        - Remove executáveis e build/"
	@echo "  make help         - Mostra esta mensagem"