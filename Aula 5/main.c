#include <stdio.h>

extern int media_pesada(int i);

int main(void) {
    int i;
    while (1) {
        printf("Número ? ");
        scanf("%d", &i);
        if (i < 0) break;
        printf("Média pesada %d\n", media_pesada(i));
    }
    return 0;
}
