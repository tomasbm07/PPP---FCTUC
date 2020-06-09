#include <stdio.h>
#include "lib.h"


/*int soma(int n) {
    if (n == 1)
        return 1;
    else
        return (n + soma(n - 1));
}

int soma_array(int a[], int i, int j) {
    if (i > j)
        return 1;
    else
        return (a[i] + soma_array(a, i + 1, j));
}*/

int main() {
    int i, n;
    while (1) {
        printf("Número: ");
        scanf("%d", &n);
        if (n < 1) break;
        printf("Fibonacci de %d é %e\n", n, fib(n));
    }
    return 0;
}


int main1() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = soma_array(data, 0, 2);
    printf("%d", sum);
    return 0;
}