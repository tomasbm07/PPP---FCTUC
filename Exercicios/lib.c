#include "lib.h"
#include <stdio.h>

void amigos(int a, int b) {
    int divisores_a[1000] = {}, divisores_b[1000] = {};
    int count = 0, soma_a = 0, soma_b = 0;

    // Encontrar todos os divisores de a
    for (int i = 0; i <= a; i++) {
        if ((a % i) == 0) {
            divisores_a[count] = i;
            count++;
        }
    }

    count = 0;
    // Encontrar todos os divisores de b
    for (int i = 0; i <= b; i++) {
        if ((a % i) == 0) {
            divisores_a[count] = i;
            count++;
        }
    }


    for (int i = 0; i < (sizeof(divisores_a) / sizeof(divisores_a[0])); i++)
        soma_a += divisores_a[i];

    for (int i = 0; i < (sizeof(divisores_b) / sizeof(divisores_b[0])); i++)
        soma_b += divisores_b[i];


    if (soma_a == b && soma_b == a)
        printf("Os numeros são amigos");
    else
        printf("Os numeros não são amigos");

}
