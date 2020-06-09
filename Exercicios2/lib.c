#include "lib.h"
#include <stdio.h>

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1)
            printf("%d\n", *(a + i));
        else
            printf("%d, ", *(a + i));
    }
}

void soma_vetores(double a[], double b[], int n) {
    double c[n];
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

void double_impares(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        if (*(a + i) % 2 != 0)
            *(a + i) = (*(a + i)) * 2;
    }
}

void load_array(int a[], int n) {
    printf("Enter the number of elements: ");
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
}

int max_array(int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[0] < a[i])
            a[0] = a[i];
    }
    return a[0];
}

void find_words(char *dic) {

}
