#include "qry.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "util_forma.h"
#include "anteparo.h"
#include "poligono.h"
#include "visibilidade.h"
#include "lista.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define TAM_LINHA_MAX 512
#define EPSILON_GEOM 1e-9

int comparaAnteparos(ANTEPARO ant1, ANTEPARO ant2, double yRef) {
    if (ant1 == NULL || ant2 == NULL) return 0;

    double x11 = getX1Anteparo(ant1);
    double y11 = getY1Anteparo(ant1);
    double x12 = getX2Anteparo(ant1);
    double y12 = getY2Anteparo(ant1);

    double x21 = getX1Anteparo(ant2);
    double y21 = getY1Anteparo(ant2);
    double x22 = getX2Anteparo(ant2);
    double y22 = getY2Anteparo(ant2);

    double xi1, xi2;

    // calcula interseção do anteparo com a linha y = yRef
    if (fabs(y12 - y11) < EPSILON_GEOM) {
        xi1 = (x11 + x12) / 2.0;
    } else {
        double t1 = (yRef - y11) / (y12 - y11);
        if (t1 < 0.0) t1 = 0.0;
        if (t1 > 1.0) t1 = 1.0;
        xi1 = x11 + t1 * (x12 - x11);
    }

    if (fabs(y22 - y21) < EPSILON_GEOM) {
        xi2 = (x21 + x22) / 2.0;
    } else {
        double t2 = (yRef - y21) / (y22 - y21);
        if (t2 < 0.0) t2 = 0.0;
        if (t2 > 1.0) t2 = 1.0;
        xi2 = x21 + t2 * (x22 - x21);
    }

    if (fabs(xi1 - xi2) < EPSILON_GEOM) return 0;
    return (xi1 < xi2) ? -1 : 1;
}

bool anteparosIntersectam(ANTEPARO ant1, ANTEPARO ant2, double *x, double *y) {
    if (ant1 == NULL || ant2 == NULL) return false;

    double x1 = getX1Anteparo(ant1), y1 = getY1Anteparo(ant1);
    double x2 = getX2Anteparo(ant1), y2 = getY2Anteparo(ant1);
    double x3 = getX1Anteparo(ant2), y3 = getY1Anteparo(ant2);
    double x4 = getX2Anteparo(ant2), y4 = getY2Anteparo(ant2);

    double denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (fabs(denom) < EPSILON_GEOM) return false;

    double px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    double py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    // verifica se o ponto está dentro dos dois segmentos (com margem)
    double minx1 = fmin(x1,x2)-EPSILON_GEOM, maxx1 = fmax(x1,x2)+EPSILON_GEOM;
    double miny1 = fmin(y1,y2)-EPSILON_GEOM, maxy1 = fmax(y1,y2)+EPSILON_GEOM;
    double minx2 = fmin(x3,x4)-EPSILON_GEOM, maxx2 = fmax(x3,x4)+EPSILON_GEOM;
    double miny2 = fmin(y3,y4)-EPSILON_GEOM, maxy2 = fmax(y3,y4)+EPSILON_GEOM;

    if (px >= minx1 && px <= maxx1 && py >= miny1 && py <= maxy1 &&
        px >= minx2 && px <= maxx2 && py >= miny2 && py <= maxy2) {
        if (x) *x = px;
        if (y) *y = py;
        return true;
    }

    return false;
}

bool pontoNoPoligono(double px, double py, double *verticesX, double *verticesY, int numVertices) {
    if (verticesX == NULL || verticesY == NULL || numVertices < 3) return false;
    bool dentro = false;
    for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
        double xi = verticesX[i], yi = verticesY[i];
        double xj = verticesX[j], yj = verticesY[j];
        if ( ((yi > py) != (yj > py)) && (px < (xj - xi) * (py - yi) / (yj - yi + 0.0) + xi) ) {
            dentro = !dentro;
        }
    }
    return dentro;
}

double distanciaPontoAnteparo(double px, double py, ANTEPARO ant) {
    if (ant == NULL) return 1e100;
    double x1 = getX1Anteparo(ant), y1 = getY1Anteparo(ant);
    double x2 = getX2Anteparo(ant), y2 = getY2Anteparo(ant);

    double dx = x2 - x1;
    double dy = y2 - y1;
    double l2 = dx*dx + dy*dy;
    if (l2 == 0.0) return hypot(px - x1, py - y1);

    double t = ((px - x1)*dx + (py - y1)*dy) / l2;
    if (t < 0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    double projx = x1 + t * dx;
    double projy = y1 + t * dy;
    return hypot(px - projx, py - projy);
}
static double distanciaPontoSegmento(double px, double py, double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double l2 = dx*dx + dy*dy;
    if (l2 == 0.0) return hypot(px - x1, py - y1);
    double t = ((px - x1)*dx + (py - y1)*dy) / l2;
    if (t < 0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    double projx = x1 + t * dx;
    double projy = y1 + t * dy;
    return hypot(px - projx, py - projy);
}

// Determina a orientação de três pontos (ax,ay), (bx,by), (cx,cy)
static int orientacao(double ax, double ay, double bx, double by, double cx, double cy) {
    double v = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    if (fabs(v) < EPSILON_GEOM) return 0;
    return (v > 0.0) ? 1 : 2;
}

static bool estaNoSegmento(double ax, double ay, double bx, double by, double px, double py) {
    if (px <= fmax(ax, bx) + EPSILON_GEOM && px + EPSILON_GEOM >= fmin(ax, bx) &&
        py <= fmax(ay, by) + EPSILON_GEOM && py + EPSILON_GEOM >= fmin(ay, by))
        return true;
    return false;
}

static bool segmentosInterceptam(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    int o1 = orientacao(x1,y1,x2,y2,x3,y3);
    int o2 = orientacao(x1,y1,x2,y2,x4,y4);
    int o3 = orientacao(x3,y3,x4,y4,x1,y1);
    int o4 = orientacao(x3,y3,x4,y4,x2,y2);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && estaNoSegmento(x1,y1,x2,y2,x3,y3)) return true;
    if (o2 == 0 && estaNoSegmento(x1,y1,x2,y2,x4,y4)) return true;
    if (o3 == 0 && estaNoSegmento(x3,y3,x4,y4,x1,y1)) return true;
    if (o4 == 0 && estaNoSegmento(x3,y3,x4,y4,x2,y2)) return true;
    return false;
}

// Verifica se polígono intercepta ponto, círculo, retângulo ou linha
static bool poligonoInterceptaPonto(POLIGONO poli, double px, double py) {
    if (poli == NULL) return false;
    if (isInside(poli, px, py)) return true;

    void *v = getPrimeiroVertice(poli);
    if (v == NULL) return false;
    void *prev = v;
    double xprev, yprev;
    getCoordenadaVertice(prev, &xprev, &yprev);
    v = getProximoVertice(v);
    while (v != NULL) {
        double xv, yv;
        getCoordenadaVertice(v, &xv, &yv);
        double d = distanciaPontoSegmento(px, py, xprev, yprev, xv, yv);
        if (d <= EPSILON_GEOM) return true;
        xprev = xv; yprev = yv;
        v = getProximoVertice(v);
    }
    return false;
}

static bool poligonoInterceptaCirculo(POLIGONO poli, CIRCULO c) {
    if (poli == NULL || c == NULL) return false;
    double cx = getXCirculo(c), cy = getYCirculo(c), r = getRaioCirculo(c);
    if (isInside(poli, cx, cy)) return true;

    // verifica distância mínima de cada aresta ao centro do círculo
    void *v = getPrimeiroVertice(poli);
    if (v == NULL) return false;
    double x1,y1;
    getCoordenadaVertice(v, &x1, &y1);
    v = getProximoVertice(v);
    while (v != NULL) {
        double x2,y2;
        getCoordenadaVertice(v, &x2, &y2);
        if (distanciaPontoSegmento(cx, cy, x1,y1, x2,y2) <= r + EPSILON_GEOM) return true;
        x1 = x2; y1 = y2;
        v = getProximoVertice(v);
    }
    return false;
}

static bool poligonoInterceptaRetangulo(POLIGONO poli, RETANGULO rect) {
    if (poli == NULL || rect == NULL) return false;
    double x = getXRetangulo(rect), y = getYRetangulo(rect);
    double w = getLarguraRetangulo(rect), h = getAlturaRetangulo(rect);

    
    if (isInside(poli, x, y)) return true;
    if (isInside(poli, x + w, y)) return true;
    if (isInside(poli, x, y + h)) return true;
    if (isInside(poli, x + w, y + h)) return true;

    // verifica se algum vértice do polígono está dentro do retângulo
    void *v = getPrimeiroVertice(poli);
    while (v != NULL) {
        double vx, vy;
        getCoordenadaVertice(v, &vx, &vy);
        if (vx >= x - EPSILON_GEOM && vx <= x + w + EPSILON_GEOM && vy >= y - EPSILON_GEOM && vy <= y + h + EPSILON_GEOM) return true;
        v = getProximoVertice(v);
    }

    // verifica interseção entre arestas do polígono e lados do retângulo
    double rx1 = x, ry1 = y, rx2 = x + w, ry2 = y;
    double rx3 = x + w, ry3 = y + h, rx4 = x, ry4 = y + h;

    v = getPrimeiroVertice(poli);
    if (v == NULL) return false;
    double px1, py1;
    getCoordenadaVertice(v, &px1, &py1);
    v = getProximoVertice(v);
    while (v != NULL) {
        double px2, py2;
        getCoordenadaVertice(v, &px2, &py2);
        if (segmentosInterceptam(px1,py1,px2,py2, rx1,ry1, rx2,ry2)) return true;
        if (segmentosInterceptam(px1,py1,px2,py2, rx2,ry2, rx3,ry3)) return true;
        if (segmentosInterceptam(px1,py1,px2,py2, rx3,ry3, rx4,ry4)) return true;
        if (segmentosInterceptam(px1,py1,px2,py2, rx4,ry4, rx1,ry1)) return true;
        px1 = px2; py1 = py2;
        v = getProximoVertice(v);
    }
    return false;
}

static bool poligonoInterceptaLinha(POLIGONO poli, LINHA l) {
    if (poli == NULL || l == NULL) return false;
    double x1 = getX1Linha(l), y1 = getY1Linha(l), x2 = getX2Linha(l), y2 = getY2Linha(l);
    if (isInside(poli, x1, y1)) return true;
    if (isInside(poli, x2, y2)) return true;

    void *v = getPrimeiroVertice(poli);
    if (v == NULL) return false;
    double px1, py1;
    getCoordenadaVertice(v, &px1, &py1);
    v = getProximoVertice(v);
    while (v != NULL) {
        double px2, py2;
        getCoordenadaVertice(v, &px2, &py2);
        if (segmentosInterceptam(px1,py1,px2,py2, x1,y1, x2,y2)) return true;
        px1 = px2; py1 = py2;
        v = getProximoVertice(v);
    }
    return false;
}

static bool poligonoInterceptaTexto(POLIGONO poli, TEXTO t) {
    if (poli == NULL || t == NULL) return false;
    double x = getXTexto(t), y = getYTexto(t);
    return poligonoInterceptaPonto(poli, x, y);
}

bool formaIntersectaPoligono(void *forma, char tipo, POLIGONO poli) {
    if (forma == NULL || poli == NULL) return false;
    if (tipo == 'c') {
        return poligonoInterceptaCirculo(poli, (CIRCULO)forma);
    }
    else if (tipo == 'r') {
        return poligonoInterceptaRetangulo(poli, (RETANGULO)forma);
    }
    else if (tipo == 'l') {
        return poligonoInterceptaLinha(poli, (LINHA)forma);
    }
    else if (tipo == 't') {
        return poligonoInterceptaTexto(poli, (TEXTO)forma);
    }
    return false;
}



