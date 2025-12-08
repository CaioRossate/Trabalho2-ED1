#ifndef LINHA_H
#define LINHA_H

#include <stdlib.h>
#include <math.h> 

/**
 * @file linha.h
 * @brief Definições do TAD Linha (formato em SVG).
 *
 * @details
 * O arquivo linha.h declara um tipo abstrato de dado para representar uma linha em um plano 2D,
 * juntamente com funções para criar, acessar, modificar e desalocar linhas.
 */

typedef void *LINHA; // Tipo opaco para LINHA

/**
 * @brief Cria uma linha com os atributos especificados.
 *
 * @param id Identificador único da linha.
 * @param x1 Coordenada x1 (ponto inicial).
 * @param y1 Coordenada y1 (ponto inicial).
 * @param x2 Coordenada x2 (ponto final).
 * @param y2 Coordenada y2 (ponto final).
 * @param cor Cor da linha.
 * @return Um ponteiro para o objeto `LINHA` criado.
 */
LINHA criaLinha(int id, double x1, double y1, double x2, double y2, const char *cor);

/**
 * @brief Libera a memória alocada para a linha e suas strings internas.
 * @param l O TAD LINHA a ser destruído.
 */
void destroiLinha(LINHA l);


/**
 * @brief Obtém o id da linha.
 * @param l A linha do qual será pego o id.
 * @return O id da forma. 
 */
int getIdLinha (LINHA l);

/**
 * @brief Obtém o valor da coordenada x1 da linha.
 * @param l A linha do qual será pego a coordenada x1.
 * @return A coordenada x1 da forma. 
 */
double getX1Linha(LINHA l);

/**
 * @brief Obtém o valor da coordenada y1 da linha.
 * @param l A linha do qual será pego a coordenada y1.
 * @return A coordenada y1 da forma. 
 */
double getY1Linha(LINHA l);

/**
 * @brief Obtém o valor da coordenada x2 da linha.
 * @param l A linha do qual será pego a coordenada x2.
 * @return A coordenada x2 da forma. 
 */
double getX2Linha(LINHA l);

/**
 * @brief Obtém o valor da coordenada y2 da linha.
 * @param l A linha do qual será pego a coordenada y2.
 * @return A coordenada y2 da forma. 
 */
double getY2Linha(LINHA l);

/**
 * @brief Obtém a cor da linha.
 * @param l A linha do qual será pego a cor.
 * @return Uma string com a cor da forma. 
 */
char *getCorLinha(LINHA l);

/**
 * @brief Calcula a área da linha (2.0 * comprimento).
 * @param x1 Coordenada x1 da linha.
 * @param x2 Coordenada x2 da linha.
 * @param y1 Coordenada y1 da linha.
 * @param y2 Coordenada y2 da linha.
 * @return O valor da área da forma. 
 */
double calculaAreaLinha(double x1, double y1, double x2, double y2);


/**
 * @brief Define o valor da coordenada x1 da linha.
 * @param l A linha do qual será definido a coordenada x1.
 * @param x1 O novo valor para a coordenada x1.
 */
void definirX1Linha(LINHA l, double x1);

/**
 * @brief Define o valor da coordenada y1 da linha.
 * @param l A linha do qual será definido a coordenada y1.
 * @param y1 O novo valor para a coordenada y1.
 */
void definirY1Linha(LINHA l, double y1);

/**
 * @brief Define o valor da coordenada x2 da linha.
 * @param l A linha do qual será definido a coordenada x2.
 * @param x2 O novo valor para a coordenada x2.
 */
void definirX2Linha(LINHA l, double x2);

/**
 * @brief Define o valor da coordenada y2 da linha.
 * @param l A linha do qual será definido a coordenada y2.
 * @param y2 O novo valor para a coordenada y2.
 */
void definirY2Linha(LINHA l, double y2);

/**
 * @brief Define o valor da cor da linha.
 * @param l A linha do qual será definido a cor.
 * @param cor O novo valor para a cor.
 */
void definirCorLinha(LINHA l, const char *cor);

#endif