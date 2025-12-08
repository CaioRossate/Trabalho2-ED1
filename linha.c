#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linha.h"


typedef struct {
    int id;
    double x1, y1;
    double x2, y2;
    char *cor;
} Linha;


LINHA criaLinha(int id, double x1, double y1, double x2, double y2, const char *cor) {
    Linha* l = (Linha*)malloc(sizeof(Linha));
    if (l == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para a linha.\n");
        exit(1);
    }

    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = (char*)malloc(strlen(cor) + 1);
    if (l->cor == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para a cor da linha.\n");
        free(l);
        exit(1);
    }
    strcpy(l->cor, cor);

    return l;
}

void destroiLinha(LINHA l) {
    Linha* linha = (Linha*)l;
    if (linha != NULL) {
        if (linha->cor != NULL) {
            free(linha->cor);
        }
        free(linha); 
    }
}


double calculaAreaLinha(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double comprimento = sqrt(dx * dx + dy * dy); 
    return 2.0 * comprimento; 
}


int getIdLinha(LINHA l) { 
    return ((Linha*)l)->id; 
}

double getX1Linha(LINHA l) { 
    return ((Linha*)l)->x1; 
}

double getY1Linha(LINHA l) { 
    return ((Linha*)l)->y1; 
}

double getX2Linha(LINHA l) { 
    return ((Linha*)l)->x2; 
}

double getY2Linha(LINHA l) { 
    return ((Linha*)l)->y2; 
}

char *getCorLinha(LINHA l) { 
    return ((Linha*)l)->cor; 
}


void definirX1Linha(LINHA l, double x1) { 
    ((Linha*)l)->x1 = x1; 
}

void definirY1Linha(LINHA l, double y1) { 
    ((Linha*)l)->y1 = y1; 
}

void definirX2Linha(LINHA l, double x2) { 
    ((Linha*)l)->x2 = x2; 
}

void definirY2Linha(LINHA l, double y2) { 
    ((Linha*)l)->y2 = y2; 
}

void definirCorLinha(LINHA l, const char *cor) {
    Linha* linha = (Linha*)l;
    
    if (linha->cor != NULL) {
        free(linha->cor);
    }
    
    linha->cor = (char*)malloc(strlen(cor) + 1);
    if (linha->cor == NULL) {
        fprintf(stderr, "ERRO: Falha ao realocar memória para a nova cor da linha.\n");
        exit(1);
    }
    strcpy(linha->cor, cor);
}