#include <stdio.h>
#include <stdlib.h>
#include "../lista.h"

// comparador de inteiros para busca na lista
int comparaInt(void *a, void *b) {
    int va = *(int*)a;
    int vb = *(int*)b;
    if (va == vb) return 0;
    return (va < vb) ? -1 : 1;
}

int main(void) {
    printf("=== teste_lista ===\n");
    LISTA l = criaLista();
    if (!l) { printf("Falha ao criar lista\n"); return 1; }

    int *a = malloc(sizeof(int)); *a = 10; insereLista(l, a, 'i');
    int *b = malloc(sizeof(int)); *b = 20; insereLista(l, b, 'i');
    int *c = malloc(sizeof(int)); *c = 30; insereInicioLista(l, c, 'i');

    printf("tamanho (esperado 3) = %d\n", obtemTamanhoLista(l));

    void *no = buscaLista(l, b, (int(*)(void*,void*))comparaInt);
    if (no) printf("busca encontrado: %d\n", *(int*)obtemDado(no)); else printf("busca nao encontrado\n");

    int *r1 = (int*)removePrimeiroLista(l);
    printf("removePrimeiro = %d\n", r1 ? *r1 : -1);
    free(r1);

    int *r2 = (int*)removeUltimoLista(l);
    printf("removeUltimo = %d\n", r2 ? *r2 : -1);
    free(r2);

    printf("tamanho (esperado 1) = %d\n", obtemTamanhoLista(l));

    // limpa lista
    int *rem = (int*)removePrimeiroLista(l);
    if (rem) free(rem);
    destroiLista(l);

    printf("teste_lista: ok\n");
    return 0;
}
