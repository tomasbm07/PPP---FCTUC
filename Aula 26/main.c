#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_LINHA 30

int get_one_line(FILE *fich, char *nome, char *num, int lim);

int main(int argc, char *argv[]) {
    // argv[0] diretório do programa, argv[1] nome do ficheiro
    char *tail;
    long int numl;
    int num = 0;
    char nome[TAM_LINHA], number[TAM_LINHA];
    int c = 0;

    FILE *file = NULL;

    if (argc != 2)
        exit(1);

    if ((file = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit(1);
    }

    while ((c = get_one_line(file, nome, number, TAM_LINHA)) != EOF) {
        //converter
        errno = 0;
        numl = strtol(number, &tail, 0);
        if (errno) {
            fprintf(stderr, "Transbordo em long\n");
            continue;
        }

        // verificar que só há espaço branco no resto da linha
        while ((*tail) != 0) {
            if (!isspace(*tail)) {
                fprintf(stderr, "%s -> Carateres Inválidos na idade\n", nome);
                exit(1);
            }
            tail++;
        }

        // converter de long para int
        if (numl <= INT_MAX && numl >= INT_MIN) {
            num = (int) numl;
        } else
            fprintf(stderr, "Transbordo em long\n");

        if (num > 120) {
            fprintf(stderr, "%s - %d -> Idade Invalida\n", nome, num);
            exit(1);
        }

        printf("%s - %d\n", nome, num);
    }

    return 0;
}

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE *fich, char *nome, char *num, int lim) { //returns the last character
    int c, i, d = 0, flag = 0;
    i = 0;
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) nome[i++] = c;
    } else
        return c;

    //Ler o nome
    for (; i < lim - 1; d++) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (isdigit(c)) {
            nome[i] = 0;
            fprintf(stderr, "%s -> Erro na leitura da linha\n", nome);
            exit(1);
        }
        if (c == ';')
            break;
        if (c == '\n') {
            nome[i] = 0;
            fprintf(stderr, "%s -> Erro no formato\n", nome);
            exit(1);
        }

        if (!iscntrl(c)) nome[i++] = c;
    }
    if (c != ';') { // se n houver ; = nome demasiado longo
        nome[i] = 0;
        fprintf(stderr, "%s -> Nome demasiado longo\n", nome);
        exit(1);
    }
    nome[i] = 0;

    if ((strcmp(nome, "")) == 0) {
        fprintf(stderr, "Nome Invalido\n");
        exit(1);
    }

    //Ler o numero
    for (i = 0; i < lim;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == ' ')
            continue;
        if (c == '\n')
            break;
        if (!iscntrl(c)) num[i++] = c;
    }
    num[i] = 0;

    if ((strcmp(num, "")) == 0) {
        fprintf(stderr, "%s -> Colocar uma Idade\n", nome);
        exit(1);
    }

    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);

    return c;
}
