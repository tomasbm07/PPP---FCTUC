// Árvore binária genérica
// João Gabriel Silva 2020-04-21
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXNOME 100

struct pessoa {
    char nome[MAXNOME + 1];
    unsigned int ano_nasc;
};

/****** Interface da árvore binária - não depende da maneira como a árvore é implementada */

// deve ser sempre chamada antes da árvore ser usada
void inicializar_arvore(void);

// coloca uma pessoa na árvore. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int colocar(struct pessoa alguem);

// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve zero se a pessoa não foi encontrada
unsigned int consultar(char nome[]);

// obter os dados da próxima pessoa (por ordem alfabética) presente na árvore, a seguir ao nome indicado
// Se não há ninguém na árvore com um nome a seguir ao fornecido, devolve 1 em *pvazio;
// se havia pelo menos mais uma pessoa na árvore, devolve zero em *pvazio
struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]);

void mostrar_tudo(void);

struct pessoa nome_igual(char pn[]);

void first_name(char nome[], char copy[]);

/*****************************************************/

int get_one_line(char *linha, int lim);


int main(void) {
    char ano_str[10];
    struct pessoa alguem;
    unsigned int ano;
    int vazio;

    inicializar_arvore();

    // inserir pares {nome,data nascimento} na árvore
    /*while (get_one_line(alguem.nome, MAXNOME + 1) != EOF && strcasecmp(alguem.nome, "Fim") != 0) {
        if (get_one_line(ano_str, 6) != EOF) {
            alguem.ano_nasc = (unsigned int) strtol(ano_str, NULL, 0);
            if (colocar(alguem) != 0) {
                printf("Não há espaço para inserir\n");
                break;
            }
        }
    }*/

    struct pessoa pessoas[] = {{"Joao Silva", 2000}, {"Alexandre Andrade", 1999}, {"Tomas Mendes", 2001}, {"Alexandre Domingues", 2005},{"Joel Oliveira", 2007}};
    for (int i = 0; i < 5; ++i) {
        colocar(pessoas[i]);
    }
    //mostrar_tudo();
    alguem = nome_igual("Alexandre");
    printf("%s\n", alguem.nome);

// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve zero se a pessoa não foi encontrada
    strcpy(alguem.nome, "");
    while (strcasecmp(alguem.nome, "FIM") != 0) {
        printf("Nome da pessoa a procurar? ");
        get_one_line(alguem.nome, MAXNOME + 1);
        if ((ano = consultar(alguem.nome)) > 0)
            printf("Ano nascimento %u\n", ano);
        else
            printf("Não existe\n");
    }

    mostrar_tudo();

    // Mostrar o conteudo da árvore após o nome indicado
    printf("Nome da pessoa inicial do varrimento? ");
    get_one_line(alguem.nome, MAXNOME + 1);
    while (strcasecmp(alguem.nome, "FIM") != 0) {
        alguem = seguinte(&vazio, alguem.nome);
        while (!vazio) {
            printf("%4u %s\n", alguem.ano_nasc, alguem.nome);
            alguem = seguinte(&vazio, alguem.nome);
        }
        printf("Nome da pessoa inicial do varrimento? ");
        get_one_line(alguem.nome, MAXNOME + 1);
    }

    return 0;
}

/*****************************************************/
// Concretização da árvore binária

struct tnode               // the tree node:
{
    struct pessoa gente;
    struct tnode *left;      // left child
    struct tnode *right;     // right child
} *raiz;

void inicializar_arvore(void) {
    raiz = NULL;
}

struct tnode *addtree(struct tnode *, struct tnode *);

int colocar(struct pessoa alguem) {
    struct tnode *p;
    p = (struct tnode *) malloc(sizeof(struct tnode)); // make a new node
    if (p == NULL)
        return 1;
    p->gente = alguem;
    p->left = p->right = NULL;
    raiz = addtree(raiz, p);
    return 0;
}

struct tnode *addtree(struct tnode *pr, struct tnode *p) {
    int cond;
    if (pr == NULL) {
        pr = p;
    } else {
        if ((cond = strcasecmp(p->gente.nome, pr->gente.nome)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

struct tnode *find(struct tnode *pr, char *pn);

unsigned int consultar(char nome[]) {
    struct tnode *p;
    p = find(raiz, nome);
    if (p == NULL)
        return 0;
    else
        return p->gente.ano_nasc;
}

struct tnode *find(struct tnode *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    else if ((cond = strcasecmp(pr->gente.nome, pn)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato);
struct pessoa pes_vazia = {"", 0};

struct pessoa seguinte(int *pvazio, const char nome[MAXNOME + 1]) {
    struct tnode *p;

    p = find_next(raiz, nome, NULL);
    if (p == NULL) {
        *pvazio = 1;
        return pes_vazia;
    }
    *pvazio = 0;
    return p->gente;
}

// devolve NULL se não há seguinte
struct tnode *find_next(struct tnode *pr, const char *anterior, struct tnode *candidato) {
    int cond;
    if (pr == NULL) return candidato;
    if ((cond = strcasecmp(anterior, pr->gente.nome)) >= 0)
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
        printf("%4u - %s\n", p->gente.ano_nasc, p->gente.nome);
        treeprint(p->right);
    }
}

struct pessoa nome_igual(char nome[]) {
    struct tnode *p;
    int *pvazio = (int *) 1, cond;
    char aux_str[MAXNOME];

    p = find_next(raiz, nome, NULL);
    if (p == NULL) {
        *pvazio = 1;
        return pes_vazia;
    }

    first_name(nome, aux_str);
    if ((cond = strcasecmp(nome, aux_str)) == 0)
    *pvazio = 0;
    return p->gente;
}

void first_name(char nome[], char copy[]){
    int i = 0;
    while(nome[i] != 0){
        if(nome[i] == ' ')
            strncpy(copy, nome, i);
        i++;
    }
}

/****************************************************/

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = getchar()));
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = getchar();
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = getchar();
    return c;
}
