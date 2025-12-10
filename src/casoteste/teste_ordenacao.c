#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ordenacao.h"

int cmpInt(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    return (ia < ib) ? -1 : (ia > ib) ? 1 : 0;
}

void printArr(int *arr, int n) {
    for (int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");
}

int main(void) {
    printf("=== teste_ordenacao ===\n");
    int arr[] = {5,3,8,1,9,2,7,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("antes: "); printArr(arr,n);

    // teste insertion sort
    insertionsort(arr, n, sizeof(int), cmpInt);
    printf("insertion: "); printArr(arr,n);

    // shuffle e teste mergesort
    int arr2[] = {5,3,8,1,9,2,7,4,6};
    mergesort(arr2, n, sizeof(int), cmpInt, 4);
    printf("mergesort: "); printArr(arr2,n);

    // verifica ordenacao
    for (int i=1;i<n;i++) if (arr2[i-1] > arr2[i]) { printf("ordenacao falhou\n"); return 1; }

    printf("teste_ordenacao: ok\n");
    return 0;
}
