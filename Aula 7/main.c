#include <stdio.h>

void func(int *pi){
    *pi = 3;
    printf("i dentro %d\n", *pi);
}

void swap(int *x, int *y){
    int temp = *y;
    *y = *x;
    *x = temp;
}

int main(void) {
    int x = 5, y = 9;
    swap(&x, &y);
    printf("%d %d\n", x, y);

/*    int i = 3;
    int *j;
    int **k;
    j = &i;
    k = &j;
    printf("%p\n", &i);
    printf("%p\n", j);
    printf("%p\n", *k);
    printf("%p\n", &k);
    printf("----------------\n");
    printf("%d\n", i);
    printf("%d\n", *j);
    printf("%d\n", **k);*/

    return 0;
}

