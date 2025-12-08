#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include "lista.h"

/**
 * @file qry.h
 * @brief Declarações das funções de processamento do arquivo .qry
 * @details
 * Este módulo contém a declaração da função principal para processar comandos
 * do arquivo .qry, aplicando-os às formas armazenadas na lista.
 * A função processarQry lê o arquivo .qry, interpreta os comandos e executa
 * as operações correspondentes nas formas.
 * @param pathQry Caminho para o arquivo .qry de entrada
 * @param pathTxt Caminho para o arquivo .txt de saída (pode ser NULL)
 * @param pathSvg Caminho para o arquivo .svg de saída
 * @param formas Lista de formas (LISTA) a serem processadas
 * @param tipoOrdenacao Tipo de ordenação a ser usada ('b' para bubble sort, 'i' para insertion sort, etc.)
 * @param thresholdInsertionSort Threshold para usar insertion sort
 */
void processarQry(const char *pathQry, const char *pathTxt, const char *pathSvg, LISTA formas, char tipoOrdenacao, int thresholdInsertionSort);

#endif