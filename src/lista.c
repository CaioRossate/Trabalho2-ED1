#include <stdio.h>
#include "lista.h"
#include <stdlib.h>

typedef struct no {
    void *dado;
    char tipo;
    struct no *proximo;
    struct no *anterior;
} No;

typedef struct lista {
    No *primeiro;
    No *ultimo;
    int tamanho;
} Lista;

LISTA criaLista() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) return NULL;
    
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    
    return lista;
}

void destroiLista(LISTA lista) {
    if (lista == NULL) return;
    
    Lista *l = (Lista*)lista;
    No *atual = l->primeiro;
    
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(l);
}

bool listaVazia(LISTA lista) {
    if (lista == NULL) return true;
    return ((Lista*)lista)->tamanho == 0;
}

void insereLista(LISTA lista, void *dado, char tipo) {
    if (lista == NULL) return;
    
    Lista *l = (Lista*)lista;
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) return;
    
    novo->dado = dado;
    novo->tipo = tipo;
    novo->proximo = NULL;
    novo->anterior = l->ultimo;
    
    if (l->ultimo != NULL) {
        l->ultimo->proximo = novo;
    } else {
        l->primeiro = novo;
    }
    
    l->ultimo = novo;
    l->tamanho++;
}

void insereInicioLista(LISTA lista, void *dado, char tipo) {
    if (lista == NULL) return;
    
    Lista *l = (Lista*)lista;
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) return;
    
    novo->dado = dado;
    novo->tipo = tipo;
    novo->proximo = l->primeiro;
    novo->anterior = NULL;
    
    if (l->primeiro != NULL) {
        l->primeiro->anterior = novo;
    } else {
        l->ultimo = novo;
    }
    
    l->primeiro = novo;
    l->tamanho++;
}

void* removePrimeiroLista(LISTA lista) {
    if (lista == NULL) return NULL;
    
    Lista *l = (Lista*)lista;
    if (l->primeiro == NULL) return NULL;
    
    No *removido = l->primeiro;
    void *dado = removido->dado;
    
    l->primeiro = removido->proximo;
    
    if (l->primeiro != NULL) {
        l->primeiro->anterior = NULL;
    } else {
        l->ultimo = NULL;
    }
    
    free(removido);
    l->tamanho--;
    
    return dado;
}

void* removeUltimoLista(LISTA lista) {
    if (lista == NULL) return NULL;
    
    Lista *l = (Lista*)lista;
    if (l->ultimo == NULL) return NULL;
    
    No *removido = l->ultimo;
    void *dado = removido->dado;
    
    l->ultimo = removido->anterior;
    
    if (l->ultimo != NULL) {
        l->ultimo->proximo = NULL;
    } else {
        l->primeiro = NULL;
    }
    
    free(removido);
    l->tamanho--;
    
    return dado;
}

void* removeNoLista(LISTA lista, void *no) {
    if (lista == NULL || no == NULL) return NULL;
    
    Lista *l = (Lista*)lista;
    No *n = (No*)no;
    
    if (n->anterior != NULL) {
        n->anterior->proximo = n->proximo;
    } else {
        l->primeiro = n->proximo;
    }
    
    if (n->proximo != NULL) {
        n->proximo->anterior = n->anterior;
    } else {
        l->ultimo = n->anterior;
    }
    
    void *dado = n->dado;
    free(n);
    l->tamanho--;
    
    return dado;
}

void* obtemPrimeiroNo(LISTA lista) {
    if (lista == NULL) return NULL;
    return ((Lista*)lista)->primeiro;
}

void* obtemUltimoNo(LISTA lista) {
    if (lista == NULL) return NULL;
    return ((Lista*)lista)->ultimo;
}

void* obtemProximoNo(void *no) {
    if (no == NULL) return NULL;
    return ((No*)no)->proximo;
}

void* obtemAnteriorNo(void *no) {
    if (no == NULL) return NULL;
    return ((No*)no)->anterior;
}

void* obtemDado(void *no) {
    if (no == NULL) return NULL;
    return ((No*)no)->dado;
}

char obtemTipo(void *no) {
    if (no == NULL) return '\0';
    return ((No*)no)->tipo;
}

void setDado(void *no, void *dado) {
    if (no == NULL) return;
    ((No*)no)->dado = dado;
}

void setTipo(void *no, char tipo) {
    if (no == NULL) return;
    ((No*)no)->tipo = tipo;
}

int obtemTamanhoLista(LISTA lista) {
    if (lista == NULL) return 0;
    return ((Lista*)lista)->tamanho;
}

void* buscaLista(LISTA lista, void *chave, int (*compara)(void*, void*)) {
    if (lista == NULL || compara == NULL) return NULL;
    
    Lista *l = (Lista*)lista;
    No *atual = l->primeiro;
    
    while (atual != NULL) {
        if (compara(atual->dado, chave) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}