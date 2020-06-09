// fila genérica simples (FIFO) em lista ligada com memória dinâmica
//João Gabriel Silva 2020-04-10
#include <stdio.h>

struct mensagem {
    char destino[50];
    char origem[50];
    unsigned char dados[1024];
};

/* Interface da estrutura de dados - não depende da maneira como a fila é implementada */

// deve ser sempre chamada antes da fila ser usada
void inicializar_fila(void);

// coloca uma mensagem na fila. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int colocar(struct mensagem mens);

// devolve a mensagem que estava à saída da fila. Se a fila estava vazia, devolve 1 em *pvazio; se havia pelo menos uma mensagem na fila,
//         devolve zero em *pvazio
struct mensagem retirar(int *pvazio);

int count(void); // numero de elementos da fila

void print(void);

void invert();

int main() {
    // programa simples para testar a fila
    int i, vazio;
    struct mensagem mens1 = {" Rua Sta. Apolónia, Lisboa", "Rua do Castro, Coimbra",
                             "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
    struct mensagem mens3 = {" Rua Rápida, Porto", "Rua do Castro, Coimbra",
                             "Pedaço de comunicação audio"};
    struct mensagem mens2;

    inicializar_fila();

    /*for (i = 0; i < 6; i++) {
        mens1.destino[0] = '0' + i;
        if (colocar(mens1) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");
    }

    mens2 = retirar(&vazio);
    if (vazio)
        printf("Fila estava vazia\n");
    else
        printf("Mens retirada com sucesso: %s\n", mens2.destino);

    for (i = 0; i < 3; i++) {
        mens3.destino[0] = 'A' + i;
        if (colocar(mens3) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");
    }

    for (i = 0; i < 20; i++) {
        mens2 = retirar(&vazio);
        if (vazio)
            printf("Fila estava vazia\n");
        else
            printf("Mens retirada com sucesso: %s\n", mens2.destino);
    }*/

    struct mensagem mensagem1 = {"aaa", "bbb", "ccc"};
    struct mensagem mensagem2 = {"111", "222", "333"};
    int pvazio = 0;
    //printf("%d\n", count());
    colocar(mensagem1);
    colocar(mensagem2);
    colocar(mensagem1);
    colocar(mensagem2);

    printf("%d\n", count());
    print();

    /*struct mensagem mensagem3 = retirar(&pvazio);
    printf("Mensagem retirada: %s, %s, %s\n\n", mensagem3.destino, mensagem3.origem, mensagem3.dados);
    mensagem3 = retirar(&pvazio);
    printf("Mensagem retirada: %s, %s, %s\n\n", mensagem3.destino, mensagem3.origem, mensagem3.dados);
    colocar(mensagem3);
    colocar(mensagem3);
    print();*/

    return 0;
}

/***************************************************************************/
// lista ligada construída com memória dinâmica

#include <stdlib.h>

struct elem_fila {
    struct mensagem mens;
    struct elem_fila *mens_seguinte;
};

// Ponteiro para o primeiro elemento da fila; = NULL se lista vazia
static struct elem_fila *raiz;
static struct mensagem mens_vazia = {"", "", ""};

void inicializar_fila(void) {
    raiz = NULL;
}


int colocar(struct mensagem mens) {
    struct elem_fila *aux;

    //Obter espaço para um novo nó
    aux = (struct elem_fila *) malloc(sizeof(struct elem_fila));
    if (aux == NULL)
        //não há espaço
        return 1;

    // inserir à entrada da lista
    aux->mens = mens;
    aux->mens_seguinte = raiz;
    raiz = aux;

    return 0;
}


struct mensagem retirar(int *pvazio) {
    struct elem_fila *prox, *anterior;
    struct mensagem mens;

    if (raiz == NULL) {
        // lista vazia
        *pvazio = 1;
        return mens_vazia;
    }

    *pvazio = 0;

    //  Procurar a última mensagem da lista
    anterior = NULL;
    for (prox = raiz; prox->mens_seguinte != NULL; prox = prox->mens_seguinte)
        anterior = prox; // guardar a localização da mensagem anterior à que vai sair

    if (anterior == NULL) {
        //só havia uma mensagem na fila - vai ficar vazia
        mens = raiz->mens;
        free(raiz);
        raiz = NULL;
    } else {
        // havia mais do que uma mensagem na lista
        anterior->mens_seguinte = NULL;
        mens = prox->mens;
        free(prox);
    }
    return mens;
}


int count() {
    struct elem_fila *prox;
    int i = 0;

    for (prox = raiz; prox != NULL; prox = prox->mens_seguinte)
        i++;

    return i;
}


void print() {
    struct elem_fila *prox;

    for (prox = raiz; prox != NULL; prox = prox->mens_seguinte)  // 1->2->NULL; NULL é o ultimo elemento
        printf("%s, %s, %s\n", prox->mens.destino, prox->mens.origem, prox->mens.dados);

    printf("\n");
}


void invert() {
    struct elem_fila *prox;
    struct mensagem aux;
    int pvazio = 0, size = count();


    for (int i = 0; i < size / 2; i++) {
        aux = retirar(&pvazio);
        if (pvazio == 1) // lista vazia
            break;
        colocar(aux);
    }


}