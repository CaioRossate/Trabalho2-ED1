#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct {
    int id;
    float x, y, w, h;
    char *corP;
    char *corB;
} Retangulo;

RETANGULO cria_retangulo(int id, float x, float y, float w, float h, const char* corP, const char* corB) {
    Retangulo* r = malloc(sizeof(Retangulo));
    if (r == NULL) {
        printf("Erro ao alocar memória para retângulo");
        exit(1);
    }

    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;

    r->corP = malloc(strlen(corP) + 1);
    if (r->corP == NULL) {
        printf("Erro ao alocar memória para cor de preenchimento");
        exit(1);
    }
    strcpy(r->corP, corP);

    r->corB = malloc(strlen(corB) + 1);
    if (r->corB == NULL) {
        printf("Erro ao alocar memória para cor da borda");
        exit(1);
    }
    strcpy(r->corB, corB);

    return r;
}

void destroiRetangulo(RETANGULO r) {
    Retangulo* ret = (Retangulo*)r;
    if (ret != NULL) {
        if (ret->corP != NULL) {
            free(ret->corP);
        }
        if (ret->corB != NULL) {
            free(ret->corB);
        }
        free(ret);
    }
}

int getIDRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->id;
}

float getXRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->x;
}

float getYRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->y;
}

float getLarguraRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->w;
}

float getAlturaRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->h;
}

char* getCorPRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->corP;
}

char* getCorBRetangulo(RETANGULO r) {
    return ((Retangulo*)r)->corB;
}

float getAreaRetangulo(RETANGULO r) {
    Retangulo* ret = (Retangulo*)r;
    return ret->w * ret->h;
}

void setIDRetangulo(RETANGULO r, int id) {
    ((Retangulo*)r)->id = id;
}

void setXRetangulo(RETANGULO r, float x) {
    ((Retangulo*)r)->x = x;
}

void setYRetangulo(RETANGULO r, float y) {
    ((Retangulo*)r)->y = y;
}

void setLarguraRetangulo(RETANGULO r, float w) {
    ((Retangulo*)r)->w = w;
}

void setAlturaRetangulo(RETANGULO r, float h) {
    ((Retangulo*)r)->h = h;
}

void setCorPRetangulo(RETANGULO r, const char* corP) {
    Retangulo* ret = (Retangulo*)r;
    free(ret->corP);
    ret->corP = malloc(strlen(corP) + 1);
    strcpy(ret->corP, corP);
}

void setCorBRetangulo(RETANGULO r, const char* corB) {
    Retangulo* ret = (Retangulo*)r;
    free(ret->corB);
    ret->corB = malloc(strlen(corB) + 1);
    strcpy(ret->corB, corB);
}
