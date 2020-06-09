#include <stdio.h>

#define TAMFILA 10 /* maximo de mensagens em espera */

int entrada_lista;


struct mensagem {
    char destino[50];
    char origem[50];
    unsigned char dados[1024];
};

struct elem_fila {
    struct mensagem mens;
    int prioridade;
    int mens_seguinte;
} fila[TAMFILA];

int colocar(struct mensagem mens, int prioridade);

struct mensagem retirar(void);

void print_message(struct mensagem *m);

void print_fila();

int main() {
    int i;
    struct mensagem mens1 = {"A", "B", "m1"};
    struct mensagem mens3 = {"C", "D", "m3"};
    struct mensagem mens2 = {"X", "Y", "m2"};

    //print_message(&mens1);

    print_fila(); // m1, m3, m2

    //lista inicialmente vazia
    entrada_lista = -1;
    for (i = 0; i < TAMFILA; i++)
        fila[i].prioridade = -1;

    for (i = 0; i < TAMFILA - 1; i++) {
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
    }

    return 0;
}

int colocar(struct mensagem mens, int prioridade) {
    int i, anterior, prox;
    //Procurar uma posição disponível
    for (i = 0; i < TAMFILA && fila[i].prioridade >= 0; i++);
    if (i >= TAMFILA) {
        //fila cheia
        return 1;
    }
    //colocar mensagem na fila
    fila[i].mens = mens;
    fila[i].prioridade = prioridade;
//    printf("posição a colocar %d\n", i);
    //Procurar a posição onde a mensagem deve ficar
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
            while (prox >= 0 && fila[prox].prioridade < prioridade) {
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
    }
    return 0;
}

struct mensagem retirar(void) {
    int i, j;

    if (entrada_lista < 0) {
        // lista vazia
        fila[0].mens.destino[0] = 0;
        return fila[0].mens;
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
    return fila[i].mens;
}

void print_message(struct mensagem *m) {
    printf("origem: %s\n", m->origem); // (*m).dados = m->dados
    printf("destino: %s\n", m->destino);
    printf("dados: %s", m->dados);
}

void print_fila(struct mensagem m) {
    int anterior, prox, j;
    for (int i = entrada_lista; fila[i].mens_seguinte != -1; i = fila[i].mens_seguinte) {
        j = i; // localizaçao da mensagem anterior à q vai sair
    }
    if (j != -1)
    print_message(&fila[j].mens);
}

