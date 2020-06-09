#include <stdio.h>
#include "lib.h"

void int3(int *p) {
    int n = 0, c, sum = 0, div = 100;
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            int d = c - '0';
            sum += d * div;
            div = div / 10;
        }
    }
    printf("%d", sum);
    *p = sum;
}

void swap_array(int a[], int n) {
    for (int i = 0; i <= (n / 2) - 1; i++) {
        int *left = &a[i];
        int *right = &a[n - 1 - i];
        int temp = *left;
        *left = *right;
        *right = temp;
    }
}

void print_array(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        if (i == n)
            printf("%d\n", a[i - 1]);
        else
            printf("%d, ", a[i - 1]);
    }
}

void primos(int n, int a[]) {
    int i = 3, count, c, count_array = 0;
    int *pInt = &a[n];
    if (n >= 1) {
        a[0] = 2; // 2 é sempre o 1º primo se n <= 1
    }
    for (count = 2; count <= n;) {
        for (c = 2; c <= i - 1; c++) {
            if (i % c == 0)
                break;
        }
        if (c == i) { // i é primo
            count_array++;
            *pInt = i;
            a[count_array] = *pInt;
            count++;
        }
        i++;
    }
}

void agregar(int arr[]) {
    int c, count = 0;
    int d;
    int a[10] = {}, b[10] = {};

    for (int i = 0, j = 0; i <= 10; i++, j++) {
        printf("a >> ");
        scanf("%d", &d);
        a[i] = d;
        /*printf("b >> ");
        scanf("%d", &d);
        b[j] = d;*/
    }
    sort_array(a, 10);
    print_array(a, 10);
}


void sort_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] < a[j]) {
                int num = a[i];
                a[i] = a[j];
                a[j] = num;
            }
        }
    }
}


int* v_pont[] ={};

