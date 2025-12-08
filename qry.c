#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "qry.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "util_forma.h"
#include "anteparo.h"
#include "poligono.h"
#include "visibilidade.h"
#include "lista.h"
#include "svg.h"

#define TAM_LINHA_MAX 512
#define M_PI 3.14159265358979323846

    // Lista global para armazenar os anteparos (segmentos bloqueantes)
static LISTA anteparos = NULL;

/**
 * @brief Clona uma forma genérica.
 */
void* clonaForma(void *forma, char tipo, int novoID) {
    if (forma == NULL) return NULL;
    
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        return cria_circulo(novoID, getXCirculo(c), getYCirculo(c), 
                           getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
    }
    else if (tipo == 'r') {
        RETANGULO r = (RETANGULO)forma;
        return cria_retangulo(novoID, getXRetangulo(r), getYRetangulo(r),
                             getLarguraRetangulo(r), getAlturaRetangulo(r),
                             getCorBRetangulo(r), getCorPRetangulo(r));
    }
    else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        return criaLinha(novoID, getX1Linha(l), getY1Linha(l),
                        getX2Linha(l), getY2Linha(l), getCorLinha(l));
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        return cria_texto(novoID, getXTexto(t), getYTexto(t), getAncoraTexto(t),
                         getCorBTexto(t), getCorPTexto(t), getTxtoTexto(t),
                         getFontFamilyTexto(t), getFontWeightTexto(t), getFontSizeTexto(t));
    }
    
    return NULL;
}

/**
 * @brief Verifica se uma forma está REALMENTE dentro do polígono.
 * Critério rigoroso: forma só é destruída se majoritariamente dentro.
 */
bool formaIntersectaPoligono(void *forma, char tipo, POLIGONO poli) {
    if (forma == NULL || poli == NULL) return false;
    
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        double cx = getXCirculo(c);
        double cy = getYCirculo(c);
        double r = getRaioCirculo(c);
        
        // Critério: Centro E bordas significativas do círculo devem estar dentro
        // Teste 1: Centro dentro?
        if (!isInside(poli, cx, cy)) return false;
        
        // Teste 2: Pelo menos 3 pontos na borda do círculo também dentro?
        // (nordeste, sudeste, sudoeste, noroeste)
        int pontosInside = 0;
        double angulos[4] = {M_PI/4, -M_PI/4, -3*M_PI/4, 3*M_PI/4};
        for (int i = 0; i < 4; i++) {
            double px = cx + r * cos(angulos[i]);
            double py = cy + r * sin(angulos[i]);
            if (isInside(poli, px, py)) pontosInside++;
        }
        
        return pontosInside >= 3;  // Destruir apenas se 3+ pontos da borda estão dentro
    }
    else if (tipo == 'r') {
        RETANGULO rect = (RETANGULO)forma;
        double x = getXRetangulo(rect);
        double y = getYRetangulo(rect);
        double w = getLarguraRetangulo(rect);
        double h = getAlturaRetangulo(rect);
        
        // Critério: TODOS os 4 vértices devem estar dentro para destruir
        int verticesInside = 0;
        if (isInside(poli, x, y)) verticesInside++;
        if (isInside(poli, x + w, y)) verticesInside++;
        if (isInside(poli, x, y + h)) verticesInside++;
        if (isInside(poli, x + w, y + h)) verticesInside++;
        
        return verticesInside == 4;  // Destruir apenas se TODOS os vértices estão dentro
    }
    else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        double x1 = getX1Linha(l);
        double y1 = getY1Linha(l);
        double x2 = getX2Linha(l);
        double y2 = getY2Linha(l);
        
        // Critério: AMBAS as extremidades devem estar dentro
        bool p1Inside = isInside(poli, x1, y1);
        bool p2Inside = isInside(poli, x2, y2);
        
        // Também verifica ponto do meio
        double xMeio = (x1 + x2) / 2.0;
        double yMeio = (y1 + y2) / 2.0;
        bool pMeioInside = isInside(poli, xMeio, yMeio);
        
        return p1Inside && p2Inside && pMeioInside;  // Destruir se toda a linha está dentro
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        double x = getXTexto(t);
        double y = getYTexto(t);
        
        // Texto: só destrói se a âncora está bem dentro do polígono
        return isInside(poli, x, y);
    }
    
    return false;
}

/**
 * @brief Transforma formas em anteparos (segmentos bloqueantes).
 */
void cmd_a(int idInicio, int idFim, char orientacao, LISTA formas, FILE *txt) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[A] Transformando formas [%d-%d] em anteparos (orientação: %c)\n", 
                idInicio, idFim, orientacao);
        fprintf(txt, "========================================\n");
    }
    
    if (anteparos == NULL) {
        anteparos = criaLista();
    }
    
    LISTA novasFormas = criaLista();
    int idSegmento = 100000;
    int totalSegmentos = 0;
    
    void *no = obtemPrimeiroNo(formas);
    
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        int id = obtemIDforma(forma, tipo);
        
        void *proximoNo = obtemProximoNo(no);
        
        if (id >= idInicio && id <= idFim) {
            // Forma está na faixa: transformar em anteparo
            
            if (tipo == 'c') {
                CIRCULO c = (CIRCULO)forma;
                double cx = getXCirculo(c);
                double cy = getYCirculo(c);
                double r = getRaioCirculo(c);
                char *cor = getCorBCirculo(c);
                
                ANTEPARO seg;
                if (orientacao == 'h' || orientacao == 'H') {
                    seg = criaAnteparo(idSegmento++, cx - r, cy, cx + r, cy, cor);
                } else {
                    seg = criaAnteparo(idSegmento++, cx, cy - r, cx, cy + r, cor);
                }

                insereLista(anteparos, seg, 'a');
                totalSegmentos++;

                if (txt) {
                    fprintf(txt, "  Círculo ID=%d -> Anteparo ID=%d: (%.2f,%.2f)-(%.2f,%.2f)\n",
                            id, getIdAnteparo(seg), 
                            getX1Anteparo(seg), getY1Anteparo(seg),
                            getX2Anteparo(seg), getY2Anteparo(seg));
                }

                destroiCirculo(c);
            }
            else if (tipo == 'r') {
                RETANGULO r = (RETANGULO)forma;
                double x = getXRetangulo(r);
                double y = getYRetangulo(r);
                double w = getLarguraRetangulo(r);
                double h = getAlturaRetangulo(r);
                char *cor = getCorBRetangulo(r);
                
                ANTEPARO seg1 = criaAnteparo(idSegmento++, x, y, x, y + h, cor);
                ANTEPARO seg2 = criaAnteparo(idSegmento++, x, y + h, x + w, y + h, cor);
                ANTEPARO seg3 = criaAnteparo(idSegmento++, x + w, y + h, x + w, y, cor);
                ANTEPARO seg4 = criaAnteparo(idSegmento++, x + w, y, x, y, cor);

                insereLista(anteparos, seg1, 'a');
                insereLista(anteparos, seg2, 'a');
                insereLista(anteparos, seg3, 'a');
                insereLista(anteparos, seg4, 'a');
                totalSegmentos += 4;

                if (txt) {
                    fprintf(txt, "  Retângulo ID=%d -> 4 anteparos (IDs=%d a %d)\n",
                            id, idSegmento - 4, idSegmento - 1);
                }

                destroiRetangulo(r);
            }
            else if (tipo == 'l') {
                LINHA l = (LINHA)forma;
                double x1 = getX1Linha(l);
                double y1 = getY1Linha(l);
                double x2 = getX2Linha(l);
                double y2 = getY2Linha(l);
                char *cor = getCorLinha(l);
                
                ANTEPARO seg = criaAnteparo(idSegmento++, x1, y1, x2, y2, cor);
                insereLista(anteparos, seg, 'a');
                totalSegmentos++;

                if (txt) {
                    fprintf(txt, "  Linha ID=%d -> Anteparo ID=%d (anteparo)\n", id, idSegmento - 1);
                }

                destroiLinha(l);
            }
            else if (tipo == 't') {
                TEXTO t = (TEXTO)forma;
                double xt = getXTexto(t);
                double yt = getYTexto(t);
                char ancora = getAncoraTexto(t);
                char *txto = getTxtoTexto(t);
                char *cor = getCorBTexto(t);
                int tamanho = strlen(txto);
                
                double x1, y1, x2, y2;
                double comprimento = 10.0 * tamanho;
                
                if (ancora == 'i' || ancora == 'I') {
                    x1 = xt;
                    y1 = yt;
                    x2 = xt + comprimento;
                    y2 = yt;
                } else if (ancora == 'f' || ancora == 'F') {
                    x1 = xt - comprimento;
                    y1 = yt;
                    x2 = xt;
                    y2 = yt;
                } else {
                    x1 = xt - comprimento / 2.0;
                    y1 = yt;
                    x2 = xt + comprimento / 2.0;
                    y2 = yt;
                }
                
                ANTEPARO seg = criaAnteparo(idSegmento++, x1, y1, x2, y2, cor);
                insereLista(anteparos, seg, 'a');
                totalSegmentos++;

                if (txt) {
                    fprintf(txt, "  Texto ID=%d -> Anteparo ID=%d: (%.2f,%.2f)-(%.2f,%.2f)\n",
                            id, idSegmento - 1, x1, y1, x2, y2);
                }

                destroiTexto(t);
            }
        } else {
            // Forma NÃO está na faixa: mantém
            insereLista(novasFormas, forma, tipo);
        }
        
        no = proximoNo;
    }
    
    // Substitui a lista antiga pela nova
    // ATENÇÃO: Aqui assumimos que você vai copiar os dados de volta
    // Para simplificar, vou apenas limpar e repovoar
    while (!listaVazia(formas)) {
        removePrimeiroLista(formas);
    }
    
    no = obtemPrimeiroNo(novasFormas);
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        insereLista(formas, forma, tipo);
        no = obtemProximoNo(no);
    }
    
    destroiLista(novasFormas);
    
    if (txt) {
        fprintf(txt, "Total de segmentos criados: %d\n", totalSegmentos);
        fprintf(txt, "========================================\n\n");
    }
}

/**
 * @brief Bomba de destruição.
 */
void cmd_d(double x, double y, const char *sufixo, LISTA formas, FILE *txt,
           const char *svgBase, char tipoOrdenacao, int threshold) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[D] Bomba de Destruição em (%.2f, %.2f)\n", x, y);
        fprintf(txt, "========================================\n");
    }
    
    // Calcula polígono de visibilidade
    POLIGONO poli = calculaVisibilidade(x, y, anteparos, tipoOrdenacao, threshold);
    
    if (poli == NULL) {
        if (txt) fprintf(txt, "ERRO: Não foi possível calcular visibilidade\n");
        return;
    }
    
    LISTA formasDestruidas = criaLista();
    LISTA formasSobreviventes = criaLista();
    int totalDestruidas = 0;
    
    // Verifica quais formas estão dentro da região
    void *no = obtemPrimeiroNo(formas);
    
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        
        if (formaIntersectaPoligono(forma, tipo, poli)) {
            // Forma está dentro: destrói
            insereLista(formasDestruidas, forma, tipo);
            totalDestruidas++;
            
            if (txt) {
                fprintf(txt, "  DESTRUÍDA: Forma ID=%d, tipo='%c'\n", 
                        obtemIDforma(forma, tipo), tipo);
            }
        } else {
            // Forma está fora: mantém
            insereLista(formasSobreviventes, forma, tipo);
        }
        
        no = obtemProximoNo(no);
    }
    
    // Atualiza lista de formas
    while (!listaVazia(formas)) {
        removePrimeiroLista(formas);
    }
    
    no = obtemPrimeiroNo(formasSobreviventes);
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        insereLista(formas, forma, tipo);
        no = obtemProximoNo(no);
    }
    
    // Libera formas destruídas
    no = obtemPrimeiroNo(formasDestruidas);
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        destroiForma(forma, tipo);
        no = obtemProximoNo(no);
    }
    
    destroiLista(formasDestruidas);
    destroiLista(formasSobreviventes);
    
    // Desenha polígono de visibilidade no SVG
    if (strcmp(sufixo, "-") != 0) {
        char caminhoSvg[1024];
        snprintf(caminhoSvg, sizeof(caminhoSvg), "%s-%s.svg", svgBase, sufixo);
        
        FILE *svgFile = fopen(caminhoSvg, "w");
        if (svgFile != NULL) {
            desenhaPoligonoVisibilidadeSvg(svgFile, poli);
            fclose(svgFile);
        }
    }
    
    liberaPoligono(poli);
    
    if (txt) {
        fprintf(txt, "Total de formas destruídas: %d\n", totalDestruidas);
        fprintf(txt, "========================================\n\n");
    }
}

/**
 * @brief Bomba de pintura.
 */
void cmd_p(double x, double y, const char *cor, const char *sufixo,
           LISTA formas, FILE *txt, const char *svgBase,
           char tipoOrdenacao, int threshold) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[P] Bomba de Pintura em (%.2f, %.2f) com cor %s\n", x, y, cor);
        fprintf(txt, "========================================\n");
    }
    
    POLIGONO poli = calculaVisibilidade(x, y, anteparos, tipoOrdenacao, threshold);
    
    if (poli == NULL) {
        if (txt) fprintf(txt, "ERRO: Não foi possível calcular visibilidade\n");
        return;
    }
    
    int totalPintadas = 0;
    
    void *no = obtemPrimeiroNo(formas);
    
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        
        if (formaIntersectaPoligono(forma, tipo, poli)) {
            // Forma está dentro: pinta
            
            if (tipo == 'c') {
                CIRCULO c = (CIRCULO)forma;
                setCorBCirculo(c, cor);
                setCorPCirculo(c, cor);
            } else if (tipo == 'r') {
                RETANGULO r = (RETANGULO)forma;
                setCorBRetangulo(r, cor);
                setCorPRetangulo(r, cor);
            } else if (tipo == 'l') {
                LINHA l = (LINHA)forma;
                definirCorLinha(l, cor);
            } else if (tipo == 't') {
                TEXTO t = (TEXTO)forma;
                setCorBTexto(t, cor);
                setCorPTexto(t, cor);
            }
            
            totalPintadas++;
            
            if (txt) {
                fprintf(txt, "  PINTADA: Forma ID=%d, tipo='%c' -> cor %s\n", 
                        obtemIDforma(forma, tipo), tipo, cor);
            }
        }
        
        no = obtemProximoNo(no);
    }
    
    // Desenha polígono no SVG
    if (strcmp(sufixo, "-") != 0) {
        char caminhoSvg[1024];
        snprintf(caminhoSvg, sizeof(caminhoSvg), "%s-%s.svg", svgBase, sufixo);
        
        FILE *svgFile = fopen(caminhoSvg, "w");
        if (svgFile != NULL) {
            desenhaPoligonoVisibilidadeSvg(svgFile, poli);
            fclose(svgFile);
        }
    }
    
    liberaPoligono(poli);
    
    if (txt) {
        fprintf(txt, "Total de formas pintadas: %d\n", totalPintadas);
        fprintf(txt, "========================================\n\n");
    }
}

/**
 * @brief Bomba de clonagem.
 */
void cmd_cln(double x, double y, double dx, double dy, const char *sufixo,
             LISTA formas, FILE *txt, const char *svgBase,
             char tipoOrdenacao, int threshold) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[CLN] Bomba de Clonagem em (%.2f, %.2f), offset (%.2f, %.2f)\n",
                x, y, dx, dy);
        fprintf(txt, "========================================\n");
    }
    
    POLIGONO poli = calculaVisibilidade(x, y, anteparos, tipoOrdenacao, threshold);
    
    if (poli == NULL) {
        if (txt) fprintf(txt, "ERRO: Não foi possível calcular visibilidade\n");
        return;
    }
    
    LISTA clones = criaLista();
    int totalClonadas = 0;
    int proximoID = 200000;
    
    void *no = obtemPrimeiroNo(formas);
    
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        
        if (formaIntersectaPoligono(forma, tipo, poli)) {
            // Forma está dentro: clona
            void *clone = clonaForma(forma, tipo, proximoID++);
            
            if (clone != NULL) {
                // Translada o clone
                moveForma(clone, tipo, dx, dy);
                
                insereLista(clones, clone, tipo);
                totalClonadas++;
                
                if (txt) {
                    fprintf(txt, "  CLONADA: Forma ID=%d -> Clone ID=%d (offset: %.2f, %.2f)\n", 
                            obtemIDforma(forma, tipo), proximoID - 1, dx, dy);
                }
            }
        }
        
        no = obtemProximoNo(no);
    }
    
    // Adiciona clones à lista de formas
    no = obtemPrimeiroNo(clones);
    while (no != NULL) {
        void *clone = obtemDado(no);
        char tipo = obtemTipo(no);
        insereLista(formas, clone, tipo);
        no = obtemProximoNo(no);
    }
    
    destroiLista(clones);
    
    // Desenha polígono no SVG
    if (strcmp(sufixo, "-") != 0) {
        char caminhoSvg[1024];
        snprintf(caminhoSvg, sizeof(caminhoSvg), "%s-%s.svg", svgBase, sufixo);
        
        FILE *svgFile = fopen(caminhoSvg, "w");
        if (svgFile != NULL) {
            desenhaPoligonoVisibilidadeSvg(svgFile, poli);
            fclose(svgFile);
        }
    }
    
    liberaPoligono(poli);
    
    if (txt) {
        fprintf(txt, "Total de formas clonadas: %d\n", totalClonadas);
        fprintf(txt, "========================================\n\n");
    }
}

void processarQry(const char *pathQry, const char *pathTxt, const char *pathSvg,
                  LISTA formas, char tipoOrdenacao, int thresholdInsertionSort) {
    FILE *qryFile = fopen(pathQry, "r");
    if (qryFile == NULL) {
        fprintf(stderr, "ERRO: Não foi possível abrir %s\n", pathQry);
        return;
    }
    
    FILE *txtFile = NULL;
    if (pathTxt != NULL && pathTxt[0] != '\0') {
        txtFile = fopen(pathTxt, "w");
        if (txtFile == NULL) {
            fprintf(stderr, "ERRO: Não foi possível criar %s\n", pathTxt);
            fclose(qryFile);
            return;
        }
    }
    
    anteparos = criaLista();
    
    char linha[TAM_LINHA_MAX];
    
    while (fgets(linha, TAM_LINHA_MAX, qryFile) != NULL) {
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }
        
        if (linha[0] == '\0' || linha[0] == '#') {
            continue;
        }
        
        char comando[10];
        sscanf(linha, "%9s", comando);
        
        if (strcmp(comando, "a") == 0) {
            int idInicio, idFim;
            char orientacao;
            sscanf(linha, "a %d %d %c", &idInicio, &idFim, &orientacao);
            cmd_a(idInicio, idFim, orientacao, formas, txtFile);
        }
        else if (strcmp(comando, "d") == 0) {
            double x, y;
            char sufixo[256];
            sscanf(linha, "d %lf %lf %255s", &x, &y, sufixo);
            cmd_d(x, y, sufixo, formas, txtFile, pathSvg, tipoOrdenacao, thresholdInsertionSort);
        }
        else if (strcmp(comando, "p") == 0) {
            double x, y;
            char cor[64], sufixo[256];
            sscanf(linha, "p %lf %lf %63s %255s", &x, &y, cor, sufixo);
            cmd_p(x, y, cor, sufixo, formas, txtFile, pathSvg, tipoOrdenacao, thresholdInsertionSort);
        }
        else if (strcmp(comando, "cln") == 0) {
            double x, y, dx, dy;
            char sufixo[256];
            sscanf(linha, "cln %lf %lf %lf %lf %255s", &x, &y, &dx, &dy, sufixo);
            cmd_cln(x, y, dx, dy, sufixo, formas, txtFile, pathSvg, tipoOrdenacao, thresholdInsertionSort);
        }
    }
    
    // Limpa anteparos
    if (anteparos) {
        void *no = obtemPrimeiroNo(anteparos);
        while (no != NULL) {
            ANTEPARO seg = (ANTEPARO)obtemDado(no);
            destroiAnteparo(seg);
            no = obtemProximoNo(no);
        }
        destroiLista(anteparos);
    }
    
    fclose(qryFile);
    if (txtFile) fclose(txtFile);
}