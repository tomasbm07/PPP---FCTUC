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

void print_file(FILE *file);

/*****************************************************/

int get_one_line(FILE * fich, char *linha, int lim);


int main(void) {

    char ano_str[10];
    //struct pessoa alguem;
    unsigned int ano;
    int vazio;
    char nome_fich[MAXNOME + 1];
    FILE * fich = NULL;

    inicializar_arvore();

    // pedir nome do ficheiro que contém os dados
    /*while(fich == NULL) {
        printf("Nome do ficheiro de dados? ");
        if (get_one_line(stdin,nome_fich, MAXNOME + 1) == EOF)
            return 0;
        fich = fopen(nome_fich, "r");
        if (fich == NULL)
            fprintf(stderr,"Ficheiro não existe\n");
    }*/

    // inserir pares {nome,data nascimento} na árvore
   /* while (get_one_line(fich,alguem.nome, MAXNOME + 1) != EOF && strcasecmp(alguem.nome, "Fim") != 0) {
        if (get_one_line(fich,ano_str, 6) != EOF) {
            alguem.ano_nasc = (unsigned int) strtol(ano_str, NULL, 0);
            if (colocar(alguem) != 0) {
                fprintf(stderr,"Não há espaço para inserir\n");
                break;
            }
        }
    }*/

    //printf("Dados inseridos na árvore:\n\n");
    //mostrar_tudo();


// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve zero se a pessoa não foi encontrada
    /*strcpy(alguem.nome, "");
    printf("\n\nNome da pessoa a procurar? ");
    get_one_line(stdin,alguem.nome, MAXNOME + 1);
    while (strcasecmp(alguem.nome, "FIM") != 0) {
        if ((ano = consultar(alguem.nome)) > 0)
            printf("Ano de nascimento %u\n", ano);
        else
            fprintf(stderr,"Não existe\n");
        printf("Nome da pessoa a procurar? ");
        get_one_line(stdin,alguem.nome, MAXNOME + 1);
    }*/


    /*// Mostrar o conteudo da árvore após o nome indicado
    printf("\n\nNome da pessoa inicial do varrimento? ");
    get_one_line(stdin,alguem.nome, MAXNOME + 1);
    while (strcasecmp(alguem.nome, "FIM") != 0) {
        alguem = seguinte(&vazio, alguem.nome);
        while (!vazio) {
            printf("%4u %s\n", alguem.ano_nasc, alguem.nome);
            alguem = seguinte(&vazio, alguem.nome);
        }
        printf("Nome da pessoa inicial do varrimento? ");
        get_one_line(stdin,alguem.nome, MAXNOME + 1);
    }*/


    struct pessoa alguem = {"dsajdlsdiasjda", 0};
    char linha1[MAXNOME], linha2[MAXNOME];

    FILE *pal1 = NULL, *pal2 = NULL, *paljuntas = NULL;
    pal1 = fopen("pal1.txt", "r");
    pal2 = fopen("pal2.txt", "r");
    paljuntas = fopen("paljuntas.txt", "w");

    while((get_one_line(pal1, alguem.nome, MAXNOME)) != EOF)
        colocar(alguem);

    while((get_one_line(pal2, alguem.nome, MAXNOME)) != EOF)
        colocar(alguem);


    print_file(paljuntas);


    fclose(pal1);
    fclose(pal2);
    fclose(paljuntas);
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
    if (pr == NULL) return candidato;
    if ((strcasecmp(anterior, pr->gente.nome)) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

void treeprint(struct tnode *p);

void treeprint_file(struct tnode *p, FILE *file);

void mostrar_tudo(void) {
    treeprint(raiz);
}

void print_file(FILE* file){
    treeprint_file(raiz, file);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4u %s\n", p->gente.ano_nasc, p->gente.nome);
        treeprint(p->right);
    }
}

void treeprint_file(struct tnode *p, FILE *file) {
    if (p != NULL) {
        treeprint_file(p->left, file);
        fprintf(file, "%s\n", p->gente.nome);
        treeprint_file(p->right, file);
    }
}

/****************************************************/

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE * fich, char *linha, int lim) {
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich)));
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
