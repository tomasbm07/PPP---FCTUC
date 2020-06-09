#include <stdio.h>

void mostraSePremiado(int bilhete, int premiado, int n) {
    // bilhete = 125892688
    // n = 3
    int ultimo = 0, count = 0;
    int bilhete2 = bilhete;

    for (int i = 0; i < n; i++) {
        ultimo = bilhete % 10;
        if (premiado % 10 == ultimo)
            count++;
        premiado = premiado / 10;
    }

    if (count == n)
        printf("O bilhete %d foi premido", bilhete2);
}

int main(void) {
    mostraSePremiado(16498, 56498, 4);
    return 0;
}
