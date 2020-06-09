// FIFO simples
//João Gabriel Silva 2020-03-20
#include <stdio.h>

#define TAMFILA 10 /* maximo de mensagens em espera */

struct mensagem {
    char destino[50];
    char origem[50];
    unsigned char dados[1024];
};

struct mensagem fila[TAMFILA];

int colocar(struct mensagem mens);

struct mensagem retirar(void);

int main() {
    int i;
    struct mensagem mens1 = {"Rua do Moinho, Belmonte", "Rua do Castro, Coimbra",
                             "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
    struct mensagem mens2;

    for (i = 0; i < TAMFILA; i++)
        fila[i].destino[0] = 0;

    for (i = 0; i < TAMFILA + 1; i++)
        if (colocar(mens1) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");

    mens2 = retirar();
    if (mens2.destino[0] == 0)
        printf("Fila estava vazia\n");
    else
        printf("Mens retirada com sucesso: %s\n", mens2.destino);
    for (i = 0; i < 3; i++)
        if (colocar(mens1) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");

    for (i = 0; i < TAMFILA + 1; i++) {
        mens2 = retirar();
        if (mens2.destino[0] == 0)
            printf("Fila estava vazia\n");
        else
            printf("Mens retirada com sucesso: %s\n", mens2.destino);
    }


    return 0;
}

int colocar(struct mensagem mens) {
    int i;
    for (i = TAMFILA - 1; i >= 0 && fila[i].destino[0] != 0; i--);
    if (i >= 0) {    // há espaço
        fila[i] = mens;
        return 0;
    } else // não há espaço
        return 1;
}

struct mensagem retirar(void) {
    int i;
    struct mensagem ultima;
    if (fila[TAMFILA - 1].destino[0] == 0)
        // não há mensagens
        return fila[TAMFILA - 1];
    else {
        ultima = fila[TAMFILA - 1];
        for (i = TAMFILA - 2; i >= 0 && fila[i].destino[0] != 0; i--)
            fila[i + 1] = fila[i];
        fila[i + 1].destino[0] = 0;
        return ultima;
    }
}

