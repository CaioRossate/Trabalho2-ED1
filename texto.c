#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"


typedef struct {
    int id;
    float x, y; 
    char ancora;
    char *corB;
    char *corP;
    char *txto;
    char *ffamily;
    char *fweight;
    char *fsize;
} Texto;


char* alocar_e_copiar_string(const char* src) {
    char* dest = malloc(strlen(src) + 1);
    if (dest == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para string do Texto.\n");
        exit(1);
    }
    strcpy(dest, src);
    return dest;
}


TEXTO cria_texto(int id, float x, float y, char ancora, const char* corB, const char* corP, const char* txto, const char* ffamily, const char* fweight, const char* fsize) {
    Texto *t = (Texto*) malloc(sizeof(Texto));
    if (t == NULL) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para TEXTO.\n");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->ancora = ancora;

    t->corB = alocar_e_copiar_string(corB);
    t->corP = alocar_e_copiar_string(corP);
    t->txto = alocar_e_copiar_string(txto);
    t->ffamily = alocar_e_copiar_string(ffamily);
    t->fweight = alocar_e_copiar_string(fweight);
    t->fsize = alocar_e_copiar_string(fsize);

    return t;
}

void destroiTexto(TEXTO t) {
    Texto* tx = (Texto*)t;
    if (tx != NULL) {
        free(tx->corB);
        free(tx->corP);
        free(tx->txto);
        free(tx->ffamily);
        free(tx->fweight);
        free(tx->fsize);
        
        free(tx);
    }
}


int getIDTexto(TEXTO t) { return ((Texto*)t)->id; }
float getXTexto(TEXTO t) { return ((Texto*)t)->x; }
float getYTexto(TEXTO t) { return ((Texto*)t)->y; }
char getAncoraTexto(TEXTO t) { return ((Texto*)t)->ancora; }
char* getCorBTexto(TEXTO t) { return ((Texto*)t)->corB; }
char* getCorPTexto(TEXTO t) { return ((Texto*)t)->corP; }
char* getTxtoTexto(TEXTO t) { return ((Texto*)t)->txto; }
char* getFontFamilyTexto(TEXTO t) { return ((Texto*)t)->ffamily; }
char* getFontWeightTexto(TEXTO t) { return ((Texto*)t)->fweight; }
char* getFontSizeTexto(TEXTO t) { return ((Texto*)t)->fsize; }

float getAreaTexto(TEXTO t) {
    return 20.0 * strlen(((Texto*)t)->txto); 
}


void setIDTexto(TEXTO t, int id) { ((Texto*)t)->id = id; }
void setXTexto(TEXTO t, float x) { ((Texto*)t)->x = x; }
void setYTexto(TEXTO t, float y) { ((Texto*)t)->y = y; }
void setAncoraTexto(TEXTO t, char a) { ((Texto*)t)->ancora = a; }

void definir_string_texto(char** membro, const char* novo_valor) {
    free(*membro);
    *membro = malloc(strlen(novo_valor) + 1);
    if (*membro == NULL) {
        fprintf(stderr, "ERRO: Falha ao realocar memória para string do Texto durante o set.\n");
        exit(1);
    }
    strcpy(*membro, novo_valor);
}

void setCorBTexto(TEXTO t, const char* corB) {
    definir_string_texto(&((Texto*)t)->corB, corB);
}

void setCorPTexto(TEXTO t, const char* corP) {
    definir_string_texto(&((Texto*)t)->corP, corP);
}

void setTxtoTexto(TEXTO t, const char* conteudo) {
    definir_string_texto(&((Texto*)t)->txto, conteudo);
}

void setFontFamilyTexto(TEXTO t, const char* ffamily) {
    definir_string_texto(&((Texto*)t)->ffamily, ffamily);
}

void setFontWeightTexto(TEXTO t, const char* fweight) {
    definir_string_texto(&((Texto*)t)->fweight, fweight);
}

void setFontSizeTexto(TEXTO t, const char* fsize) {
    definir_string_texto(&((Texto*)t)->fsize, fsize);
}

void obtemSegmentoTexto(TEXTO t, double *x1, double *y1, double *x2, double *y2) {
    Texto *tx = (Texto*)t;
    
    if (tx == NULL || x1 == NULL || y1 == NULL || x2 == NULL || y2 == NULL) {
        return;
    }
    
    float xt = tx->x;
    float yt = tx->y;
    char ancora = tx->ancora;
    int tamanho = strlen(tx->txto);
    
    double comprimento = 10.0 * tamanho;
    
    if (ancora == 'i' || ancora == 'I') {
        *x1 = xt;
        *y1 = yt;
        *x2 = xt + comprimento;
        *y2 = yt;
    }
    else if (ancora == 'f' || ancora == 'F') {
        *x1 = xt - comprimento;
        *y1 = yt;
        *x2 = xt;
        *y2 = yt;
    }
    else if (ancora == 'm' || ancora == 'M') {
        *x1 = xt - (comprimento / 2.0);
        *y1 = yt;
        *x2 = xt + (comprimento / 2.0);
        *y2 = yt;
    }
    else {
        *x1 = xt;
        *y1 = yt;
        *x2 = xt + comprimento;
        *y2 = yt;
    }
}