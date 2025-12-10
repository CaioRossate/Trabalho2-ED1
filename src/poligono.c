#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include "poligono.h"

typedef struct vertice {
    double x;
    double y;
    struct vertice *proximo;
} Vertice;

typedef struct poligono {
    Vertice *primeiro;
    Vertice *ultimo;
    int numVertices;
} Poligono;

POLIGONO criaPoligono() {
    Poligono *p = (Poligono*)malloc(sizeof(Poligono));
    if (p == NULL) {
        fprintf(stderr, "ERRO: Não foi possível alocar memória para o polígono\n");
        exit(1);
    }
    
    p->primeiro = NULL;
    p->ultimo = NULL;
    p->numVertices = 0;
    
    return p;
}

void adicionaVertice(POLIGONO p, double x, double y) {
    if (p == NULL) return;
    
    Poligono *poli = (Poligono*)p;
    
    Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
    if (novo == NULL) {
        fprintf(stderr, "ERRO: Não foi possível alocar memória para vértice\n");
        exit(1);
    }
    
    novo->x = x;
    novo->y = y;
    novo->proximo = NULL;
    
    if (poli->ultimo == NULL) {
        // Primeiro vértice
        poli->primeiro = novo;
        poli->ultimo = novo;
    } else {
        // Adiciona no final
        poli->ultimo->proximo = novo;
        poli->ultimo = novo;
    }
    
    poli->numVertices++;
}

void adicionaSegmento(POLIGONO p) {
    if (p == NULL) return;
    
    Poligono *poli = (Poligono*)p;
    // Verifica se há pelo menos dois vértices
    if (poli->numVertices < 2) {
        fprintf(stderr, "AVISO: Menos de 2 vértices para formar segmento\n");
        return;
    }
}

int getBoundingBox(POLIGONO p, double *minX, double *minY, double *maxX, double *maxY) {
    if (p == NULL || minX == NULL || minY == NULL || maxX == NULL || maxY == NULL) {
        return 0;
    }
    
    Poligono *poli = (Poligono*)p;
    
    if (poli->numVertices == 0) {
        *minX = 0.0;
        *minY = 0.0;
        *maxX = 0.0;
        *maxY = 0.0;
        return 0;
    }
    
    // Inicializa com valores extremos
    *minX = DBL_MAX;
    *minY = DBL_MAX;
    *maxX = -DBL_MAX;
    *maxY = -DBL_MAX;
    
    // Percorre todos os vértices
    Vertice *atual = poli->primeiro;
    while (atual != NULL) {
        if (atual->x < *minX) *minX = atual->x;
        if (atual->x > *maxX) *maxX = atual->x;
        if (atual->y < *minY) *minY = atual->y;
        if (atual->y > *maxY) *maxY = atual->y;
        
        atual = atual->proximo;
    }
    
    return poli->numVertices;
}

void obtemVertice(POLIGONO p, int indice, double *x, double *y) {
    if (p == NULL || x == NULL || y == NULL) return;
    
    Poligono *poli = (Poligono*)p;
    
    if (indice < 0 || indice >= poli->numVertices) {
        *x = 0.0;
        *y = 0.0;
        return;
    }
    
    // Percorre até o índice desejado
    Vertice *atual = poli->primeiro;
    for (int i = 0; i < indice && atual != NULL; i++) {
        atual = atual->proximo;
    }
    
    if (atual != NULL) {
        *x = atual->x;
        *y = atual->y;
    }
}

void liberaPoligono(POLIGONO p) {
    if (p == NULL) return;
    
    Poligono *poli = (Poligono*)p;
    
    Vertice *atual = poli->primeiro;
    while (atual != NULL) {
        Vertice *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(poli);
}

// Algoritmo de Ray Casting para verificar se ponto está dentro do polígono
bool isInside(POLIGONO p, double x, double y) {
    if (p == NULL) return false;
    
    Poligono *poli = (Poligono*)p;
    
    if (poli->numVertices < 3) return false;
    
    bool dentro = false;
    
    Vertice *v1 = poli->primeiro;
    Vertice *v2 = v1->proximo;
    
    // Percorre todos os segmentos do polígono
    while (v2 != NULL) {
        double x1 = v1->x;
        double y1 = v1->y;
        double x2 = v2->x;
        double y2 = v2->y;
        
        // Verifica se o raio horizontal cruza o segmento
        if (((y1 > y) != (y2 > y)) &&
            (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1)) {
            dentro = !dentro;
        }
        
        v1 = v2;
        v2 = v2->proximo;
    }
    
    // Fecha o polígono: verifica o segmento do último vértice ao primeiro
    v2 = poli->primeiro;
    double x1 = v1->x;
    double y1 = v1->y;
    double x2 = v2->x;
    double y2 = v2->y;
    
    if (((y1 > y) != (y2 > y)) &&
        (x < (x2 - x1) * (y - y1) / (y2 - y1) + x1)) {
        dentro = !dentro;
    }
    
    return dentro;
}

int getNumVertices(POLIGONO p) {
    if (p == NULL) return 0;
    return ((Poligono*)p)->numVertices;
}

void* getPrimeiroVertice(POLIGONO p) {
    if (p == NULL) return NULL;
    return ((Poligono*)p)->primeiro;
}

void* getProximoVertice(void *v) {
    if (v == NULL) return NULL;
    return ((Vertice*)v)->proximo;
}

void getCoordenadaVertice(void *v, double *x, double *y) {
    if (v == NULL || x == NULL || y == NULL) return;
    Vertice *vert = (Vertice*)v;
    *x = vert->x;
    *y = vert->y;
}