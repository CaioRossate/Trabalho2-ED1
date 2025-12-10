#include "ordenacao.h"
#include <string.h>
#include <stdlib.h>

void insertionsort(void *base, size_t n, size_t size, int (*compar)(const void*, const void*)) {
    char *arr = (char*)base;
    char *temp = (char*)malloc(size);
    
    if (temp == NULL) return;
    
    for (size_t i = 1; i < n; i++) {
        memcpy(temp, arr + i * size, size);
        
        size_t j = i;
        while (j > 0 && compar(arr + (j - 1) * size, temp) > 0) {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        
        memcpy(arr + j * size, temp, size);
    }
    
    free(temp);
}

void merge(void *base, size_t left, size_t mid, size_t right, size_t size, int (*compar)(const void*, const void*)) {
    char *arr = (char*)base;
    
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    
    char *L = (char*)malloc(n1 * size);
    char *R = (char*)malloc(n2 * size);
    
    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return;
    }
    
    memcpy(L, arr + left * size, n1 * size);
    memcpy(R, arr + (mid + 1) * size, n2 * size);
    
    size_t i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (compar(L + i * size, R + j * size) <= 0) {
            memcpy(arr + k * size, L + i * size, size);
            i++;
        } else {
            memcpy(arr + k * size, R + j * size, size);
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        memcpy(arr + k * size, L + i * size, size);
        i++;
        k++;
    }
    
    while (j < n2) {
        memcpy(arr + k * size, R + j * size, size);
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergesort_recursivo(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*), int threshold) {
    if (left >= right) return;
    
    size_t tamanho = right - left + 1;
    
    // Usa insertionsort para subvetores pequenos
    if (tamanho <= (size_t)threshold) {
        insertionsort((char*)base + left * size, tamanho, size, compar);
        return;
    }
    
    size_t mid = left + (right - left) / 2;
    
    mergesort_recursivo(base, left, mid, size, compar, threshold);
    mergesort_recursivo(base, mid + 1, right, size, compar, threshold);
    merge(base, left, mid, right, size, compar);
}

void mergesort(void *base, size_t n, size_t size, int (*compar)(const void*, const void*), int threshold) {
    if (base == NULL || n <= 1) return;
    
    mergesort_recursivo(base, 0, n - 1, size, compar, threshold);
}