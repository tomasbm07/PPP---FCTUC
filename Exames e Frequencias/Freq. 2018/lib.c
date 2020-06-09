#include "lib.h"
#include <stdio.h>

void print_array(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        if (i == n)
            printf("%d\n", a[i - 1]);
        else
            printf("%d, ", a[i - 1]);
    }
}

void sort_array(int a[], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] < a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }
}

int ex1a(int a[], int n) {
    sort_array(a, n);
    print_array(a, n);
    return (int) a;
}
