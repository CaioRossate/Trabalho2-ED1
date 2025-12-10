#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anteparo.h"

typedef struct anteparo {
    int id;
    double x1, y1;
    double x2, y2;
    char cor[64];
} Anteparo;

ANTEPARO criaAnteparo(int id, double x1, double y1, double x2, double y2, const char *cor) {
    Anteparo *ant = (Anteparo*)malloc(sizeof(Anteparo));
    if (ant == NULL) return NULL;
    
    ant->id = id;
    ant->x1 = x1;
    ant->y1 = y1;
    ant->x2 = x2;
    ant->y2 = y2;
    
    if (cor != NULL) {
        strncpy(ant->cor, cor, sizeof(ant->cor) - 1);
        ant->cor[sizeof(ant->cor) - 1] = '\0';
    } else {
        strcpy(ant->cor, "black");
    }
    
    return ant;
}

void destroiAnteparo(ANTEPARO anteparo) {
    if (anteparo != NULL) {
        free(anteparo);
    }
}

int getIdAnteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return -1;
    return ((Anteparo*)anteparo)->id;
}

double getX1Anteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return 0.0;
    return ((Anteparo*)anteparo)->x1;
}

double getY1Anteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return 0.0;
    return ((Anteparo*)anteparo)->y1;
}

double getX2Anteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return 0.0;
    return ((Anteparo*)anteparo)->x2;
}

double getY2Anteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return 0.0;
    return ((Anteparo*)anteparo)->y2;
}

char* getCorAnteparo(ANTEPARO anteparo) {
    if (anteparo == NULL) return NULL;
    return ((Anteparo*)anteparo)->cor;
}

void setCorAnteparo(ANTEPARO anteparo, const char *cor) {
    if (anteparo == NULL || cor == NULL) return;
    
    Anteparo *a = (Anteparo*)anteparo;
    strncpy(a->cor, cor, sizeof(a->cor) - 1);
    a->cor[sizeof(a->cor) - 1] = '\0';
}