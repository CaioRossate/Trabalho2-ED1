#ifndef INTERSECAO_H
#define INTERSECAO_H

#include <stdbool.h>
#include <math.h> 
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "util_forma.h"

/**
 * @brief Verifica se duas formas genéricas se interceptam.
 *
 * @details
 * Esta função utiliza os tipos das formas ('c', 'r', 'l', 't').
 * Assume que 'l' (Linha) e 't' (Texto) são tratados como segmentos de linha.
 *
 * @param formaA Ponteiro opaco (void*) para a primeira forma.
 * @param tipoA Caractere do tipo da primeira forma ('c', 'r', 'l', 't').
 * @param formaB Ponteiro opaco (void*) para a segunda forma.
 * @param tipoB Caractere do tipo da segunda forma ('c', 'r', 'l', 't').
 * @return true se houver interseção, false caso contrário.
 */
bool verificaIntersecao(FORMA formaA, char tipoA, FORMA formaB, char tipoB);


/**
 * @brief Verifica sobreposição entre dois círculos (C-C).
 * @details
 * A colisão ocorre se a distância entre os centros for menor ou igual à soma dos raios.
 * @param c1 O primeiro TAD CIRCULO.
 * @param c2 O segundo TAD CIRCULO.
 * @return true se há colisão.
 */
bool intersecao_circulo_circulo(CIRCULO c1, CIRCULO c2);

/**
 * @brief Verifica sobreposição entre dois retângulos (R-R).
 * @details
 * A colisão ocorre se não houver separação em nenhum dos eixos (X ou Y).
 * @param r1 O primeiro TAD RETANGULO.
 * @param r2 O segundo TAD RETANGULO.
 * @return true se há colisão.
 */
bool intersecao_retangulo_retangulo(RETANGULO r1, RETANGULO r2);

/**
 * @brief Verifica sobreposição entre um círculo e um retângulo (C-R).
 * @details
 * Encontra o ponto mais próximo do centro do círculo que está no retângulo
 * e verifica se a distância até esse ponto é menor que o raio.
 * @param c O TAD CIRCULO.
 * @param r O TAD RETANGULO.
 * @return true se há colisão.
 */
bool intersecao_circulo_retangulo(CIRCULO c, RETANGULO r);

/**
 * @brief Verifica sobreposição entre uma linha/texto e um círculo (L/T-C).
 * @details
 * A colisão ocorre se a menor distância do centro do círculo ao segmento de linha
 * (incluindo as extremidades) for menor ou igual ao raio.
 * @param l O TAD LINHA (ou Texto, que é tratado como linha).
 * @param c O TAD CIRCULO.
 * @return true se há colisão.
 */
bool intersecao_linha_circulo(LINHA l, CIRCULO c);

/**
 * @brief Verifica sobreposição entre uma linha/texto e um retângulo (L/T-R).
 * @details
 * A colisão ocorre se o segmento de linha cruzar alguma das 4 arestas do retângulo
 * ou se estiver totalmente contido nele.
 * @param l O TAD LINHA (ou Texto).
 * @param r O TAD RETANGULO.
 * @return true se há colisão.
 */
bool intersecao_linha_retangulo(LINHA l, RETANGULO r);

/**
 * @brief Verifica sobreposição entre dois segmentos de linha/texto (L/T-L/T).
 * @details
 * A colisão ocorre se os dois segmentos se intersectarem em algum ponto.
 * @param l1 O primeiro TAD LINHA (ou Texto).
 * @param l2 O segundo TAD LINHA (ou Texto).
 * @return true se há colisão.
 */
bool intersecao_linha_linha(LINHA l1, LINHA l2); 

/**
 * @brief Verifica interseção entre texto e círculo
 */
bool intersecao_texto_circulo(TEXTO t, CIRCULO c);

/**
 * @brief Verifica interseção entre texto e retângulo
 */
bool intersecao_texto_retangulo(TEXTO t, RETANGULO r);

/**
 * @brief Verifica interseção entre texto e linha
 */
bool intersecao_texto_linha(TEXTO t, LINHA l);

/**
 * @brief Verifica interseção entre dois textos
 */
bool intersecao_texto_texto(TEXTO t1, TEXTO t2);

#endif