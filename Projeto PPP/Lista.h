#ifndef PROJETO_PPP_LISTA_H
#define PROJETO_PPP_LISTA_H

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_MAX 35 // Tamanho max do nome das equipas
#define CONTROL '#' // Carater de separação dos elementos no ficheiro
#define TAMFILA 25 // Tamanho max da fila

struct equipa {
    char nome[50];
    int pontos;
};

/**---------------------Funçoes da lista-------------------------**/
int colocar(struct equipa equipa);

struct equipa retirar(void);

void inicializar_lista(void);

void print_list(void);

void file_print_list(FILE *file);

int update(char nome[TAM_MAX], int pontos);

void sort_list(void);

void file_print_top2(FILE *file);

void file_print_bot2(FILE *file);
/**---------------------------------------------------------------**/



#endif
