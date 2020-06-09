#include <stdio.h>
#include <string.h>

extern void toupper_l(char *line);

static void novo(void);

static void tel(void);

static void listar(void);

static void remove_contacto(void);

static void search(void);

#define MAXCONTACTOS 20 // maximo de contactos a armazenar
#define TAMMAXNOME 50   // número máximo de bytes no nome
#define TAMMAXNOME1 "49"   // número máximo de bytes no nome, sem zero de terminação

struct contactos {
    char nome[TAMMAXNOME];
    int num;
} lista[MAXCONTACTOS];

int main() {
    int escolha, i;

    // inicializar a lista
    for (i = 0; i < MAXCONTACTOS; i++) {
        lista[i].nome[0] = 0;
        lista[i].num = 0;
    }
    while (1) {
        printf("\n   0 - Sair\n   1 - Introduzir contacto novo\n   2 - Obter telefone\n   3 - Listar tudo\n   4 - Remover contacto\n   5 - Procurar um contacto\nEscolha: ");
        fflush(stdout);
        if (scanf("%d", &escolha) != 1)
            escolha = -1; // escolha inválida
        while (getchar() != '\n'); //limpar o resto da linha
        switch (escolha) {
            case 0:
                return 0;
            case 1:
                novo();
                break;
            case 2:
                tel();
                break;
            case 3:
                listar();
                break;
            case 4:
                remove_contacto();
                break;
            case 5:
                search();
                break;
            default:
                printf("Escolha inválida\n");
        }
    }
}


void novo(void) {
    int i;
    // procurar a primeira posição vazia
    i = 0;
    while (i < MAXCONTACTOS && lista[i].nome[0] != 0) {
        i++;
    }
    if (i == MAXCONTACTOS) {
        printf("Não há espaço para mais contactos\n");
        return;
    }
    printf("Introduza o nome: ");
    fflush(stdout);
    scanf(" %"TAMMAXNOME1"[^\n]", &lista[i].nome[0]);
    toupper_l(lista[i].nome);
    printf("Introduza o número: ");
    fflush(stdout);
    while (scanf("%d", &lista[i].num) != 1 || getchar() != '\n') {
        while (getchar() != '\n'); //limpar o resto da linha
        printf("Introduza o número: ");
    }
}


void tel(void) {
    char nome[TAMMAXNOME];
    int i;
    printf("Introduza o nome: ");
    fflush(stdout);
    scanf(" %"TAMMAXNOME1"[^\n]", nome);
    toupper_l(nome);

    i = 0;
    while (i < MAXCONTACTOS && lista[i].nome[0] != 0 && strcmp(nome, lista[i].nome) != 0)
        i++;
    if (i < MAXCONTACTOS && lista[i].nome[0] != 0)
        printf("Número: %d\n", lista[i].num);
    else
        printf("Nome não encontrado\n");
}

// mostrar a lista toda
void listar(void) {
    int i;

    if (lista[0].nome[0] == 0)
        printf("Lista vazia\n");
    else
        for (i = 0; i < MAXCONTACTOS && lista[i].nome[0] != 0; i++) {
            printf("%s - ", lista[i].nome);
            printf("%d\n", lista[i].num);
        }
}


void remove_contacto(void) {
    char nome[TAMMAXNOME];

    if (lista[0].nome[0] == 0)
        printf("Lista vazia\n");
    else {

        printf("Introduza o nome que pretende remover: ");
        fflush(stdout);
        scanf(" %"TAMMAXNOME1"[^\n]", nome);
        toupper_l(nome);

        for (int i = 0; i < MAXCONTACTOS; ++i) {
            if (strcmp(nome, lista[i].nome) == 0) { //strcmp, compara 2 strings, se iguais return 0
                lista[i].num = 0;
                lista[i].nome[0] = 0;
                break;
            }
        }
    }
    // Mostrar a lista depois de remover um contacto
    printf("\n");
    listar();
}


void search(void) {
    char nome[TAMMAXNOME];
    int aux = 0, flag = 0;

    printf("Introduza o nome que pretende procurar: ");
    fflush(stdout);
    scanf(" %"TAMMAXNOME1"[^\n]", nome);
    toupper_l(nome);

    int size = strlen(nome);

    for (int i = 0; i < MAXCONTACTOS; ++i) {
        for (int j = 0; j < MAXCONTACTOS; ++j) {
            if (lista[i].nome[j] == nome[j]) {
                aux++;
                if (aux == size) {
                    printf("%s - ", lista[i].nome);
                    printf("%d\n", lista[i].num);
                    flag = 0;
                    break;
                }
            } else {
                aux = 0;
                flag = 1;
            }


        }
    }

    if (flag == 1)
        printf("Contacto não existe na lista");
}



