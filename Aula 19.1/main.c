// Exemplo da secção 6.5 do Kernighan & Ritchie, Second Edition, ligeiramente adaptado
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100


struct estudante{
    char nome[MAXWORD];
    int ano;
    struct estudante *left;
    struct estudante *right;
};

struct estudante *addtree(struct estudante *, char *, int ano);

void treeprint(struct estudante *);

int getword(char *, int);

void node_count(struct estudante*, int *count);


/* word frequency count*/
int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    /*root = NULL;
    for(int i = 0; i < 7; i++){
        getword(word, MAXWORD);
        if (isalpha(word[0]))
            root = addtree(root, word);
    }
    treeprint(root);
    int count = 0;
    node_count(root, &count);
    printf("%d\n", count);*/

    struct estudante *root_estudante;
    root_estudante = NULL;

    root_estudante = addtree(root_estudante, "Tomas", 2019);
    root_estudante = addtree(root_estudante, "Alexandre", 2019);

    treeprint(root_estudante);
    return 0;
}

struct estudante *talloc(void);

char *stringdup(char *);

/* addtree: add a node with 2, at or below p */
struct estudante *addtree(struct estudante *p, char w[], int ano) {
    int cond;

    if (p == NULL) {            // a new word has arrived
        p = talloc();            // make a new node
        strcpy(p->nome, w);
        p->ano = ano;
        p->left = p->right = NULL;
    } else if ((cond = strcasecmp(w, p->nome)) < 0)
        p->left = addtree(p->left, w, ano);
    else
        p->right = addtree(p->right, w, ano);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct estudante *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s - %d\n", p->nome, p->ano);
        treeprint(p->right);
    }
}

void node_count(struct estudante* p, int *count){
    if (p != NULL) {
        node_count(p->left, count);
        *count = *count + 1;
        node_count(p->right, count);
    }
}



#include <stdlib.h>

/* talloc: make a tnode */
struct estudante *talloc(void) {
    return (struct estudante *) malloc(sizeof(struct estudante));
}

char *stringdup(char *s)    // make a duplicate of s
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);   // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}
void ungetch(int);
int getch(void);

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free posotion in buf

int getch(void)      // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  // push back on input
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}
