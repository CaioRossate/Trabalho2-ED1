#include "geo.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINHA_MAX 512

static char fontFamily[50] = "sans-serif";
static char fontWeight[20] = "normal";
static char fontSize[20] = "16";

void processarGeo(const char *pathGeo, LISTA chao) {
    FILE *geoFile = fopen(pathGeo, "r");
    if (geoFile == NULL) {
        fprintf(stderr, "ERRO: Nao foi possivel abrir o arquivo .geo: %s\n", pathGeo);
        exit(1);
    }

    char linha[TAM_LINHA_MAX];
    int id = 0;
    
    while (fgets(linha, TAM_LINHA_MAX, geoFile) != NULL) {
        char comando[10];
        sscanf(linha, "%9s", comando);

        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }

        if (strcmp(comando, "c") == 0) {
            // Comando c: c id x y r corP corB
            float x, y, r;
            char corP[30], corB[30];
            sscanf(linha, "c %d %f %f %f %29s %29s", &id, &x, &y, &r, corB, corP);
            CIRCULO c = cria_circulo(id, x, y, r, corP, corB);
            insereLista(chao, c, 'c');
        } 
        else if (strcmp(comando, "r") == 0) {
            // Comando r: r id x y w h corP corB
            float x, y, w, h;
            char corP[30], corB[30];
            sscanf(linha, "r %d %f %f %f %f %29s %29s", &id, &x, &y, &w, &h, corB, corP);
            RETANGULO r = cria_retangulo(id, x, y, w, h, corP, corB);
            insereLista(chao, r, 'r');
        }
        else if (strcmp(comando, "l") == 0) {
            // Comando l: l id x1 y1 x2 y2 cor
            double x1, y1, x2, y2;
            char cor[30];
            sscanf(linha, "l %d %lf %lf %lf %lf %29s", &id, &x1, &y1, &x2, &y2, cor);
            LINHA l = criaLinha(id, x1, y1, x2, y2, cor);
            insereLista(chao, l, 'l');
        }
        else if (strcmp(comando, "t") == 0) {
            // Comando t: t id x y corB corP ancora txto
            float x, y;
            char corB[30], corP[30], ancora;
            char txto[256];
            
            
            int numRead = sscanf(linha, "t %d %f %f %29s %29s %c %s", &id, &x, &y, corB, corP, &ancora, txto);
            
            if (numRead == 7) {           
                TEXTO t = cria_texto(id, x, y, ancora, corB, corP, txto, fontFamily, fontWeight, fontSize);
                insereLista(chao, t, 't');
            }
        }
        else if (strcmp(comando, "ts") == 0) {
            char fFamily[50], fWeight[20], fSize[20];
            sscanf(linha, "ts %49s %19s %19s", fFamily, fWeight, fSize);
            
            strncpy(fontFamily, fFamily, sizeof(fontFamily)-1);
            strncpy(fontWeight, fWeight, sizeof(fontWeight)-1);
            strncpy(fontSize, fSize, sizeof(fontSize)-1);
        }

    }
    
    fclose(geoFile);
}
