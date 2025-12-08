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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define TAM_LINHA_MAX 512
#define EPSILON_GEOM 1e-9

static LISTA anteparos = NULL;





int comparaAnteparos(ANTEPARO ant1, ANTEPARO ant2, double yRef) {
    if (ant1 == NULL || ant2 == NULL) return 0;

    double x11 = getX1Anteparo(ant1);
    double y11 = getY1Anteparo(ant1);
    double x12 = getX2Anteparo(ant1);
    double y12 = getY2Anteparo(ant1);

    double x21 = getX1Anteparo(ant2);
    double y21 = getY1Anteparo(ant2);
    double x22 = getX2Anteparo(ant2);
    double y22 = getY2Anteparo(ant2);

    double xi1, xi2;

    // calcula interseção do anteparo com a linha y = yRef
    if (fabs(y12 - y11) < EPSILON_GEOM) {
        xi1 = (x11 + x12) / 2.0;
    } else {
        double t1 = (yRef - y11) / (y12 - y11);
        if (t1 < 0.0) t1 = 0.0; if (t1 > 1.0) t1 = 1.0;
        xi1 = x11 + t1 * (x12 - x11);
    }

    if (fabs(y22 - y21) < EPSILON_GEOM) {
        xi2 = (x21 + x22) / 2.0;
    } else {
        double t2 = (yRef - y21) / (y22 - y21);
        if (t2 < 0.0) t2 = 0.0; if (t2 > 1.0) t2 = 1.0;
        xi2 = x21 + t2 * (x22 - x21);
    }

    if (fabs(xi1 - xi2) < EPSILON_GEOM) return 0;
    return (xi1 < xi2) ? -1 : 1;
}

bool anteparosIntersectam(ANTEPARO ant1, ANTEPARO ant2, double *x, double *y) {
    if (ant1 == NULL || ant2 == NULL) return false;

    double x1 = getX1Anteparo(ant1), y1 = getY1Anteparo(ant1);
    double x2 = getX2Anteparo(ant1), y2 = getY2Anteparo(ant1);
    double x3 = getX1Anteparo(ant2), y3 = getY1Anteparo(ant2);
    double x4 = getX2Anteparo(ant2), y4 = getY2Anteparo(ant2);

    double denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (fabs(denom) < EPSILON_GEOM) return false;

    double px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    double py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    // verifica se o ponto está dentro dos dois segmentos (com margem)
    double minx1 = fmin(x1,x2)-EPSILON_GEOM, maxx1 = fmax(x1,x2)+EPSILON_GEOM;
    double miny1 = fmin(y1,y2)-EPSILON_GEOM, maxy1 = fmax(y1,y2)+EPSILON_GEOM;
    double minx2 = fmin(x3,x4)-EPSILON_GEOM, maxx2 = fmax(x3,x4)+EPSILON_GEOM;
    double miny2 = fmin(y3,y4)-EPSILON_GEOM, maxy2 = fmax(y3,y4)+EPSILON_GEOM;

    if (px >= minx1 && px <= maxx1 && py >= miny1 && py <= maxy1 &&
        px >= minx2 && px <= maxx2 && py >= miny2 && py <= maxy2) {
        if (x) *x = px;
        if (y) *y = py;
        return true;
    }

    return false;
}

bool pontoNoPoligono(double px, double py, double *verticesX, double *verticesY, int numVertices) {
    if (verticesX == NULL || verticesY == NULL || numVertices < 3) return false;
    bool dentro = false;
    for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
        double xi = verticesX[i], yi = verticesY[i];
        double xj = verticesX[j], yj = verticesY[j];
        if ( ((yi > py) != (yj > py)) &&
             (px < (xj - xi) * (py - yi) / (yj - yi + 0.0) + xi) ) {
            dentro = !dentro;
        }
    }
    return dentro;
}

double distanciaPontoAnteparo(double px, double py, ANTEPARO ant) {
    if (ant == NULL) return 1e100;
    double x1 = getX1Anteparo(ant), y1 = getY1Anteparo(ant);
    double x2 = getX2Anteparo(ant), y2 = getY2Anteparo(ant);

    double dx = x2 - x1;
    double dy = y2 - y1;
    double l2 = dx*dx + dy*dy;
    if (l2 == 0.0) return hypot(px - x1, py - y1);

    double t = ((px - x1)*dx + (py - y1)*dy) / l2;
    if (t < 0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    double projx = x1 + t * dx;
    double projy = y1 + t * dy;
    return hypot(px - projx, py - projy);
}

static void* clonaForma(void *forma, char tipo, int novoID) {
    if (forma == NULL) return NULL;
    
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        return cria_circulo(novoID, getXCirculo(c), getYCirculo(c), getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
    }
    else if (tipo == 'r') {
        RETANGULO r = (RETANGULO)forma;
        return cria_retangulo(novoID, getXRetangulo(r), getYRetangulo(r), getLarguraRetangulo(r), getAlturaRetangulo(r), getCorBRetangulo(r), getCorPRetangulo(r));
    }
    else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        return criaLinha(novoID, getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        return cria_texto(novoID, getXTexto(t), getYTexto(t), getAncoraTexto(t), getCorBTexto(t), getCorPTexto(t), getTxtoTexto(t), getFontFamilyTexto(t), getFontWeightTexto(t), getFontSizeTexto(t));
    }
    
    return NULL;
}

static bool formaIntersectaPoligono(void *forma, char tipo, POLIGONO poli) {
    if (forma == NULL || poli == NULL) return false;
    
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        double cx = getXCirculo(c);
        double cy = getYCirculo(c);
        double r = getRaioCirculo(c);
        
        if (isInside(poli, cx, cy)) return true;
        
        void *v = getPrimeiroVertice(poli);
        while (v != NULL) {
            double vx, vy;
            getCoordenadaVertice(v, &vx, &vy);
            
            double dist = sqrt((vx - cx) * (vx - cx) + (vy - cy) * (vy - cy));
            if (dist <= r) return true;
            
            v = getProximoVertice(v);
        }
        
        return false;
    }
    else if (tipo == 'r') {
        RETANGULO rect = (RETANGULO)forma;
        double x = getXRetangulo(rect);
        double y = getYRetangulo(rect);
        double w = getLarguraRetangulo(rect);
        double h = getAlturaRetangulo(rect);
        
        // Teste: Vértices do retângulo dentro do polígono
        if (isInside(poli, x, y)) return true;
        if (isInside(poli, x + w, y)) return true;
        if (isInside(poli, x, y + h)) return true;
        if (isInside(poli, x + w, y + h)) return true;
        
        // Teste: Vértices do polígono dentro do retângulo
        void *v = getPrimeiroVertice(poli);
        while (v != NULL) {
            double vx, vy;
            getCoordenadaVertice(v, &vx, &vy);
            
            if (vx >= x && vx <= x + w && vy >= y && vy <= y + h) {
                return true;
            }
            
            v = getProximoVertice(v);
        }
        
        return false;
    }
    else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        double x1 = getX1Linha(l);
        double y1 = getY1Linha(l);
        double x2 = getX2Linha(l);
        double y2 = getY2Linha(l);
        
        if (isInside(poli, x1, y1)) return true;
        if (isInside(poli, x2, y2)) return true;
        
        return false;
    }
    else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        double x = getXTexto(t);
        double y = getYTexto(t);
        
        return isInside(poli, x, y);
    }
    
    return false;
}

static void cmd_a(int idInicio, int idFim, char orientacao, LISTA formas, FILE *txt) {
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
    int idAnteparo = 100000;
    int totalAnteparos = 0;
    
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
                
                ANTEPARO ant;
                if (orientacao == 'h' || orientacao == 'H') {
                    ant = criaAnteparo(idAnteparo++, cx - r, cy, cx + r, cy, cor);
                } else {
                    ant = criaAnteparo(idAnteparo++, cx, cy - r, cx, cy + r, cor);
                }
                
                insereLista(anteparos, ant, 'a');
                totalAnteparos++;
                
                if (txt) {
                    fprintf(txt, "  Círculo ID=%d -> Anteparo ID=%d: (%.2f,%.2f)-(%.2f,%.2f)\n",
                            id, getIdAnteparo(ant), 
                            getX1Anteparo(ant), getY1Anteparo(ant),
                            getX2Anteparo(ant), getY2Anteparo(ant));
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
                
                ANTEPARO ant1 = criaAnteparo(idAnteparo++, x, y, x, y + h, cor);
                ANTEPARO ant2 = criaAnteparo(idAnteparo++, x, y + h, x + w, y + h, cor);
                ANTEPARO ant3 = criaAnteparo(idAnteparo++, x + w, y + h, x + w, y, cor);
                ANTEPARO ant4 = criaAnteparo(idAnteparo++, x + w, y, x, y, cor);
                
                insereLista(anteparos, ant1, 'a');
                insereLista(anteparos, ant2, 'a');
                insereLista(anteparos, ant3, 'a');
                insereLista(anteparos, ant4, 'a');
                totalAnteparos += 4;
                
                if (txt) {
                    fprintf(txt, "  Retângulo ID=%d -> 4 anteparos (IDs=%d a %d)\n",
                            id, idAnteparo - 4, idAnteparo - 1);
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
                
                ANTEPARO ant = criaAnteparo(idAnteparo++, x1, y1, x2, y2, cor);
                insereLista(anteparos, ant, 'a');
                totalAnteparos++;
                
                if (txt) {
                    fprintf(txt, "  Linha ID=%d -> Anteparo ID=%d\n", id, idAnteparo - 1);
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
                
                ANTEPARO ant = criaAnteparo(idAnteparo++, x1, y1, x2, y2, cor);
                insereLista(anteparos, ant, 'a');
                totalAnteparos++;
                
                if (txt) {
                    fprintf(txt, "  Texto ID=%d -> Anteparo ID=%d: (%.2f,%.2f)-(%.2f,%.2f)\n",
                            id, idAnteparo - 1, x1, y1, x2, y2);
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
        fprintf(txt, "Total de anteparos criados: %d\n", totalAnteparos);
        fprintf(txt, "========================================\n\n");
    }
}

static void cmd_d(double x, double y, const char *sufixo, LISTA formas, FILE *txt,
           const char *svgBase, char tipoOrdenacao, int threshold) {
    if (txt) {
        fprintf(txt, "\n========================================\n");
        fprintf(txt, "[D] Bomba de Destruição em (%.2f, %.2f)\n", x, y);
        fprintf(txt, "========================================\n");
    }
    
    POLIGONO poli = calculaVisibilidade(x, y, anteparos, tipoOrdenacao, threshold);
    if (poli == NULL) {
        if (txt) fprintf(txt, "ERRO: Não foi possível calcular visibilidade\n");
        return;
    }
    LISTA formasDestruidas = criaLista();
    LISTA formasSobreviventes = criaLista();
    int totalDestruidas = 0;
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
        }else {
            // Forma está fora: mantém
            insereLista(formasSobreviventes, forma, tipo);
        }
        
        no = obtemProximoNo(no);
    }
    
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

    no = obtemPrimeiroNo(formasDestruidas);
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        destroiForma(forma, tipo);
        no = obtemProximoNo(no);
    }

    destroiLista(formasDestruidas);
    destroiLista(formasSobreviventes);

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

