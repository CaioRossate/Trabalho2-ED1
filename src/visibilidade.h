#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

#include "poligono.h"
#include "lista.h"

/**
 * @file visibilidade.h
 * @brief Algoritmo de cálculo do polígono de visibilidade.
 * 
 * @details
 * Implementa o algoritmo de sweep line angular para calcular a região visível
 * a partir de um ponto, considerando obstáculos (anteparos/segmentos).
 * 
 */

/**
 * @brief Calcula o polígono de visibilidade a partir de um ponto.
 * 
 * @param x Coordenada X do ponto de observação (origem da bomba)
 * @param y Coordenada Y do ponto de observação
 * @param anteparos Lista de segmentos que bloqueiam a visão
 * @param tipoOrdenacao 'q' para qsort, 'm' para mergesort
 * @param threshold Threshold para insertionsort no mergesort
 * @return Polígono de visibilidade calculado
 */
POLIGONO calculaVisibilidade(double x, double y, LISTA anteparos, char tipoOrdenacao, int threshold);

/**
 * @brief Verifica se um ponto está dentro do polígono de visibilidade.
 * 
 * @param poli Polígono de visibilidade
 * @param x Coordenada X do ponto
 * @param y Coordenada Y do ponto
 * @return true se o ponto está visível, false caso contrário
 */
bool pontoVisivel(POLIGONO poli, double x, double y);

#endif