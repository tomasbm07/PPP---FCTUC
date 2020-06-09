// FIFO com prioridades em lista duplamente ligada em matriz
//João Gabriel Silva 2020-03-21
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TAMFILA 100 /* maximo de mensagens em espera */

int entrada_lista;
int saida_lista;

struct mensagem {
    int num;
};

struct elem_fila {
    struct mensagem mens;
    //int prioridade;
    int mens_seguinte;
    int mens_anterior;
} fila[TAMFILA];

int colocar(struct mensagem mens);

struct mensagem retirar(void);

int get_one_line(FILE * fich, char *linha, int lim);

int main() {
    int i;
  /*  struct mensagem mens1 = {" Rua Sta. Apolónia, Lisboa", "Rua do Castro, Coimbra",
                             "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
    struct mensagem mens3 = {"Rua Rápida, Porto", "Rua do Castro, Coimbra",
                             "Pedaço de comunicação audio"};
    struct mensagem mens2;*/

    //lista inicialmente vazia
    entrada_lista = -1;
    saida_lista = -1;

    // marcar todas as posições como vazias
    /*for (i = 0; i < TAMFILA; i++)
        fila[i].prioridade = -1;*/

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

    FILE *input = NULL, *output = NULL;
    struct mensagem mens;
    char aux[50];
    int maior = 0, menor = 0, flag = 0;

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");


    while((get_one_line(input, aux, 50)) != EOF){
        mens.num = atoi(aux);
        if (flag == 0){
            menor = mens.num;
            maior = mens.num;
        } else{
            if(mens.num > maior)
                maior = mens.num;
            if(mens.num < menor)
                menor = mens.num;
        }
        flag++;
        //printf("%d\n", mens.num);
        colocar(mens);
    }
    get_one_line(input, aux, 50);
    mens.num = atoi(aux);
    colocar(mens);
    flag++;

    struct elem_fila *temp;
    temp = fila;
    for (int j = 0; j <= flag ; ++j) {
        fprintf(output, "%d\n",temp->mens.num);
        temp = fila->mens_seguinte;
    }






    fclose(input);
    fclose(output);
    return 0;
}

int colocar(struct mensagem mens) {
    int i, anterior, prox;
    //Procurar uma posição disponível
    for (i = 0; i < TAMFILA; i++);
    if (i >= TAMFILA) {
        //fila cheia
        return 1;
    }
    //colocar mensagem na fila
    fila[i].mens = mens;
    //fila[i].prioridade = prioridade;
    //printf("posição a colocar %d\n", i);
    //Procurar a posição onde a mensagem deve ficar
    if (entrada_lista < 0) {
        // fila vazia, inserir primeira mensagem
        entrada_lista = i;
        saida_lista = i;
        fila[i].mens_seguinte = -1;
        fila[i].mens_anterior = -1;
    } else {
        // fila contém mensagens
        /*if (fila[entrada_lista].prioridade >= prioridade) {
            // inserir à entrada da lista
            fila[i].mens_seguinte = entrada_lista;
            fila[entrada_lista].mens_anterior = i;
            fila[i].mens_anterior = -1;
            entrada_lista = i;
        } else { */
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
    return 0;
    }


struct mensagem retirar(void) {
    int i;

    if (saida_lista < 0) {
        // lista vazia
        //fila[0].mens.destino[0] = 0;
        return fila[0].mens;
    }

    i = saida_lista;
    if (fila[saida_lista].mens_anterior == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
        //fila[saida_lista].prioridade = -1;
        saida_lista = -1;
    } else {
        // havia mais do que uma mensagem na lista
        //fila[saida_lista].prioridade = -1;
        saida_lista = fila[saida_lista].mens_anterior;
        fila[saida_lista].mens_seguinte = -1;
    }
    return fila[i].mens;
}

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE * fich, char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich))); //skip do espaços no inicio do ficheiro
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}



