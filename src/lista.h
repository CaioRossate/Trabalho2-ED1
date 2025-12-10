#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

/**
 * @file lista.h
 * @brief TAD Lista encadeada genérica.
 * 
 * @details
 * Lista duplamente encadeada que armazena ponteiros genéricos (void*).
 * Cada nó também pode ter um tipo associado (char) para diferenciar tipos de dados.
 */

typedef void* LISTA;

/**
 * @brief Cria uma lista vazia.
 * @return Ponteiro opaco para a lista criada
 */
LISTA criaLista();

/**
 * @brief Destroi a lista, liberando memória.
 * @details NÃO libera os dados armazenados, apenas os nós da lista.
 * @param lista Lista a ser destruída
 */
void destroiLista(LISTA lista);

/**
 * @brief Verifica se a lista está vazia.
 * @param lista Lista a verificar
 * @return true se vazia, false caso contrário
 */
bool listaVazia(LISTA lista);

/**
 * @brief Insere um dado no final da lista.
 * @param lista Lista
 * @param dado Ponteiro para o dado a inserir
 * @param tipo Tipo do dado (opcional, use '\0' se não usar)
 */
void insereLista(LISTA lista, void *dado, char tipo);

/**
 * @brief Insere um dado no início da lista.
 * @param lista Lista
 * @param dado Ponteiro para o dado a inserir
 * @param tipo Tipo do dado (opcional)
 */
void insereInicioLista(LISTA lista, void *dado, char tipo);

/**
 * @brief Remove e retorna o primeiro elemento da lista.
 * @param lista Lista
 * @return Ponteiro para o dado removido, ou NULL se lista vazia
 */
void* removePrimeiroLista(LISTA lista);

/**
 * @brief Remove e retorna o último elemento da lista.
 * @param lista Lista
 * @return Ponteiro para o dado removido, ou NULL se lista vazia
 */
void* removeUltimoLista(LISTA lista);

/**
 * @brief Remove um nó específico da lista.
 * @param lista Lista
 * @param no Ponteiro para o nó a remover
 * @return Ponteiro para o dado que estava no nó
 */
void* removeNoLista(LISTA lista, void *no);

/**
 * @brief Obtém o primeiro nó da lista.
 * @param lista Lista
 * @return Ponteiro opaco para o primeiro nó, ou NULL se vazia
 */
void* obtemPrimeiroNo(LISTA lista);

/**
 * @brief Obtém o último nó da lista.
 * @param lista Lista
 * @return Ponteiro opaco para o último nó, ou NULL se vazia
 */
void* obtemUltimoNo(LISTA lista);

/**
 * @brief Obtém o próximo nó.
 * @param no Nó atual
 * @return Ponteiro para o próximo nó, ou NULL se for o último
 */
void* obtemProximoNo(void *no);

/**
 * @brief Obtém o nó anterior.
 * @param no Nó atual
 * @return Ponteiro para o nó anterior, ou NULL se for o primeiro
 */
void* obtemAnteriorNo(void *no);

/**
 * @brief Obtém o dado armazenado em um nó.
 * @param no Nó
 * @return Ponteiro para o dado
 */
void* obtemDado(void *no);

/**
 * @brief Obtém o tipo do dado armazenado em um nó.
 * @param no Nó
 * @return Tipo do dado (char)
 */
char obtemTipo(void *no);

/**
 * @brief Define o dado de um nó.
 * @param no Nó
 * @param dado Novo dado
 */
void setDado(void *no, void *dado);

/**
 * @brief Define o tipo de um nó.
 * @param no Nó
 * @param tipo Novo tipo
 */
void setTipo(void *no, char tipo);

/**
 * @brief Obtém o número de elementos na lista.
 * @param lista Lista
 * @return Número de elementos
 */
int obtemTamanhoLista(LISTA lista);

/**
 * @brief Busca um dado na lista usando função de comparação.
 * @param lista Lista
 * @param chave Chave de busca
 * @param compara Função de comparação (retorna 0 se igual)
 * @return Ponteiro para o nó encontrado, ou NULL se não encontrado
 */
void* buscaLista(LISTA lista, void *chave, int (*compara)(void*, void*));

#endif