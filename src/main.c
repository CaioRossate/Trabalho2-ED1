#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "qry.h"
#include "svg.h"
#include "lista.h"

#define TAM_MAX_CAMINHO 1024
#define TAM_MAX_NOME 256

void ajustarDiretorio(char *caminho, int tamanho_max) {
    int len = strlen(caminho);
    if (len > 0 && caminho[len - 1] != '/') {
        if (len + 1 < tamanho_max) {
            strcat(caminho, "/");
        }
    }
}

void montarCaminhoCompleto(char *destino, const char *diretorio, const char *nomeArquivo) {
    if (strcmp(diretorio, ".") == 0 || diretorio[0] == '\0') {
        snprintf(destino, TAM_MAX_CAMINHO, "%s", nomeArquivo);
    } else {
        snprintf(destino, TAM_MAX_CAMINHO, "%s%s", diretorio, nomeArquivo);
    }
}

void removerExtensao(char *nome) {
    char *ponto = strrchr(nome, '.');
    if (ponto != NULL) {
        *ponto = '\0';
    }
}

int main(int argc, char *argv[]) {
    char diretorioEntrada[TAM_MAX_CAMINHO] = ".";
    char diretorioSaida[TAM_MAX_CAMINHO] = ".";
    char nomeArquivoGeo[TAM_MAX_NOME] = "";
    char nomeArquivoQry[TAM_MAX_NOME] = "";
    
    char caminhoCompletoGeo[TAM_MAX_CAMINHO];
    char caminhoCompletoQry[TAM_MAX_CAMINHO];
    
    int temGeo = 0;
    int temSaida = 0;
    int temQry = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            if (++i < argc) strncpy(diretorioEntrada, argv[i], sizeof(diretorioEntrada)-1);
        } 
        else if (strcmp(argv[i], "-o") == 0) {
            if (++i < argc) {
                strncpy(diretorioSaida, argv[i], sizeof(diretorioSaida)-1);
                temSaida = 1;
            }
        } 
        else if (strcmp(argv[i], "-f") == 0) {
            if (++i < argc) {
                strncpy(nomeArquivoGeo, argv[i], sizeof(nomeArquivoGeo)-1);
                temGeo = 1;
            }
        } 
        else if (strcmp(argv[i], "-q") == 0) {
            if (++i < argc) {
                strncpy(nomeArquivoQry, argv[i], sizeof(nomeArquivoQry)-1);
                temQry = 1;
            }
        }
        
        diretorioEntrada[sizeof(diretorioEntrada)-1] = '\0';
        diretorioSaida[sizeof(diretorioSaida)-1] = '\0';
        nomeArquivoGeo[sizeof(nomeArquivoGeo)-1] = '\0';
        nomeArquivoQry[sizeof(nomeArquivoQry)-1] = '\0';
    }

    if (!temGeo || !temSaida) {
        fprintf(stderr, "ERRO: Os parâmetros '-f <arq.geo>' e '-o <dir_saida>' são obrigatórios.\n");
        fprintf(stderr, "Uso: %s -e <dir_entrada> -f <arq.geo> -o <dir_saida> [-q <arq.qry>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    ajustarDiretorio(diretorioEntrada, TAM_MAX_CAMINHO);
    ajustarDiretorio(diretorioSaida, TAM_MAX_CAMINHO);

    montarCaminhoCompleto(caminhoCompletoGeo, diretorioEntrada, nomeArquivoGeo);

    printf("Processando arquivo .geo: %s\n", caminhoCompletoGeo);
    
    LISTA chao = criaLista();
    processarGeo(caminhoCompletoGeo, chao);
    
    char nomeBaseGeo[TAM_MAX_NOME];
    strncpy(nomeBaseGeo, nomeArquivoGeo, sizeof(nomeBaseGeo)-1);
    removerExtensao(nomeBaseGeo);
    
    char *geoUnderLine = strchr(nomeBaseGeo, '/');
    while (geoUnderLine != NULL) {
        *geoUnderLine = '_';
        geoUnderLine = strchr(nomeBaseGeo, '/');
    }

    char caminhoSvgGeo[2048];
    snprintf(caminhoSvgGeo, 2048, "%s%s.svg", diretorioSaida, nomeBaseGeo);
    
    FILE *svgGeo = fopen(caminhoSvgGeo, "w");
    if (svgGeo != NULL) {
        iniciaSvg(svgGeo);
        desenhaFormasLista(svgGeo, chao);
        finalizaSvg(svgGeo);
        printf("SVG gerado: %s\n", caminhoSvgGeo);
    }

    if (temQry) {
        montarCaminhoCompleto(caminhoCompletoQry, diretorioEntrada, nomeArquivoQry);
        printf("Processando arquivo .qry: %s\n", caminhoCompletoQry);
        
        char nomeBaseQry[TAM_MAX_NOME];
        strncpy(nomeBaseQry, nomeArquivoQry, sizeof(nomeBaseQry)-1);
        removerExtensao(nomeBaseQry);

        char *qryUnderLine = strchr(nomeBaseQry, '/');
        while (qryUnderLine != NULL) {
            *qryUnderLine = '_';
            qryUnderLine = strchr(nomeBaseQry, '/');
        }

        char caminhoTxt[2048];
        char caminhoSvgQry[2048];
        
        snprintf(caminhoTxt, 2048, "%s%s-%s.txt", diretorioSaida, nomeBaseGeo, nomeBaseQry);
        snprintf(caminhoSvgQry, 2048, "%s%s-%s.svg", diretorioSaida, nomeBaseGeo, nomeBaseQry);

        FILE *svgQry = fopen(caminhoSvgQry, "w");
        if(svgQry != NULL){
            iniciaSvg(svgQry);
        }
        // Chama processarQry com parâmetros padrão de ordenação
        char tipoOrdenacao = 'q';
        int threshold = 10;
        processarQry(caminhoCompletoQry, caminhoTxt, caminhoSvgQry, chao, tipoOrdenacao, threshold, svgQry);

        
        if (svgQry != NULL) {
            desenhaFormasLista(svgQry, chao);
            finalizaSvg(svgQry);
            printf("SVG final gerado: %s\n", caminhoSvgQry);
        }
        
        printf("Relatório gerado: %s\n", caminhoTxt);
    }
    void *no = obtemPrimeiroNo(chao);
        while (no != NULL) {
        void *forma = obtemDado(no);
        char tipo = obtemTipo(no);
        destroiForma(forma, tipo);
        no = obtemProximoNo(no);
    }


    destroiLista(chao);
    
    printf("Processamento concluído com sucesso!\n");
    return EXIT_SUCCESS;
}