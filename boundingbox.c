#include <stdlib.h>
#include <math.h>
#include "boundingbox.h"

typedef struct stBB {
    double x, y, w, h;
} stBB;

BoundingBox criarBB(double x, double y, double w, double h) {
    stBB *bb = (stBB*)malloc(sizeof(stBB));
    if (bb == NULL) return NULL;
    bb->x = x;
    bb->y = y;
    bb->w = w;
    bb->h = h;
    return (BoundingBox)bb;
}

void destruirBB(BoundingBox bb) {
    if (bb) free(bb);
}

BoundingBox criaBBAnteparo(ANTEPARO a) {
    if (!a) return NULL;
    double x1 = getX1Anteparo(a);
    double y1 = getY1Anteparo(a);
    double x2 = getX2Anteparo(a);
    double y2 = getY2Anteparo(a);
    double minx = fmin(x1, x2);
    double miny = fmin(y1, y2);
    double w = fabs(x2 - x1);
    double h = fabs(y2 - y1);
    return criarBB(minx, miny, w, h);
}

BoundingBox criaBBCirculo(CIRCULO c) {
    if (!c) return NULL;
    double cx = getXCirculo(c);
    double cy = getYCirculo(c);
    double r = getRaioCirculo(c);
    return criarBB(cx - r, cy - r, 2.0 * r, 2.0 * r);
}

BoundingBox criaBBRetangulo(RETANGULO r) {
    if (!r) return NULL;
    double x = getXRetangulo(r);
    double y = getYRetangulo(r);
    double w = getLarguraRetangulo(r);
    double h = getAlturaRetangulo(r);
    return criarBB(x, y, w, h);
}

BoundingBox criaBBLinha(LINHA l) {
    if (!l) return NULL;
    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    double minx = fmin(x1, x2);
    double miny = fmin(y1, y2);
    double w = fabs(x2 - x1);
    double h = fabs(y2 - y1);
    return criarBB(minx, miny, w, h);
}

BoundingBox criaBBTexto(TEXTO t) {
    if (!t) return NULL;
    double x = getXTexto(t);
    double y = getYTexto(t);
    return criarBB(x, y, 0.0, 0.0);
}

void uniaoBB(BoundingBox destino, BoundingBox fonte) {
    if (!destino || !fonte) return;
    stBB *d = (stBB*)destino;
    stBB *f = (stBB*)fonte;
    double minx = fmin(d->x, f->x);
    double miny = fmin(d->y, f->y);
    double maxx = fmax(d->x + d->w, f->x + f->w);
    double maxy = fmax(d->y + d->h, f->y + f->h);
    d->x = minx;
    d->y = miny;
    d->w = maxx - minx;
    d->h = maxy - miny;
}

double getXBoundingBox(BoundingBox bb) {
    if (!bb) return 0.0;
    return ((stBB*)bb)->x;
}

double getYBoundingBox(BoundingBox bb) {
    if (!bb) return 0.0;
    return ((stBB*)bb)->y;
}

double getWBoundingBox(BoundingBox bb) {
    if (!bb) return 0.0;
    return ((stBB*)bb)->w;
}

double getHBoundingBox(BoundingBox bb) {
    if (!bb) return 0.0;
    return ((stBB*)bb)->h;
}
