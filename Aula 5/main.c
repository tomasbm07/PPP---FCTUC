#include <stdio.h>

extern int media_pesada(int i);

extern int media_simples(int i);

int main(void) {
    int i, t;
    printf("Tipo de filtro ? (1- média simples, 2- média pesada): ");
    scanf("%d", &t);
    if (t != 1 && t != 2) return 1;
    while (1) {
        printf("Número ? ");
        scanf("%d", &i);
        if (i < 0) break;
        if (t == 2)
            printf("Média pesada %d\n", media_pesada(i));
        else printf("Média simples %d\n", media_simples(i));
    }
    return 0;
}
