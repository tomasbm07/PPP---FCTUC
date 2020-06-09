// FIFO com prioridades em lista duplamente ligada em matriz
//João Gabriel Silva 2020-03-21
#include <stdio.h>
#include <limits.h>

#define TAMFILA 10 /* maximo de mensagens em espera */

int entrada_lista;
int saida_lista;

/*struct mensagem {
    char destino[50];
    char origem[50];
    unsigned char dados[1024];
};*/

struct elem_fila {
    //struct mensagem mens;
    int mens;
    //int prioridade;
    int mens_seguinte;
    int mens_anterior;
} fila[TAMFILA];

int colocar(int mens);

int retirar(void);

void print(void);

int main() {
    int i;
    /*struct mensagem mens1 = {" Rua Sta. Apolónia, Lisboa", "Rua do Castro, Coimbra",
                             "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
    struct mensagem mens3 = {"Rua Rápida, Porto", "Rua do Castro, Coimbra",
                             "Pedaço de comunicação audio"};
    struct mensagem mens2;*/

    //lista inicialmente vazia
    entrada_lista = -1;
    saida_lista = -1;

    // marcar todas as posições como vazias
    for (i = 0; i < TAMFILA; i++) {
        fila[i].mens = INT_MIN;
        fila[i].mens_seguinte = i;
    }
    colocar(1);
    colocar(4);
    colocar(5);
    print();
    printf("%d", retirar());

    /*for (i = 0; i < TAMFILA - 1; i++) {
        mens1.destino[0] = '0' + i;
        if (colocar(mens1, 1) != 0)
            printf("Erro na colocação P1 E%d S%d\n", entrada_lista, saida_lista);
        else
            printf("Colocação com sucesso P1 E%d S%d\n", entrada_lista, saida_lista);
    }

    for (i = 0; i < 3; i++)
        if (colocar(mens3, 2) != 0)
            printf("Erro na colocação P2 E%d S%d\n", entrada_lista, saida_lista);
        else
            printf("Colocação com sucesso P2 E%d S%d\n", entrada_lista, saida_lista);

    mens2 = retirar();
    if (mens2.destino[0] == 0)
        printf("Fila estava vazia E%d S%d\n", entrada_lista, saida_lista);
    else
        printf("Mens retirada com sucesso: %s E%d S%d\n", mens2.destino, entrada_lista, saida_lista);

    for (i = 0; i < 3; i++) {
        mens1.destino[0] = 'A' + i;
        if (colocar(mens1, 1) != 0)
            printf("Erro na colocação E%d S%d\n", entrada_lista, saida_lista);
        else
            printf("Colocação com sucesso E%d S%d\n", entrada_lista, saida_lista);
    }

    for (i = 0; i < TAMFILA + 1; i++) {
        mens2 = retirar();
        if (mens2.destino[0] == 0)
            printf("Fila estava vazia E%d S%d\n", entrada_lista, saida_lista);
        else
            printf("Mens retirada com sucesso: %s E%d S%d\n", mens2.destino, entrada_lista, saida_lista);
    }*/
    return 0;
}

int colocar(int mens) {
    int i, anterior, prox;
    //Procurar uma posição disponível
    for (i = 0; TAMFILA &&fila[i].mens>INT_MIN; i++)
        fila[i].mens = INT_MIN;

    if (i >= TAMFILA) {
        //fila cheia
        return 1;
    }
    //colocar mensagem na fila
    fila[i].mens = mens;
//    printf("posição a colocar %d\n", i);
    //Procurar a posição onde a mensagem deve ficar
    if (entrada_lista < 0) {
        // fila vazia, inserir primeira mensagem
        entrada_lista = i;
        saida_lista = i;
        fila[i].mens_seguinte = -1;
        fila[i].mens_anterior = -1;
    } else {
        // fila contém mensagens
        if (fila[entrada_lista].mens >= mens) {
            // inserir à entrada da lista
            fila[i].mens_seguinte = entrada_lista;
            fila[entrada_lista].mens_anterior = i;
            fila[i].mens_anterior = -1;
            entrada_lista = i;
        } else {
            // procurar posição de inserção
            anterior = entrada_lista;
            prox = fila[entrada_lista].mens_seguinte;
            while (prox >= 0 && fila[prox].mens < mens) { //while (prox >= 0 && fila[prox].prioridade < prioridade)
                anterior = prox;
                prox = fila[prox].mens_seguinte;
            }
            if (prox < 0) {
                // inserir no final da lista
                fila[anterior].mens_seguinte = i;;
                fila[i].mens_seguinte = -1;
                fila[i].mens_anterior = anterior;
                saida_lista = i;
            } else {
                // inserir a meio da lista
                fila[anterior].mens_seguinte = i;
                fila[i].mens_anterior = anterior;
                fila[i].mens_seguinte = prox;
                fila[prox].mens_anterior = i;
            }
        }
    }
    return 0;
}

int retirar(void) {
    int i;

    if (saida_lista < 0) {
        // lista vazia
        fila[0].mens = INT_MIN;
        return fila[0].mens;
    }

    i = saida_lista;
    int mensagem = fila[i].mens;

    if (fila[saida_lista].mens_anterior == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
        fila[saida_lista].mens = INT_MIN;
        saida_lista = -1;
    } else {
        // havia mais do que uma mensagem na lista
        fila[saida_lista].mens = INT_MIN;
        saida_lista = fila[saida_lista].mens_anterior;
        fila[saida_lista].mens_seguinte = -1;
    }
    return mensagem;
}

void print(){
    for (int i = 0; i >= 0 ; i = fila[i].mens_seguinte) {
        printf("%d", fila[i].mens);
    }
}

void estatistica(){

}