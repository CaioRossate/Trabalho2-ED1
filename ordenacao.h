#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdlib.h>

/**
 * @file ordenacao.h
 * @brief Algoritmos de ordenação para o projeto.
 */

/**
 * @brief Mergesort com otimização usando insertionsort.
 * 
 * @param base Ponteiro para o array
 * @param n Número de elementos
 * @param size Tamanho de cada elemento
 * @param compar Função de comparação
 * @param threshold Limite para usar insertionsort
 */
void mergesort(void *base, size_t n, size_t size, int (*compar)(const void*, const void*), int threshold);

/**
 * @brief Insertionsort para arrays pequenos.
 */
void insertionsort(void *base, size_t n, size_t size, int (*compar)(const void*, const void*));

#endif