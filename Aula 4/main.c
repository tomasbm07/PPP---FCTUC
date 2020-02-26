#include <stdio.h>

int main() {
    char op;
    int num;

    printf("Escolha uma operação (+ - x /) e um numero: ");
    scanf("%c %d", &op, &num);

    switch (op) {
        case 'x':
            for (int i = 1; i < 11; i++)
                printf("%d x %d = %d\n", num, i, num * i);
            break;

        case '/':
            for (int i = 1; i < 11; i++)
                printf("%d / %d = %.3f\n", num, i, (float)num / (float)i);
            break;

        case '+':
            for (int i = 1; i < 11; i++)
                printf("%d + %d = %d\n", num, i, num + i);
            break;

        case '-':
            for (int i = 1; i < 11; i++)
                printf("%d - %d = %d\n", num, i, num - i);
            break;

        default:
            printf("Erro");

    }

    return 0;
}

