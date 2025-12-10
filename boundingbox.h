#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "anteparo.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

/**
 * @file boundingbox.h
 * @brief Caixa delimitadora (bounding box) para formas geométricas.
 * 
 * @details
 * Implementa o conceito de bounding box (caixa delimitadora mínima) que encapsula
 * geometricamente uma forma. Usada para otimização de cálculos de interseção.
 */

typedef void* BoundingBox;

/**
 * @brief Cria um bounding box simples com as dimensões fornecidas.
 * @param x Coordenada X do canto superior esquerdo
 * @param y Coordenada Y do canto superior esquerdo
 * @param w Largura da caixa
 * @param h Altura da caixa
 * @return Ponteiro opaco para o bounding box criado
 */
BoundingBox criarBB(double x, double y, double w, double h);

/**
 * @brief Destrói um bounding box, liberando sua memória.
 * @param bb Bounding box a ser destruído
 */
void destruirBB(BoundingBox bb);

/**
 * @brief Cria um bounding box a partir de um anteparo.
 * @param a Anteparo que define o bounding box
 * @return Bounding box encapsulador do anteparo
 */
BoundingBox criaBBAnteparo(ANTEPARO a);

/**
 * @brief Cria um bounding box a partir de um círculo.
 * @param c Círculo que define o bounding box
 * @return Bounding box encapsulador do círculo
 */
BoundingBox criaBBCirculo(CIRCULO c);

/**
 * @brief Cria um bounding box a partir de um retângulo.
 * @param r Retângulo que define o bounding box
 * @return Bounding box encapsulador do retângulo
 */
BoundingBox criaBBRetangulo(RETANGULO r);

/**
 * @brief Cria um bounding box a partir de uma linha.
 * @param l Linha que define o bounding box
 * @return Bounding box encapsulador da linha
 */
BoundingBox criaBBLinha(LINHA l);

/**
 * @brief Cria um bounding box a partir de um texto.
 * @param t Texto que define o bounding box
 * @return Bounding box encapsulador do texto
 */
BoundingBox criaBBTexto(TEXTO t);

/**
 * @brief Une dois bounding boxes expandindo o destino.
 * @param destino Bounding box que será expandido
 * @param fonte Bounding box que contribui para a expansão
 */
void uniaoBB(BoundingBox destino, BoundingBox fonte);

/**
 * @brief Obtém a coordenada X do canto superior esquerdo.
 * @param bb Bounding box
 * @return Coordenada X
 */
double getXBoundingBox(BoundingBox bb);

/**
 * @brief Obtém a coordenada Y do canto superior esquerdo.
 * @param bb Bounding box
 * @return Coordenada Y
 */
double getYBoundingBox(BoundingBox bb);

/**
 * @brief Obtém a largura do bounding box.
 * @param bb Bounding box
 * @return Largura
 */
double getWBoundingBox(BoundingBox bb);

/**
 * @brief Obtém a altura do bounding box.
 * @param bb Bounding box
 * @return Altura
 */
double getHBoundingBox(BoundingBox bb);

#endif
