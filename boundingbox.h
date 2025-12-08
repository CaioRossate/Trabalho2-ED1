#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "anteparo.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"

typedef void* BoundingBox;

/* cria um bounding box simples */
BoundingBox criarBB(double x, double y, double w, double h);
void destruirBB(BoundingBox bb);

/* criadores a partir de formas/anteparos */
BoundingBox criaBBAnteparo(ANTEPARO a);
BoundingBox criaBBCirculo(CIRCULO c);
BoundingBox criaBBRetangulo(RETANGULO r);
BoundingBox criaBBLinha(LINHA l);
BoundingBox criaBBTexto(TEXTO t);

/* operações */
void uniaoBB(BoundingBox destino, BoundingBox fonte);

/* getters */
double getXBoundingBox(BoundingBox bb);
double getYBoundingBox(BoundingBox bb);
double getWBoundingBox(BoundingBox bb);
double getHBoundingBox(BoundingBox bb);

#endif
