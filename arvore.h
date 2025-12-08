#ifndef ARVORE_H
#define ARVORE_H

#include <stdbool.h>
#include "anteparo.h" 

/**
 * @file arvore.h
 * @brief TAD Árvore Binária de Busca para anteparos ativos no algoritmo de visibilidade.
 * 
 * @details
 * Esta árvore mantém os anteparos ordenados pela coordenada Y na linha de varredura.
 * É usada no algoritmo de visibilidade para determinar qual anteparo é atingido
 * por um raio em determinada direção.
 */

typedef void* ARVORE;

/**
 * @brief Cria uma árvore vazia.
 */
ARVORE criaArvore();

/**
 * @brief Destroi a árvore, liberando memória.
 */
void destroiArvore(ARVORE arvore);

/**
 * @brief Verifica se a árvore está vazia.
 */
bool arvoreVazia(ARVORE arvore);

/**
 * @brief Insere um anteparo na árvore.
 * @param arvore Árvore
 * @param ant Anteparo a inserir
 * @param yReferencia Coordenada Y de referência para ordenação
 */
void insereArvore(ARVORE arvore, ANTEPARO ant, double yReferencia);

/**
 * @brief Remove um anteparo da árvore.
 * @param arvore Árvore
 * @param ant Anteparo a remover
 * @return true se removido com sucesso
 */
bool removeArvore(ARVORE arvore, ANTEPARO ant);

/**
 * @brief Busca o anteparo mais próximo em uma determinada direção.
 * @param arvore Árvore
 * @param x Coordenada X do ponto de origem
 * @param y Coordenada Y do ponto de origem
 * @param angulo Ângulo da direção (em radianos)
 * @return Anteparo encontrado ou NULL
 */
ANTEPARO buscaAnteparoMaisProximo(ARVORE arvore, double x, double y, double angulo);

/**
 * @brief Obtém o número de elementos na árvore.
 */
int tamanhoArvore(ARVORE arvore);

/**
 * @brief Remove todos os elementos da árvore.
 */
void limpaArvore(ARVORE arvore);

#endif