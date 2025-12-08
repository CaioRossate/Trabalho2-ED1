#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#include "circulo.h"

typedef struct {
    int id;
    float x, y, raio;
    char *corP;
    char *corB;
} Circulo;

CIRCULO cria_circulo(int id, float x, float y, float raio, const char* corP, const char* corB) {
    Circulo* c = malloc(sizeof(Circulo));
    if (c == NULL) {
        printf("Erro ao alocar memoria para a criação do círculo");
        exit(1);
    }

    c->id = id;
    c->x = x;
    c->y = y;
    c->raio = raio;

    c->corP = malloc(strlen(corP) + 1);
    if (c->corP == NULL) {
        printf("Erro ao alocar memória para a cor de preenchimento");
        exit(1);
    }
    strcpy(c->corP, corP);

    c->corB = malloc(strlen(corB) + 1);
    if (c->corB == NULL) {
        printf("Erro ao alocar memória para a cor da borda");
        exit(1);
    }
    strcpy(c->corB, corB);

    return c;
}

void destroiCirculo(CIRCULO c) {
    Circulo* circ = (Circulo*)c;
    if (circ != NULL) {
        if (circ->corP != NULL) {
            free(circ->corP);
        }
        if (circ->corB != NULL) {
            free(circ->corB);
        }
        free(circ);
    }
}

int getIDCirculo(CIRCULO c) {
    return ((Circulo*)c)->id;
}

float getXCirculo(CIRCULO c) {
    return ((Circulo*)c)->x;
}

float getYCirculo(CIRCULO c) {
    return ((Circulo*)c)->y;
}

float getRaioCirculo(CIRCULO c) {
    return ((Circulo*)c)->raio;
}

float getAreaCirculo(CIRCULO c) {
    Circulo* circ = (Circulo*)c;
    return M_PI * circ->raio * circ->raio;
}

char* getCorBCirculo(CIRCULO c) {
    return ((Circulo*)c)->corB;
}

char* getCorPCirculo(CIRCULO c) {
    return ((Circulo*)c)->corP;
}

void setIDCirculo(CIRCULO c, int id) {
    ((Circulo*)c)->id = id;
}

void setXCirculo(CIRCULO c, float x) {
    ((Circulo*)c)->x = x;
}

void setYCirculo(CIRCULO c, float y) {
    ((Circulo*)c)->y = y;
}

void setRaioCirculo(CIRCULO c, float raio) {
    ((Circulo*)c)->raio = raio;
}

void setCorBCirculo(CIRCULO c, const char* corB) {
    Circulo* circ = (Circulo*)c;
    free(circ->corB);
    circ->corB = malloc(strlen(corB) + 1);
    strcpy(circ->corB, corB);
}

void setCorPCirculo(CIRCULO c, const char* corP) {
    Circulo* circ = (Circulo*)c;
    free(circ->corP);
    circ->corP = malloc(strlen(corP) + 1);
    strcpy(circ->corP, corP);
}
