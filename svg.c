#include <stdio.h>
#include "svg.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "anteparo.h"
#include "poligono.h"
#include "lista.h" 
#include <string.h>

void iniciaSvg(FILE *svgFile) {
    if (svgFile == NULL) return;

    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void desenhaCirculoSvg(FILE *svgFile, CIRCULO circulo) {
    if (svgFile == NULL || circulo == NULL) return;

    double cx = getXCirculo(circulo);
    double cy = getYCirculo(circulo);
    double r = getRaioCirculo(circulo);
    char *corb = getCorBCirculo(circulo);
    char *corp = getCorPCirculo(circulo);

    const char *fill_color = (corp != NULL && corp[0] != '\0') ? corp : "gray";
    const char *stroke_color = (corb != NULL && corb[0] != '\0') ? corb : "black";

    fprintf(svgFile, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/> \n", cx, cy, r, fill_color, stroke_color);
}

void desenhaRetanguloSvg(FILE *svgFile, RETANGULO retangulo) {
    if (svgFile == NULL || retangulo == NULL) return;

    double x = getXRetangulo(retangulo);
    double y = getYRetangulo(retangulo);
    double w = getLarguraRetangulo(retangulo);
    double h = getAlturaRetangulo(retangulo);
    char *corb = getCorBRetangulo(retangulo);
    char *corp = getCorPRetangulo(retangulo);

    const char *fill_color = (corp != NULL && corp[0] != '\0') ? corp : "gray";
    const char *stroke_color = (corb != NULL && corb[0] != '\0') ? corb : "black";
    fprintf(svgFile, "\t<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n", x, y, w, h, fill_color, stroke_color);
}

void desenhaLinhaSvg(FILE *svgFile, LINHA linha) {
    if (svgFile == NULL || linha == NULL) return;

    double x1 = getX1Linha(linha);
    double y1 = getY1Linha(linha);
    double x2 = getX2Linha(linha);
    double y2 = getY2Linha(linha);
    char *cor = getCorLinha(linha);
    const char *stroke_color = (cor != NULL && cor[0] != '\0') ? cor : "black";

    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" stroke-width=\"1\" fill-opacity=\"0.5\"/>\n", x1, y1, x2, y2, stroke_color);
}

void desenhaTextoSvg(FILE *svgFile, TEXTO texto) {
    if (svgFile == NULL || texto == NULL) return;

    double x = getXTexto(texto);
    double y = getYTexto(texto);
    char *corb = getCorBTexto(texto);
    char *corp = getCorPTexto(texto);
    char *txto = getTxtoTexto(texto);
    char ancora = getAncoraTexto(texto);
    
    char *text_anchor;
    if (ancora == 'm' || ancora == 'M') {
        text_anchor = "middle";
    } else if (ancora == 'f' || ancora == 'F') {
        text_anchor = "end";
    } else {
        text_anchor = "start";
    }
    const char *fill_color = (corp != NULL && corp[0] != '\0') ? corp : "black";
    const char *stroke_color = (corb != NULL && corb[0] != '\0') ? corb : "white";
    fprintf(svgFile, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"0.5\" text-anchor=\"%s\" fill-opacity=\"0.5\">%s</text>\n", x, y, fill_color, stroke_color, text_anchor, txto);
}

void desenhaPoligonoVisibilidadeSvg(FILE *svgFile, POLIGONO poli) {
    if (svgFile == NULL || poli == NULL) return;
    
    int numVertices = getNumVertices(poli);
    if (numVertices < 3) return;
    
    fprintf(svgFile, "\t<polygon points=\"");
    
    for (int i = 0; i < numVertices; i++) {
        double x, y;
        obtemVertice(poli, i, &x, &y);
        fprintf(svgFile, "%.2f,%.2f ", x, y);
    }
    
    fprintf(svgFile, "\" fill=\"yellow\" fill-opacity=\"0.3\" stroke=\"red\" stroke-width=\"2\"/>\n");
}

void desenhaFormasLista(FILE *svgFile, LISTA formas) {
    if (svgFile == NULL || formas == NULL) return;
    
    void *no = obtemPrimeiroNo(formas);
    
    while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        
        if (tipo == 'c') {
            desenhaCirculoSvg(svgFile, (CIRCULO)forma);
        } 
        else if (tipo == 'r') {
            desenhaRetanguloSvg(svgFile, (RETANGULO)forma);
        } 
        else if (tipo == 'l') {
            desenhaLinhaSvg(svgFile, (LINHA)forma);
        } 
        else if (tipo == 't') {
            desenhaTextoSvg(svgFile, (TEXTO)forma);
        }
        else if (tipo == 's') {
            desenhaSegmentoSvg(svgFile, (ANTEPARO)forma);
        }
        
        no = obtemProximoNo(no);
    }
}

void desenhaSegmentoSvg(FILE *svgFile, ANTEPARO seg) {
    if (svgFile == NULL || seg == NULL) return;

    double x1 = getX1Anteparo(seg);
    double y1 = getY1Anteparo(seg);
    double x2 = getX2Anteparo(seg);
    double y2 = getY2Anteparo(seg);
    char *cor = getCorAnteparo(seg);

    const char *stroke_color = (cor != NULL && cor[0] != '\0') ? cor : "black";

    fprintf(svgFile, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" stroke-width=\"2\"/>\n", x1, y1, x2, y2, stroke_color);
}

void finalizaSvg(FILE *svgFile) {
    if (svgFile == NULL) return;
    fprintf(svgFile, "</svg>\n");
    fclose(svgFile);
}

