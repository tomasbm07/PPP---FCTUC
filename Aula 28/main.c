#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TAM_LINHA 30
#define MAXNOME 100

struct stock{
    long ref;
    char nome[MAXNOME + 1];
    int quantidade;
};

int get_one_line(FILE *fich, char *ref, char *nome, char *quantidade,int lim);

/****** Interface da árvore binária - não depende da maneira como a árvore é implementada */

// deve ser sempre chamada antes da árvore ser usada
void inicializar_arvore(void);

// coloca uma pessoa na árvore. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int colocar(struct stock product);

// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve zero se a pessoa não foi encontrada
unsigned int consultar(char nome[]);

// obter os dados da próxima pessoa (por ordem alfabética) presente na árvore, a seguir ao nome indicado
// Se não há ninguém na árvore com um nome a seguir ao fornecido, devolve 1 em *pvazio;
// se havia pelo menos mais uma pessoa na árvore, devolve zero em *pvazio
struct stock seguinte(int *pvazio, const char nome[MAXNOME + 1]);

void mostrar_tudo(void);

/*****************************************************/

int main(int argc, char *argv[]) {
    // argv[0] diretório do programa, argv[1] input, argv[2] output
    char *tail;
    long int numl;
    int num = 0;
    char ref[TAM_LINHA] = "", name[TAM_LINHA] = "", quantidade[TAM_LINHA] = "";
    int c = 0;
    struct stock produto;

    inicializar_arvore();

    FILE *file_in = NULL, *file_out = NULL;

    if (argc != 3)
        exit(1);

    if ((file_in = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit(1);
    }

    if ((file_out = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit(1);
    }

    while ((c = get_one_line(file_in, ref, produto.nome, quantidade, TAM_LINHA)) != EOF) {
        //converter
        // ref - string -> long
        //quantidade - string -> long -> int
        errno = 0;
        numl = strtol(quantidade, &tail, 0);
        if (errno) {
            fprintf(stderr, "Transbordo em long\n");
            continue;
        }

        // verificar que só há espaço branco no resto da linha
        while ((*tail) != 0) {
            if (!isspace(*tail)) {
                fprintf(stderr, "%s -> Carateres Inválidos na idade\n", name);
                exit(1);
            }
            tail++;
        }

        // converter de long para int
        // num = qauntidade do produto(int)
        if (numl <= INT_MAX && numl >= INT_MIN) {
            produto.quantidade = (int) numl;
        } else
            fprintf(stderr, "Transbordo em long\n");

        /*if (num > 120) {
            fprintf(stderr, "%s - %d -> Idade Invalida\n", nome, num);
            exit(1);
        }*/


        //Converter String para Long - referencia
        errno = 0;
        produto.ref = strtol(ref, &tail, 0);
        if (errno) {
            fprintf(stderr, "Transbordo em long\n");
            continue;
        }

        printf("%ld - %s - %d\n", produto.ref, produto.nome, produto.quantidade);
        colocar(produto);

    }

    /*struct stock produto = {123456798, "Farinha", 50};
    colocar(produto);
    struct stock produto_2 = {987456321, "Arroz", 60};
    colocar(produto_2);
    struct stock produto_3 = {987456321, "Massa", 20};
    colocar(produto_3);
*/
    printf("\n\n");
    mostrar_tudo();

    return 0;
}

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE *fich, char *ref, char *nome, char *quantidade, int lim) {
    int c, i = 0, d = 0;
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) ref[i++] = c;
    } else
        return c;

    //Ler a referencia
    for (; i < lim;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        /*if (c == ' ')
            continue;*/
        if (c == ';')
            break;
        if (!iscntrl(c)) ref[i++] = c;
    }

    ref[i] = 0;
    if ((strcmp(ref, "")) == 0) {
        fprintf(stderr, "%s -> Colocar uma Idade\n", nome);
        exit(1);
    }


    //Ler o nome do produto
    for (i = 0; i < lim - 1; d++) {
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


    //Ler a quantidade
    for (i = 0; i < lim;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == ' ')
            continue;
        if (c == '\n')
            break;
        if (!iscntrl(c)) quantidade[i++] = c;
    }
    quantidade[i] = 0;

    if ((strcmp( quantidade, "")) == 0) {
        fprintf(stderr, "%s -> Colocar uma Idade\n", nome);
        exit(1);
    }

    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);

    return c;
}

/*****************************************************/
// Concretização da árvore binária

struct tnode               // the tree node:
{
    struct stock product;
    struct tnode *left;      // left child
    struct tnode *right;     // right child
} *raiz;

void inicializar_arvore(void) {
    raiz = NULL;
}

struct tnode *addtree(struct tnode *, struct tnode *);

int colocar(struct stock product) {
    struct tnode *p;
    p = (struct tnode *) malloc(sizeof(struct tnode)); // make a new node
    if (p == NULL)
        return 1;
    p->product = product;
    //printf("%ld - %s - %d\n", p->product.ref, p->product.nome, p->product.quantidade);
    p->left = p->right = NULL;
    raiz = addtree(raiz, p);
    return 0;
}

struct tnode *addtree(struct tnode *pr, struct tnode *p) {
    if (pr == NULL) {
        pr = p;
    } else {
        if (p->product.quantidade > pr->product.quantidade) {
            pr->right = addtree(pr->right, p);
        } else
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

//struct tnode *find(struct tnode *pr, char *pn);

/*unsigned int consultar(char nome[]) {
    struct tnode *p;
    p = find(raiz, nome);
    if (p == NULL)
        return 0;
    else
        return p->gente.ano_nasc;
}*/

/*struct tnode *find(struct tnode *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    else if ((cond = strcasecmp(pr->product.nome, pn)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}*/

struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato);
struct stock product_vazio = {0,"", 0};

struct stock seguinte(int *pvazio, const char nome[MAXNOME + 1]) {
    struct tnode *p;

    p = find_next(raiz, nome, NULL);
    if (p == NULL) {
        *pvazio = 1;
        return product_vazio;
    }
    *pvazio = 0;
    return p->product;
}

// devolve NULL se não há seguinte
struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato) {
    if (pr == NULL) return candidato;
    if ((strcasecmp(anterior, pr->product.nome)) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

void treeprint(struct tnode *p);

void mostrar_tudo(void) {
    treeprint(raiz);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%ld - %s - %d\n", p->product.ref, p->product.nome, p->product.quantidade);
        treeprint(p->right);
    }
}

/****************************************************/