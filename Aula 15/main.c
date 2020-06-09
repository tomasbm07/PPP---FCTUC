// FIFO com prioridades em lista ligada em matriz
//João Gabriel Silva 2020-03-20
#include <stdio.h>

#define TAMFILA 10 /* maximo de mensagens em espera */

int entrada_lista;


struct mensagem {
    //char destino[50];
    //char origem[50];
    long double num;
    char vazio;
    //unsigned char dados[1024];
};

struct elem_fila {
    struct mensagem mens;
    //int prioridade;
    int mens_seguinte;
} fila[TAMFILA];

int colocar(long double num);

long double retirar(void);

void print_list();

int main() {
    int i;
    /* struct mensagem mens1 = {" Rua Sta. Apolónia, Lisboa", "Rua do Castro, Coimbra",
                              "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
     struct mensagem mens3 = {"Rua Rápida, Porto", "Rua do Castro, Coimbra",
                              "Pedaço de comunicação audio"};
     struct mensagem mens2;*/

    //lista inicialmente vazia
    entrada_lista = -1;
    for (i = 0; i < TAMFILA; i++) {
        fila[i].mens.vazio = 0; // Se o elemento está vazio, fila[i].mens.vazio = 0, se tem um numero, = 1
    }
    int aux = 0;
    for (int j = 0; j < 20; j++) {
        aux = colocar(j);
        if(aux == 1)
            break;
    }

    if(aux == 1)
        printf("\nLista cheia\n");

    print_list();
    printf("%Lg\n", retirar());
    printf("%Lg\n", retirar());
    printf("%Lg\n", retirar());
    printf("%Lg\n", retirar());
    print_list();


    /*for (i = 0; i < TAMFILA - 1; i++) {
        mens1.destino[0] = '0' + i;
        if (colocar(mens1, 1) != 0)
            printf("Erro na colocação P1 E%d\n", entrada_lista);
        else
            printf("Colocação com sucesso P1 E%d\n", entrada_lista);
    }

    for (i = 0; i < 3; i++)
        if (colocar(mens3, 2) != 0)
            printf("Erro na colocação P2 E%d\n", entrada_lista);
        else
            printf("Colocação com sucesso P2 E%d\n", entrada_lista);

    mens2 = retirar();
    if (mens2.destino[0] == 0)
        printf("Fila estava vazia E%d\n", entrada_lista);
    else
        printf("Mens retirada com sucesso: %s E%d\n", mens2.destino, entrada_lista);

    for (i = 0; i < 3; i++) {
        mens1.destino[0] = 'A' + i;
        if (colocar(mens1, 1) != 0)
            printf("Erro na colocação E%d\n", entrada_lista);
        else
            printf("Colocação com sucesso E%d\n", entrada_lista);
    }

    for (i = 0; i < TAMFILA + 1; i++) {
        mens2 = retirar();
        if (mens2.destino[0] == 0)
            printf("Fila estava vazia E%d\n", entrada_lista);
        else
            printf("Mens retirada com sucesso: %s E%d\n", mens2.destino, entrada_lista);
    }*/

    return 0;
}

int colocar(long double num) {
    int i, anterior, prox;
    //Procurar uma posição disponível
    for (i = 0; i < TAMFILA; i++);
    if (i >= TAMFILA) {
        //fila cheia
        return 1;
    }
    //colocar mensagem na fila
   /* fila[i].mens.num = mens.num;
    fila[i].mens.vazio = mens.vazio;*/
//    printf("posição a  colocar %d\n", i);
    //    //Procurar a posição onde a mensagem deve ficar
    if (entrada_lista < 0) {
        // fila vazia, inserir primeira mensagem
        entrada_lista = i;
        fila[i].mens_seguinte = -1;
    } else {
        // fila contém mensagens
        if (fila[entrada_lista].prioridade >= prioridade) {
            // inserir à entrada da lista
            fila[i].mens_seguinte = entrada_lista;
            entrada_lista = i;
        } else {
            // procurar posição de inserção
            anterior = entrada_lista;
            prox = fila[entrada_lista].mens_seguinte;
            while (prox >= 0) {
                anterior = prox;
                prox = fila[prox].mens_seguinte;
            }
            if (prox < 0) {
                // inserir no final da lista
                fila[anterior].mens_seguinte = i;;
                fila[i].mens_seguinte = -1;
            } else {
                // inserir a meio da lista
                fila[anterior].mens_seguinte = i;
                fila[i].mens_seguinte = prox;
            }
        }
    //return 0;
    }
    return 0;
}

long double retirar(void){
    int i, j;

    if (entrada_lista < 0) {
        // lista vazia
        fila[0].mens.num = 0;
        return fila[0].mens.num;
    }

    //  Procurar a última mensagem da lista
    j = -1;
    for (i = entrada_lista; fila[i].mens_seguinte != -1; i = fila[i].mens_seguinte)
        j = i; // guardar a localização da mensagem anterior à que vai sair

    if (j == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
        fila[i].prioridade = -1;
    } else {
        // havia mais do que uma mensagem na lista
        fila[j].mens_seguinte = -1;
        fila[i].prioridade = -1;
    }
    return fila[i].mens.num;
}

void print_list() {
    for (int i = 0; i < TAMFILA; i++) {
        printf("%Lg->", fila[i].mens.num);
    }
    printf("\n");
}