#include <stdio.h>
#include "arvore.h"
#include "anteparo.h"
#include "geometria.h"
#include <stdlib.h>
#include <math.h>

typedef struct no_arvore {
    ANTEPARO anteparo;
    double yReferencia;
    struct no_arvore *esquerda;
    struct no_arvore *direita;
} NoArvore;

typedef struct arvore {
    NoArvore *raiz;
    int tamanho;
} Arvore;

ARVORE criaArvore() {
    Arvore *arv = (Arvore*)malloc(sizeof(Arvore));
    if (arv == NULL) return NULL;
    
    arv->raiz = NULL;
    arv->tamanho = 0;
    
    return arv;
}

void destroiNoArvore(NoArvore *no) {
    if (no == NULL) return;
    
    destroiNoArvore(no->esquerda);
    destroiNoArvore(no->direita);
    free(no);
}

void destroiArvore(ARVORE arvore) {
    if (arvore == NULL) return;
    
    Arvore *arv = (Arvore*)arvore;
    destroiNoArvore(arv->raiz);
    free(arv);
}

bool arvoreVazia(ARVORE arvore) {
    if (arvore == NULL) return true;
    return ((Arvore*)arvore)->raiz == NULL;
}

NoArvore* criaNoArvore(ANTEPARO ant, double yRef) {
    NoArvore *no = (NoArvore*)malloc(sizeof(NoArvore));
    if (no == NULL) return NULL;
    
    no->anteparo = ant;
    no->yReferencia = yRef;
    no->esquerda = NULL;
    no->direita = NULL;
    
    return no;
}

NoArvore* insereNoArvore(NoArvore *no, ANTEPARO ant, double yRef) {
    if (no == NULL) {
        return criaNoArvore(ant, yRef);
    }
    
    int cmp = comparaAnteparos(ant, no->anteparo, yRef);
    
    if (cmp < 0) {
        no->esquerda = insereNoArvore(no->esquerda, ant, yRef);
    } else if (cmp > 0) {
        no->direita = insereNoArvore(no->direita, ant, yRef);
    }
    // Se cmp == 0, já existe (não insere duplicatas)
    
    return no;
}

void insereArvore(ARVORE arvore, ANTEPARO ant, double yReferencia) {
    if (arvore == NULL || ant == NULL) return;
    
    Arvore *arv = (Arvore*)arvore;
    arv->raiz = insereNoArvore(arv->raiz, ant, yReferencia);
    arv->tamanho++;
}

NoArvore* encontraMenor(NoArvore *no) {
    while (no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}

NoArvore* removeNoArvore(NoArvore *no, ANTEPARO ant, double yRef, bool *removido) {
    if (no == NULL) {
        *removido = false;
        return NULL;
    }
    
    int cmp = comparaAnteparos(ant, no->anteparo, yRef);
    
    if (cmp < 0) {
        no->esquerda = removeNoArvore(no->esquerda, ant, yRef, removido);
    } else if (cmp > 0) {
        no->direita = removeNoArvore(no->direita, ant, yRef, removido);
    } else {
        // Encontrou o nó a remover
        *removido = true;
        
        if (no->esquerda == NULL) {
            NoArvore *temp = no->direita;
            free(no);
            return temp;
        } else if (no->direita == NULL) {
            NoArvore *temp = no->esquerda;
            free(no);
            return temp;
        }
        
        // Nó com dois filhos: pega o sucessor (menor da direita)
        NoArvore *temp = encontraMenor(no->direita);
        no->anteparo = temp->anteparo;
        no->yReferencia = temp->yReferencia;
        no->direita = removeNoArvore(no->direita, temp->anteparo, temp->yReferencia, removido);
    }
    
    return no;
}

bool removeArvore(ARVORE arvore, ANTEPARO ant) {
    if (arvore == NULL || ant == NULL) return false;
    
    Arvore *arv = (Arvore*)arvore;
    bool removido = false;
    
    // Usa yReferencia do anteparo
    double yRef = (getY1Anteparo(ant) + getY2Anteparo(ant)) / 2.0;
    
    arv->raiz = removeNoArvore(arv->raiz, ant, yRef, &removido);
    
    if (removido) {
        arv->tamanho--;
    }
    
    return removido;
}

/**
 * @brief Calcula a interseção de um raio com um anteparo.
 * @return Distância até a interseção, ou -1 se não intersecta
 */
static double intersecaoRaioAnteparo(double px, double py, double angulo, ANTEPARO ant) {
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
    
    if (fabs(denominador) < 1e-9) {
        // Raio paralelo ao anteparo
        return -1.0;
    }
    
    double t = ((x1 - px) * sy - (y1 - py) * sx) / denominador;
    double u = ((x1 - px) * dy - (y1 - py) * dx) / denominador;
    
    // Verifica se a interseção está no raio (t >= 0) e no anteparo (0 <= u <= 1)
    if (t >= 0.0 && u >= 0.0 && u <= 1.0) {
        return t; // Distância até a interseção
    }
    
    return -1.0;
}

void buscaMaisProximoRec(NoArvore *no, double x, double y, double angulo, 
                         ANTEPARO *melhor, double *melhorDist) {
    if (no == NULL) return;
    
    // Busca em toda a árvore
    buscaMaisProximoRec(no->esquerda, x, y, angulo, melhor, melhorDist);
    
    double dist = intersecaoRaioAnteparo(x, y, angulo, no->anteparo);
    
    if (dist >= 0.0 && ((*melhor) == NULL || dist < *melhorDist)) {
        *melhor = no->anteparo;
        *melhorDist = dist;
    }
    
    buscaMaisProximoRec(no->direita, x, y, angulo, melhor, melhorDist);
}

ANTEPARO buscaAnteparoMaisProximo(ARVORE arvore, double x, double y, double angulo) {
    if (arvore == NULL) return NULL;
    
    Arvore *arv = (Arvore*)arvore;
    ANTEPARO melhor = NULL;
    double melhorDist = -1.0;
    
    buscaMaisProximoRec(arv->raiz, x, y, angulo, &melhor, &melhorDist);
    
    return melhor;
}

int tamanhoArvore(ARVORE arvore) {
    if (arvore == NULL) return 0;
    return ((Arvore*)arvore)->tamanho;
}

void limpaArvore(ARVORE arvore) {
    if (arvore == NULL) return;
    
    Arvore *arv = (Arvore*)arvore;
    destroiNoArvore(arv->raiz);
    arv->raiz = NULL;
    arv->tamanho = 0;
}