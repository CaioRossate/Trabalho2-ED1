#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * @file poligono.h
 * @brief Definições do TAD Polígono genérico, implementado com lista encadeada.
 * 
 * @details
 * O Polígono é uma estrutura que armazena uma sequência de pontos (vértices) que definem a forma geométrica.
 * Cada ponto é representado por suas coordenadas x e y.
 */
typedef void *POLIGONO; // Tipo opaco para o Polígono

/**
 * @brief Cria e inicializa um novo Polígono vazio.
 * @return Um ponteiro para o POLIGONO criado.
 * @warning Encerra o programa com `exit(1)` se não for possível alocar memória.
 */
POLIGONO criaPoligono();

/**
 * @brief Adiciona um vértice ao Polígono.
 * @param p O Polígono onde o vértice será adicionado.
 * @param x A coordenada x do vértice.
 * @param y A coordenada y do vértice.
 */
void adicionaVertice(POLIGONO p, double x, double y);

/**
 * @brief Adiciona um segmento ao Polígono.
 * @param p O Polígono onde o segmento será adicionado.
 * @details
 * O segmento é definido pelos dois últimos vértices adicionados ao Polígono.
 * Se houver menos de dois vértices, a função não faz nada.
 */
void adicionaSegmento(POLIGONO p);

/**
 * @brief Obtém o número de vértices do Polígono que cobre a area.
 * @param p O Polígono em volta.
 * @return O número de vértices no Polígono que cobre a area.
 */
int getBoundingBox(POLIGONO p, double *minX, double *minY, double *maxX, double *maxY);

/**
 * @brief Obtém as coordenadas do vértice no índice especificado.
 * @param p O Polígono a ser consultado.
 * @param indice O índice do vértice (0-based).
 * @param x Ponteiro para armazenar a coordenada x do vértice.
 * @param y Ponteiro para armazenar a coordenada y do vértice.
 * @warning Comportamento indefinido se o índice for inválido.
 */
void obtemVertice(POLIGONO p, int indice, double *x, double *y);

/**
 * @brief Libera a memória alocada para o Polígono.
 * @param p O Polígono a ser liberado.
 */
void liberaPoligono(POLIGONO p);

/**
 * @brief Verifica se um ponto está dentro do Polígono.
 * @param p O Polígono a ser consultado.
 * @param x A coordenada x do ponto.
 * @param y A coordenada y do ponto.
 * @return true se o ponto estiver dentro do Polígono, false caso contrário.
 */
bool isInside(POLIGONO p, double x, double y);

/**
 * @brief Obtém o número de vértices do polígono.
 * @param p O Polígono a ser consultado.
 * @return O número de vértices.
 */
int getNumVertices(POLIGONO p);

/**
 * @brief Obtém o primeiro vértice para iteração.
 * @param p O Polígono.
 * @return Ponteiro opaco para o primeiro vértice.
 */
void* getPrimeiroVertice(POLIGONO p);

/**
 * @brief Obtém o próximo vértice para iteração.
 * @param v Ponteiro para o vértice atual.
 * @return Ponteiro opaco para o próximo vértice.
 */
void* getProximoVertice(void *v);

/**
 * @brief Obtém as coordenadas de um vértice.
 * @param v Ponteiro para o vértice.
 * @param x Ponteiro para armazenar coordenada x.
 * @param y Ponteiro para armazenar coordenada y.
 */
void getCoordenadaVertice(void *v, double *x, double *y);




#endif