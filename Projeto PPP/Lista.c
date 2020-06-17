#include "Lista.h"

static int entrada_lista; //1º elemento da lista
static int saida_lista; //ultimo elemento da lista

static struct elem_fila {
    struct equipa equipa;
    int node_seguinte;
    int node_anterior;
} fila[TAMFILA];


// Inicializa a lista
void inicializar_lista(void) {
    // Lista inicialmete vazia
    entrada_lista = -1;
    saida_lista = -1;

    // Inicializar a fila
    for (int k = 0; k < TAMFILA; ++k) {
        fila[k].equipa.pontos = 0;
        fila[k].equipa.nome[0] = 0;
        fila[k].node_seguinte = -1;
        fila[k].node_anterior = -1;
    }

    printf("\n---Lista Inicializada---\n\n");
}

//Coloca um elemento novo na lista
int colocar(struct equipa equipa) {
    int i;
    //Procurar uma posição disponível. Condiçao de uma posição livre:
    //i < tamanho max da fila e não é o ultimo elemento da lista
    // (fila[i].node_seguinte == -1 && i != saida_lista) -> condiçao do ultimo elemento da lista
    for (i = 0; i < TAMFILA && !(fila[i].node_seguinte == -1 && i != saida_lista); i++);

    if (i >= TAMFILA) //fila cheia
        return 1;

    //colocar mensagem na fila
    fila[i].equipa = equipa;

    //colocar os indices corretos na node seguinte e anterior
    if (entrada_lista == -1) { // lista vazia, colocar 1º elemento
        entrada_lista = i;
        saida_lista = i;
        fila[i].node_seguinte = -1;
        fila[i].node_anterior = -1;
    } else { // Colocar asseguir ao ultimo elemento da lista
        fila[i].node_seguinte = -1;
        fila[i].node_anterior = saida_lista;
        fila[saida_lista].node_seguinte = i;
        saida_lista = i;
    }

    return 0;
}

//returns the node at saida_lista
struct equipa retirar(void) {
    int i;

    if (saida_lista < 0) { // lista vazia
        return fila[0].equipa;
    }

    i = saida_lista;
    if (fila[saida_lista].node_anterior == -1) {
        //só havia uma mensagem na fila - vai ficar vazia
        entrada_lista = -1;
        saida_lista = -1;
    } else { // havia mais do que uma mensagem na lista
        //saida da lista passa a ser a mensagem aterior á que vai sair
        //mensagem que saiu passa a -1 = Vazia
        saida_lista = fila[saida_lista].node_anterior;
        fila[saida_lista].node_seguinte = -1;
    }
    return fila[i].equipa;
}

//Prints the list in the console
//Doesn't print empty nodes
void print_list(void) {
    int i = 0;
    if (saida_lista == -1) {
        fprintf(stderr, "Lista Vazia\n");
    } else {
        while (fila[i].node_seguinte != -1) {
            printf("%s # %d\n", fila[i].equipa.nome, fila[i].equipa.pontos);
            i++;
        }
        printf("%s # %d\n", fila[i].equipa.nome, fila[i].equipa.pontos);
    }
}

//Prints the list in the file
//Doesn't print empty nodes
void file_print_list(FILE *file) {
    int i = 0;
    if (saida_lista == -1) {
        fprintf(stderr, "Lista Vazia\n");
    } else {
        while (fila[i].node_seguinte != -1) {
            fprintf(file, "%s # %d\n", fila[i].equipa.nome, fila[i].equipa.pontos);
            i++;
        }
        fprintf(file, "%s # %d\n", fila[i].equipa.nome, fila[i].equipa.pontos);
    }
}


//Procura o nome da equipa na lista e soma os pontos
int update(char nome[TAMFILA], int pontos) {
    for (int i = 0; i < TAMFILA; ++i) {
        if ((strcmp(nome, fila[i].equipa.nome)) == 0) {
            fila[i].equipa.pontos += pontos;
            return 0;
        }
    }
    //Se chegar aqui, o nome da equipa n existe na lista
    return 1;
}

//Sort da lista por ordem decrescente
void sort_list(void) {
    struct equipa equipa_aux;

    for (int i = 0; i < TAMFILA; ++i) {
        for (int j = i; j < TAMFILA; ++j) {
            if (fila[i].equipa.pontos < fila[j].equipa.pontos) { // Trocar os elementos
                equipa_aux = fila[i].equipa;
                strcpy(fila[i].equipa.nome, fila[j].equipa.nome);
                fila[i].equipa.pontos = fila[j].equipa.pontos;

                strcpy(fila[j].equipa.nome, equipa_aux.nome);
                fila[j].equipa.pontos = equipa_aux.pontos;
            }
        }
    }
}

//Prints all the teams with the 2 best scores
void file_print_top2(FILE *file) {
    int i = 1;

    fprintf(file, "%s # %d\n", fila[entrada_lista].equipa.nome, fila[entrada_lista].equipa.pontos);
    if (fila[entrada_lista + i].equipa.pontos == fila[entrada_lista].equipa.pontos) {
        while (fila[entrada_lista + i].equipa.pontos == fila[entrada_lista].equipa.pontos) {
            fprintf(file, "%s # %d\n", fila[entrada_lista + i].equipa.nome, fila[entrada_lista + i].equipa.pontos);
            i++;
        }
    }

    fprintf(file, "%s # %d\n", fila[entrada_lista + i].equipa.nome, fila[entrada_lista + i].equipa.pontos);
    if (fila[entrada_lista + i + 1].equipa.pontos == fila[entrada_lista + i].equipa.pontos) {
        while (fila[entrada_lista + i + 1].equipa.pontos == fila[entrada_lista + i].equipa.pontos) {
            fprintf(file, "%s # %d\n", fila[entrada_lista + i + 1].equipa.nome,
                    fila[entrada_lista + i + 1].equipa.pontos);
            i++;
        }
    }
}

//Prints all the teams with the 2 worse scores
void file_print_bot2(FILE *file) {
    int i = 1;

    fprintf(file, "%s # %d\n", fila[saida_lista].equipa.nome, fila[saida_lista].equipa.pontos);
    if (fila[saida_lista - i].equipa.pontos == fila[saida_lista].equipa.pontos) {
        while (fila[saida_lista - i].equipa.pontos == fila[saida_lista].equipa.pontos) {
            fprintf(file, "%s # %d\n", fila[saida_lista - i].equipa.nome, fila[saida_lista - i].equipa.pontos);
            i++;
        }
    }

    fprintf(file, "%s # %d\n", fila[saida_lista - i].equipa.nome, fila[saida_lista - i].equipa.pontos);
    if (fila[saida_lista - i - 1].equipa.pontos == fila[saida_lista - i].equipa.pontos) {
        while (fila[saida_lista - i - 1].equipa.pontos == fila[saida_lista - i].equipa.pontos) {
            fprintf(file, "%s # %d\n", fila[saida_lista - i - 1].equipa.nome, fila[saida_lista - i - 1].equipa.pontos);
            i++;
        }
    }
}

