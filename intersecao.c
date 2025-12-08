#include "intersecao.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define EPSILON 1e-6

bool intersecao_circulo_circulo(CIRCULO c1, CIRCULO c2) {
    float x1 = getXCirculo(c1);
    float y1 = getYCirculo(c1);
    float r1 = getRaioCirculo(c1);

    float x2 = getXCirculo(c2);
    float y2 = getYCirculo(c2);
    float r2 = getRaioCirculo(c2);

    float dx = x1 - x2;
    float dy = y1 - y2;
    float dist_centros_sq = dx * dx + dy * dy;
    
    float raios_somados = r1 + r2;
    float raios_somados_sq = raios_somados * raios_somados;

    return dist_centros_sq <= raios_somados_sq;
}

bool intersecao_retangulo_retangulo(RETANGULO r1, RETANGULO r2) {
    float x1 = getXRetangulo(r1);
    float y1 = getYRetangulo(r1);
    float w1 = getLarguraRetangulo(r1);
    float h1 = getAlturaRetangulo(r1);

    float x2 = getXRetangulo(r2);
    float y2 = getYRetangulo(r2);
    float w2 = getLarguraRetangulo(r2);
    float h2 = getAlturaRetangulo(r2);

    
    if (x1 + w1 <= x2) return false;
    if (x2 + w2 <= x1) return false;
    if (y1 + h1 <= y2) return false;
    if (y2 + h2 <= y1) return false;

    return true;
}


bool intersecao_circulo_retangulo(CIRCULO c, RETANGULO r) {
    float Cx = getXCirculo(c);
    float Cy = getYCirculo(c);
    float Raio = getRaioCirculo(c);

    float Rx = getXRetangulo(r);
    float Ry = getYRetangulo(r);
    float Rw = getLarguraRetangulo(r);
    float Rh = getAlturaRetangulo(r);

    float Px = fmaxf(Rx, fminf(Cx, Rx + Rw));
    float Py = fmaxf(Ry, fminf(Cy, Ry + Rh));

    float dx = Cx - Px;
    float dy = Cy - Py;
    float dist_sq = dx * dx + dy * dy;

    return dist_sq <= (Raio * Raio);
}

bool intersecao_linha_circulo(LINHA l, CIRCULO c) {
    float x1 = getX1Linha(l);
    float y1 = getY1Linha(l);
    float x2 = getX2Linha(l);
    float y2 = getY2Linha(l);

    float Cx = getXCirculo(c);
    float Cy = getYCirculo(c);
    float Raio = getRaioCirculo(c);

    float dx_linha = x2 - x1;
    float dy_linha = y2 - y1;
    float len_sq = dx_linha * dx_linha + dy_linha * dy_linha;

    if (len_sq == 0.0) {
        float dist_sq = (Cx - x1) * (Cx - x1) + (Cy - y1) * (Cy - y1);
        return dist_sq <= (Raio * Raio);
    }

    float t = ((Cx - x1) * dx_linha + (Cy - y1) * dy_linha) / len_sq;

    if (t < 0) t = 0;
    if (t > 1) t = 1;

    float Px = x1 + t * dx_linha;
    float Py = y1 + t * dy_linha;

    float dx = Cx - Px;
    float dy = Cy - Py;
    float dist_sq = dx * dx + dy * dy;

    return dist_sq <= (Raio * Raio);
}

bool intersecao_linha_retangulo(LINHA l, RETANGULO r) {
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);

    double Rx = getXRetangulo(r);
    double Ry = getYRetangulo(r);
    double Rw = getLarguraRetangulo(r);
    double Rh = getAlturaRetangulo(r);
    
    double Rx_fim = Rx + Rw;
    double Ry_fim = Ry + Rh;

    
    if (x1 >= Rx && x1 <= Rx_fim && y1 >= Ry && y1 <= Ry_fim) {
        return true;
    }
    if (x2 >= Rx && x2 <= Rx_fim && y2 >= Ry && y2 <= Ry_fim) {
        return true;
    }

    
    double x3, y3, x4, y4;
    double D, Nt, Nu, t, u;
    
    x3 = Rx; y3 = Ry;
    x4 = Rx_fim; y4 = Ry;
    D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (fabs(D) > EPSILON) {
        Nt = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        Nu = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        t = Nt / D;
        u = -Nu / D; 
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) return true;
    }

    x3 = Rx; y3 = Ry_fim;
    x4 = Rx_fim; y4 = Ry_fim;
    D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (fabs(D) > EPSILON) {
        Nt = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        Nu = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        t = Nt / D;
        u = -Nu / D; 
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) return true;
    }

    x3 = Rx; y3 = Ry;
    x4 = Rx; y4 = Ry_fim;
    D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (fabs(D) > EPSILON) {
        Nt = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        Nu = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        t = Nt / D;
        u = -Nu / D; 
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) return true;
    }

    x3 = Rx_fim; y3 = Ry;
    x4 = Rx_fim; y4 = Ry_fim;
    D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (fabs(D) > EPSILON) {
        Nt = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
        Nu = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        t = Nt / D;
        u = -Nu / D; 
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) return true;
    }

    return false;
}

bool intersecao_linha_linha(LINHA l1, LINHA l2) {
    float x1 = getX1Linha(l1);
    float y1 = getY1Linha(l1);
    float x2 = getX2Linha(l1);
    float y2 = getY2Linha(l1);

    float x3 = getX1Linha(l2);
    float y3 = getY1Linha(l2);
    float x4 = getX2Linha(l2);
    float y4 = getY2Linha(l2);

    float D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (fabs(D) < 1e-6) {
        return false; 
    }

    float Nt = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
    float Nu = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);

    float t = Nt / D;
    float u = -Nu / D; 

    return (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0); 
}

bool intersecao_texto_circulo(TEXTO t, CIRCULO c) {
    double x1, y1, x2, y2;
    obtemSegmentoTexto(t, &x1, &y1, &x2, &y2);
    
    LINHA linhaTemp = criaLinha(-1, x1, y1, x2, y2, "black");
    
    bool resultado = intersecao_linha_circulo(linhaTemp, c);
    
    destroiLinha(linhaTemp);
    
    return resultado;
}

bool intersecao_texto_retangulo(TEXTO t, RETANGULO r) {
    double x1, y1, x2, y2;
    obtemSegmentoTexto(t, &x1, &y1, &x2, &y2);
    
    LINHA linhaTemp = criaLinha(-1, x1, y1, x2, y2, "black");
    
    bool resultado = intersecao_linha_retangulo(linhaTemp, r);
    
    destroiLinha(linhaTemp);
    
    return resultado;
}

bool intersecao_texto_linha(TEXTO t, LINHA l) {
    double x1, y1, x2, y2;
    obtemSegmentoTexto(t, &x1, &y1, &x2, &y2);
    
    LINHA linhaTemp = criaLinha(-1, x1, y1, x2, y2, "black");
    
    bool resultado = intersecao_linha_linha(linhaTemp, l);
    
    destroiLinha(linhaTemp);
    
    return resultado;
}

bool intersecao_texto_texto(TEXTO t1, TEXTO t2) {
    double x1a, y1a, x2a, y2a;
    double x1b, y1b, x2b, y2b;
    
    obtemSegmentoTexto(t1, &x1a, &y1a, &x2a, &y2a);
    obtemSegmentoTexto(t2, &x1b, &y1b, &x2b, &y2b);
    
    LINHA linha1 = criaLinha(-1, x1a, y1a, x2a, y2a, "black");
    LINHA linha2 = criaLinha(-1, x1b, y1b, x2b, y2b, "black");
    
    bool resultado = intersecao_linha_linha(linha1, linha2);
    
    destroiLinha(linha1);
    destroiLinha(linha2);
    
    return resultado;
}

bool verificaIntersecao(FORMA formaA, char tipoA, FORMA formaB, char tipoB) {
    if (tipoA > tipoB) {
        return verificaIntersecao(formaB, tipoB, formaA, tipoA);
    }
    
    
    if (tipoA == 'c') {
        if (tipoB == 'c') {
            return intersecao_circulo_circulo((CIRCULO)formaA, (CIRCULO)formaB);
        }
        else if (tipoB == 'l') {
            return intersecao_linha_circulo((LINHA)formaB, (CIRCULO)formaA);
        }
        else if (tipoB == 'r') {
            return intersecao_circulo_retangulo((CIRCULO)formaA, (RETANGULO)formaB);
        }
        else if (tipoB == 't') {
            return intersecao_texto_circulo((TEXTO)formaB, (CIRCULO)formaA);
        }
    }
    
    else if (tipoA == 'l') {
        if (tipoB == 'l') {
            return intersecao_linha_linha((LINHA)formaA, (LINHA)formaB);
        }
        else if (tipoB == 'r') {
            return intersecao_linha_retangulo((LINHA)formaA, (RETANGULO)formaB);
        }
        else if (tipoB == 't') {
            return intersecao_texto_linha((TEXTO)formaB, (LINHA)formaA);
        }
    }
    
    else if (tipoA == 'r') {
        if (tipoB == 'r') {
            return intersecao_retangulo_retangulo((RETANGULO)formaA, (RETANGULO)formaB);
        }
        else if (tipoB == 't') {
            return intersecao_texto_retangulo((TEXTO)formaB, (RETANGULO)formaA);
        }
    }
    
    else if (tipoA == 't') {
        if (tipoB == 't') {
            return intersecao_texto_texto((TEXTO)formaA, (TEXTO)formaB);
        }
    }
    
    
    return false; 
}