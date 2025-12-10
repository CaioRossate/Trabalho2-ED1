#include <stdio.h>
#include "visibilidade.h"
#include "poligono.h"
#include "anteparo.h"
#include "lista.h"
#include "geometria.h"
#include "ordenacao.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "boundingbox.h"

#define EPSILON 1e-9
#define MAX_VERTICES 10000
#define M_PI 3.14159265358979323846

typedef struct {
    double x, y;
    double angulo;
    int idAnteparo;
    bool isInicio;
} Evento;

double calculaAngulo(double x1, double y1, double x2, double y2) {
    return atan2(y2 - y1, x2 - x1);
}

double normalizaAngulo(double angulo) {
    while (angulo < 0) angulo += 2.0 * M_PI;
    while (angulo >= 2.0 * M_PI) angulo -= 2.0 * M_PI;
    return angulo;
}

int comparaEventos(const void *a, const void *b) {
    Evento *e1 = (Evento*)a;
    Evento *e2 = (Evento*)b;
    
    if (e1->angulo < e2->angulo - EPSILON) return -1;
    if (e1->angulo > e2->angulo + EPSILON) return 1;
    
    // Desempate por distância
    double d1 = sqrt(e1->x * e1->x + e1->y * e1->y);
    double d2 = sqrt(e2->x * e2->x + e2->y * e2->y);
    
    if (d1 < d2 - EPSILON) return -1;
    if (d1 > d2 + EPSILON) return 1;
    return 0;
}

double intersecaoRaioAnteparo(double px, double py, double angulo, ANTEPARO ant) {
    double x1 = getX1Anteparo(ant);
    double y1 = getY1Anteparo(ant);
    double x2 = getX2Anteparo(ant);
    double y2 = getY2Anteparo(ant);
    
    // Direção do raio
    double dx = cos(angulo);
    double dy = sin(angulo);
    
    // Vetor do anteparo
    double sx = x2 - x1;
    double sy = y2 - y1;
    
    // Resolve o sistema de equações
    double denominador = dx * sy - dy * sx;
    
    if (fabs(denominador) < EPSILON) {
        return -1.0;
    }
    
    double t = ((x1 - px) * sy - (y1 - py) * sx) / denominador;
    double u = ((x1 - px) * dy - (y1 - py) * dx) / denominador;
    
    if (t >= -EPSILON && u >= -EPSILON && u <= 1.0 + EPSILON) {
        return t;
    }
    
    return -1.0;
}

ANTEPARO encontraAnteparoMaisProximo(LISTA anteparos, double px, double py, double angulo) {
    ANTEPARO melhor = NULL;
    double melhorDist = DBL_MAX;
    
    void *no = obtemPrimeiroNo(anteparos);
    
    while (no != NULL) {
        ANTEPARO ant = (ANTEPARO)obtemDado(no);
        
        double dist = intersecaoRaioAnteparo(px, py, angulo, ant);
        
        if (dist >= 0.0 && dist < melhorDist) {
            melhorDist = dist;
            melhor = ant;
        }
        
        no = obtemProximoNo(no);
    }
    
    return melhor;
}

POLIGONO calculaVisibilidade(double x, double y, LISTA anteparos, char tipoOrdenacao, int threshold) {
    if (anteparos == NULL || listaVazia(anteparos)) {
        POLIGONO poli = criaPoligono();
        
        // Adiciona um grande quadrado ao redor do ponto de observação
        double raio = 4096.0;
        adicionaVertice(poli, x - raio, y - raio);
        adicionaVertice(poli, x + raio, y - raio);
        adicionaVertice(poli, x + raio, y + raio);
        adicionaVertice(poli, x - raio, y + raio);
        
        return poli;
    }
    
    // coleta eventos
    Evento *eventos = (Evento*)malloc(MAX_VERTICES * sizeof(Evento));
    if (eventos == NULL) return NULL;
    
    int numEventos = 0;
    
    // Calcula bounding box dos anteparos e distância máxima do observador
    BoundingBox bbAll = NULL;
    double maxDist = 4096.0;

    void *no = obtemPrimeiroNo(anteparos);
    while (no != NULL && numEventos < MAX_VERTICES - 1) {
        ANTEPARO ant = (ANTEPARO)obtemDado(no);
        int idAnt = getIdAnteparo(ant);
        
        double x1 = getX1Anteparo(ant);
        double y1 = getY1Anteparo(ant);
        double x2 = getX2Anteparo(ant);
        double y2 = getY2Anteparo(ant);
        
        // atualiza bounding box geral
        BoundingBox bb = criaBBAnteparo(ant);
        if (bb != NULL) {
            if (bbAll == NULL) {
                bbAll = bb;
            } else {
                uniaoBB(bbAll, bb);
                destruirBB(bb);
            }
        }

        double d1 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
        double d2 = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
        if (d1 > maxDist) maxDist = d1;
        if (d2 > maxDist) maxDist = d2;
        
        // Evento para primeira extremidade
        eventos[numEventos].x = x1 - x;
        eventos[numEventos].y = y1 - y;
        eventos[numEventos].angulo = normalizaAngulo(calculaAngulo(x, y, x1, y1));
        eventos[numEventos].idAnteparo = idAnt;
        eventos[numEventos].isInicio = true;
        numEventos++;
        
        // Evento para segunda extremidade
        eventos[numEventos].x = x2 - x;
        eventos[numEventos].y = y2 - y;
        eventos[numEventos].angulo = normalizaAngulo(calculaAngulo(x, y, x2, y2));
        eventos[numEventos].idAnteparo = idAnt;
        eventos[numEventos].isInicio = false;
        numEventos++;
        
        no = obtemProximoNo(no);
    }
    
    // ordena eventos
    if (tipoOrdenacao == 'm' || tipoOrdenacao == 'M') {
        mergesort(eventos, numEventos, sizeof(Evento), comparaEventos, threshold);
    } else {
        qsort(eventos, numEventos, sizeof(Evento), comparaEventos);
    }
    
    // constrói polígono de visibilidade
    POLIGONO poli = criaPoligono();
    
    // calcula raio máximo para projeção dos raios
    double raioMax = maxDist * 1.2;
    
    // Se temos bounding box dos anteparos, podemos também limitar pelo tamanho diagonal
    if (bbAll != NULL) {
        double bw = getWBoundingBox(bbAll);
        double bh = getHBoundingBox(bbAll);
        double diag = sqrt(bw*bw + bh*bh) * 1.1;
        if (diag > raioMax) raioMax = diag;
    }
    
    for (int i = 0; i < numEventos; i++) {
        double angulo = eventos[i].angulo;
        
        // Traça raios em 3 direções próximas
        double angulos[3] = {
            angulo - 0.0001, angulo, angulo + 0.0001
        };
        
        for (int j = 0; j < 3; j++) {
            double ang = normalizaAngulo(angulos[j]);
            
            ANTEPARO antMaisProximo = encontraAnteparoMaisProximo(anteparos, x, y, ang);
            
            if (antMaisProximo != NULL) {
                double dist = intersecaoRaioAnteparo(x, y, ang, antMaisProximo);
                
                if (dist >= 0.0) {
                    double vx = x + dist * cos(ang);
                    double vy = y + dist * sin(ang);
                    
                    adicionaVertice(poli, vx, vy);
                }
            } else {
                // Sem anteparo interceptando este raio: projeta até o raio máximo calculado
                double vx = x + raioMax * cos(ang);
                double vy = y + raioMax * sin(ang);
                adicionaVertice(poli, vx, vy);
            }
        }
    }
    
    free(eventos);
    if (bbAll != NULL) destruirBB(bbAll);
    
    return poli;
}

bool pontoVisivel(POLIGONO poli, double x, double y) {
    return isInside(poli, x, y);
}