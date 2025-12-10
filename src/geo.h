#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "lista.h"

/**
 * @file geo.h
 * @brief Módulo de processamento de arquivos .geo.
 * 
 * @details
 * Este módulo é responsável por ler e processar arquivos .geo,
 * que contêm a descrição das formas geométricas iniciais do jogo.
 */

/**
 * @brief Processa um arquivo .geo e carrega as formas no chão.
 * @param pathGeo Caminho completo para o arquivo .geo.
 * @param chao LISTA onde as formas serão armazenadas na ordem de leitura.
 */
void processarGeo(const char *pathGeo, LISTA chao);

#endif