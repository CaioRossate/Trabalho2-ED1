#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include "circulo.h" 
#include "retangulo.h" 
#include "texto.h" 
#include "linha.h"
#include "poligono.h"
#include "lista.h"
#include "anteparo.h"

/**
 * @file svg.h
 * @brief Módulo de geração de arquivos SVG.
 *
 * @details
 * Este módulo fornece funções para criar arquivos SVG,
 * desenhando as formas geométricas do jogo em formato gráfico.
 */

/**
 * @brief Inicia um arquivo SVG, escrevendo o cabeçalho XML e a tag <svg>.
 * @param svgFile Ponteiro para o arquivo SVG aberto para escrita.
 */
void iniciaSvg(FILE *svgFile);

/**
 * @brief Adiciona o desenho de um círculo ao arquivo SVG.
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param circulo Ponteiro para o TAD CIRCULO a ser desenhado.
 */
void desenhaCirculoSvg(FILE *svgFile, CIRCULO circulo);

/**
 * @brief Adiciona o desenho de um retângulo ao arquivo SVG.
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param retangulo Ponteiro para o TAD RETANGULO a ser desenhado.
 */
void desenhaRetanguloSvg(FILE *svgFile, RETANGULO retangulo);

/**
 * @brief Adiciona o desenho de uma linha ao arquivo SVG.
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param linha Ponteiro para o TAD LINHA a ser desenhada.
 */
void desenhaLinhaSvg(FILE *svgFile, LINHA linha);

/**
 * @brief Adiciona o desenho de um texto ao arquivo SVG.
 * @param svgFile Ponteiro para o arquivo SVG.
 * @param texto Ponteiro para o TAD TEXTO a ser desenhado.
 */
void desenhaTextoSvg(FILE *svgFile, TEXTO texto);


/**
 * @brief Desenha o polígono de visibilidade no SVG.
 * @param svgFile Arquivo SVG
 * @param poli Polígono de visibilidade
 */
void desenhaPoligonoVisibilidadeSvg(FILE *svgFile, POLIGONO poli);

/**
 * @brief Desenha todas as formas de uma lista no SVG.
 * @param svgFile Arquivo SVG
 * @param formas Lista de formas
 */
void desenhaFormasLista(FILE *svgFile, LISTA formas);

/**
 * @brief Desenha um segmento no SVG.
 * @param svgFile Arquivo SVG
 * @param seg Segmento a ser desenhado
 */
void desenhaSegmentoSvg(FILE *svgFile, ANTEPARO seg);

/**
 * @brief Finaliza o arquivo SVG, fechando a tag </svg>.
 * @param svgFile Ponteiro para o arquivo SVG.
 */
void finalizaSvg(FILE *svgFile);

#endif