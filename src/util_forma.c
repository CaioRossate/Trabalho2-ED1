#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util_forma.h"

float obterAreaForma(FORMA f, char tipo) {
    if (f == NULL) return 0.0;
    if (tipo == 'c') {
        return getAreaCirculo((CIRCULO)f);
    } else if (tipo == 'r') {
        return getAreaRetangulo((RETANGULO)f);
    } else if (tipo == 'l') {
        LINHA l = (LINHA)f;
        return (float)calculaAreaLinha(getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l));
    } else if (tipo == 't') {
        return getAreaTexto((TEXTO)f);
    }
    return 0.0;
}

void destroiForma(FORMA f, char tipo) {
    if (f == NULL) return;
    if (tipo == 'c') {
        destroiCirculo((CIRCULO)f);
    } else if (tipo == 'r') {
        destroiRetangulo((RETANGULO)f);
    } else if (tipo == 'l') {
        destroiLinha((LINHA)f);
    } else if (tipo == 't') {
        destroiTexto((TEXTO)f);
    }
}

void moveForma(FORMA forma, char tipo, double dx, double dy) {
    if (forma == NULL) return;
    if (tipo == 'c') {
        CIRCULO c = (CIRCULO)forma;
        setXCirculo(c, dx);
        setYCirculo(c, dy);
    } else if (tipo == 'r') {
        RETANGULO r = (RETANGULO)forma;
        setXRetangulo(r, dx);
        setYRetangulo(r, dy);
    } else if (tipo == 't') {
        TEXTO t = (TEXTO)forma;
        setXTexto(t, dx);
        setYTexto(t, dy);
    } else if (tipo == 'l') {
        LINHA l = (LINHA)forma;
        double x1 = getX1Linha(l);
        double y1 = getY1Linha(l);
        double x2 = getX2Linha(l);
        double y2 = getY2Linha(l);

        double difX = x2 - x1;
        double difY = y2 - y1;

        definirX1Linha(l, dx);
        definirY1Linha(l, dy);
        definirX2Linha(l, dx + difX);
        definirY2Linha(l, dy + difY);
    }
}


double obtemXforma(FORMA f, char tipo){
    if (f == NULL) return 0.0;
    if (tipo == 'c') {
        return getXCirculo((CIRCULO)f);
    } else if (tipo == 'r') {
        return getXRetangulo((RETANGULO)f);
    } else if (tipo == 't') {
        return getXTexto((TEXTO)f);
    } else if (tipo == 'l') {
        return getX1Linha((LINHA)f);
    }
    return 0.0;
}


double obtemYforma(FORMA f, char tipo){
    if (f == NULL) return 0.0;
    if (tipo == 'c') {
        return getYCirculo((CIRCULO)f);
    } else if (tipo == 'r') {
        return getYRetangulo((RETANGULO)f);
    } else if (tipo == 't') {
        return getYTexto((TEXTO)f);
    } else if (tipo == 'l') {
        return getY1Linha((LINHA)f);
    }
    return 0.0;
}


static int hexToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

void obterCorComplementar(const char *cor, char *corComplementar) {
    if (cor == NULL || corComplementar == NULL) {
        strcpy(corComplementar, "#000000");
        return;
    }
    
    if (cor[0] != '#' || strlen(cor) != 7) {
        strcpy(corComplementar, "#000000");
        return;
    }
    
    int r = hexToInt(cor[1]) * 16 + hexToInt(cor[2]);
    int g = hexToInt(cor[3]) * 16 + hexToInt(cor[4]);
    int b = hexToInt(cor[5]) * 16 + hexToInt(cor[6]);
    
    int rComp = 255 - r;
    int gComp = 255 - g;
    int bComp = 255 - b;
    
    // Retorna em formato #RRGGBB
    sprintf(corComplementar, "#%02X%02X%02X", rComp, gComp, bComp);
}

int obtemIDforma(FORMA f, char tipo) {
    if (f == NULL) return -1;
    if (tipo == 'c') {
        return getIDCirculo((CIRCULO)f);
    } else if (tipo == 'r') {
        return getIDRetangulo((RETANGULO)f);
    } else if (tipo == 'l') {
        return getIdLinha((LINHA)f);
    } else if (tipo == 't') {
        return getIDTexto((TEXTO)f);
    }
    return -1;
}