#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "anteparo.h" 
#include <stdbool.h>

/**
 * @file geometria.h
 * @brief Funções auxiliares de geometria computacional.
 */

/**
 * @brief Compara dois anteparos em relação a uma linha de varredura.
 * @param ant1 Primeiro anteparo
 * @param ant2 Segundo anteparo
 * @param yRef Coordenada Y da linha de varredura
 * @return < 0 se ant1 está à esquerda, 0 se coincidente, > 0 se à direita
 */
int comparaAnteparos(ANTEPARO ant1, ANTEPARO ant2, double yRef);

/**
 * @brief Calcula a interseção de dois anteparos.
 * @param ant1 Primeiro anteparo
 * @param ant2 Segundo anteparo
 * @param x Ponteiro para armazenar X da interseção
 * @param y Ponteiro para armazenar Y da interseção
 * @return true se os anteparos se intersectam
 */
bool anteparosIntersectam(ANTEPARO ant1, ANTEPARO ant2, double *x, double *y);

/**
 * @brief Verifica se um ponto está dentro de um polígono (ray casting).
 * @param px Coordenada X do ponto
 * @param py Coordenada Y do ponto
 * @param verticesX Array de coordenadas X dos vértices
 * @param verticesY Array de coordenadas Y dos vértices
 * @param numVertices Número de vértices
 * @return true se o ponto está dentro
 */
bool pontoNoPoligono(double px, double py, double *verticesX, double *verticesY, int numVertices);

/**
 * @brief Calcula a distância de um ponto a um anteparo.
 * @param px Coordenada X do ponto
 * @param py Coordenada Y do ponto
 * @param ant Anteparo
 * @return Distância mínima
 */
double distanciaPontoAnteparo(double px, double py, ANTEPARO ant);

#endif