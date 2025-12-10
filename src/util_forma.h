#ifndef UTIL_FORMA_H
#define UTIL_FORMA_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/**
 * @file util_forma.h
 * @brief Funções utilitárias para manipulação genérica de formas geométricas.
 * 
 * @details
 * Este módulo fornece funções que trabalham com formas de maneira genérica,
 * usando o tipo char para identificar o tipo específico da forma.
 */

typedef void* FORMA;

/**
 * @brief Obtém a área de uma forma genérica.
 * @param f Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 * @return A área calculada da forma.
 */
float obterAreaForma(FORMA f, char tipo);

/**
 * @brief Destrói uma forma genérica, liberando sua memória.
 * @param f Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 */
void destroiForma(FORMA f, char tipo);

/**
 * @brief Move uma forma aplicando um deslocamento.
 * @param forma Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 * @param dx Deslocamento no eixo X.
 * @param dy Deslocamento no eixo Y.
 */
void moveForma(FORMA forma, char tipo, double dx, double dy);

/**
 * @brief Obtém a coordenada X de uma forma genérica.
 * @param f Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 * @return A coordenada X da forma.
 */
double obtemXforma(FORMA f, char tipo);

/**
 * @brief Obtém a coordenada Y de uma forma genérica.
 * @param f Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 * @return A coordenada Y da forma.
 */
double obtemYforma(FORMA f, char tipo);

/**
 * @brief Obtém o ID de uma forma genérica.
 * @param f Ponteiro para a forma.
 * @param tipo Caractere que identifica o tipo ('c', 'r', 'l', 't').
 * @return O identificador único da forma.
 */
int obtemIDforma(FORMA f, char tipo);

/**
 * @brief Calcula a cor complementar de uma cor hexadecimal.
 * @param cor Cor original em formato hexadecimal (ex: "#FF0000").
 * @param corComplementar Buffer para armazenar a cor complementar (mínimo 8 chars).
 * @details Formato aceito: "#RRGGBB" (7 caracteres). Calcula 255-R, 255-G, 255-B.
 */
void obterCorComplementar(const char *cor, char *corComplementar);

#endif