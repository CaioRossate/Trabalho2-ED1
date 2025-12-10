#ifndef ANTEPARO_H
#define ANTEPARO_H

/**
 * @file anteparo.h
 * @brief TAD para anteparos (segmentos bloqueantes).
 * 
 * @details
 * Anteparos são segmentos de reta que bloqueiam a propagação das bombas.
 */

typedef void* ANTEPARO;

/**
 * @brief Cria um novo anteparo.
 * @param id Identificador único do anteparo
 * @param x1 Coordenada X da primeira extremidade
 * @param y1 Coordenada Y da primeira extremidade
 * @param x2 Coordenada X da segunda extremidade
 * @param y2 Coordenada Y da segunda extremidade
 * @param cor Cor do anteparo (string SVG)
 * @return Ponteiro opaco para o anteparo criado
 */
ANTEPARO criaAnteparo(int id, double x1, double y1, double x2, double y2, const char *cor);

/**
 * @brief Destroi um anteparo, liberando memória.
 * @param anteparo Anteparo a ser destruído
 */
void destroiAnteparo(ANTEPARO anteparo);

/**
 * @brief Obtém o ID do anteparo.
 */
int getIdAnteparo(ANTEPARO anteparo);

/**
 * @brief Obtém a coordenada X da primeira extremidade.
 */
double getX1Anteparo(ANTEPARO anteparo);

/**
 * @brief Obtém a coordenada Y da primeira extremidade.
 */
double getY1Anteparo(ANTEPARO anteparo);

/**
 * @brief Obtém a coordenada X da segunda extremidade.
 */
double getX2Anteparo(ANTEPARO anteparo);

/**
 * @brief Obtém a coordenada Y da segunda extremidade.
 */
double getY2Anteparo(ANTEPARO anteparo);

/**
 * @brief Obtém a cor do anteparo.
 */
char* getCorAnteparo(ANTEPARO anteparo);

/**
 * @brief Define a cor do anteparo.
 */
void setCorAnteparo(ANTEPARO anteparo, const char *cor);

#endif