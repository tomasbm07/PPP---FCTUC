// Pilha (LIFO) genérica sobre memória dinâmica. Calculadora em notação polaca invertida
// Adaptado de exemplo da secção 4.3 de Brian Kernighan e Dennis Ritchie, The C Programming Language, 2nd edition, Prentice Hall, 1988
#include <stdio.h>
#include <stdlib.h>  // for atof()

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number was found

int getop(char []);

// interface genérico da pilha
// inicializar a pilha
void inicializar_pilha(void);

// coloca uma número na pilha. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int push(double f);

// devolve o número que estava no topo da pilha. Se a pilha estava vazia, devolve 1 em *pvazio; se havia pelo menos um número na pilha,
//         devolve zero em *pvazio
double pop(int *pvazio);

int vazio(void);

void print(void);

/* reverse Polish calculator */
int main(void) {
    int type;
    double op2;
    char s[MAXOP];
    int v1, v2, c1;

    inicializar_pilha();

    /*while ((type = getop(s)) != EOF) {
        v1 = v2 = c1 = 0;
        switch (type) {
            case NUMBER:
                c1 = push(atof(s));
                if (c1) printf("Erro na pilha\n");
                break;
            case '+':
                c1 = push(pop(&v1) + pop(&v2));
                if (c1 + v1 + v2) printf("Erro na pilha\n");
                break;
            case '-':
                op2 = pop(&v1);
                c1 = push(pop(&v2) - op2);
                if (c1 + v1 + v2) printf("Erro na pilha\n");
                break;
            case '*':
                c1 = push(pop(&v1) * pop(&v2));
                if (c1 + v1 + v2) printf("Erro na pilha\n");
                break;
            case '/':
                op2 = pop(&v1);
                if (op2 != 0.0)
                    c1 = push(pop(&v2) / op2);
                if (c1 + v1 + v2) printf("Erro na pilha\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop(&v1));
                if (v1) printf("Erro na pilha\n");
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }*/

    double f = 8.26;
    print();
    push(f);
    //print();
    push(f);
    print();

    return 0;
}

//*********************************************************
// secção onde a pilha é implementada

struct no_pilha {
    double dado;
    struct no_pilha *pseg;
    struct no_pilha *pant;
};

struct pilha{
    struct no_pilha *first;
    struct no_pilha *last;
}raiz; // stack pointer

// inicializar a pilha
void inicializar_pilha(void) {
    raiz.first = NULL;
    raiz.last = NULL;
}

// coloca uma número na pilha. Devolve zero se tudo correu bem, devolve 1 se não havia espaço disponível
int push(double f) {
    struct no_pilha *aux;

    //Obter espaço para um novo nó
    aux = (struct no_pilha *)malloc(sizeof(struct no_pilha));
    if (aux == NULL) //não há espaço
        return 1;

    // inserir à entrada da lista
    aux->dado = f;
    if(vazio() == 1) { // Pilha vazia
        raiz.first = aux;
        raiz.last = aux;
    } else {
        aux->pseg = raiz.first;
        raiz.first = aux;
        aux->pant = NULL;
        
    }

    return 0;
}

// devolve o número que estava no topo da pilha. Se a pilha estava vazia, devolve 1 em *pvazio; se havia pelo menos um número na pilha,
//         devolve zero em *pvazio
double pop(int *pvazio) {
    double d;
    struct no_pilha *aux;

    if (vazio() == 1) { // lista vazia
        *pvazio = 1;
        return 0.0;
    }

    *pvazio = 0;

    //  Retirar o dado à entrada da lista
    d = raiz.first->dado;
    aux = raiz.first->pant;
    free(raiz.first);
    raiz.first = aux;
    return d;
}

int vazio(void){
     if (raiz.first == NULL)
         return 1; // Se está vazia return 1
     else
         return 0;// se não está vazia return 0
}

void print(void){
    struct no_pilha *aux;

    aux = raiz.first;

    while(aux != NULL) {
        printf("%f\n", aux->dado);
        aux = aux->pseg;
    }
}

//*********************************************************
// section with input character functions
#include <ctype.h>

int getch(void);

void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;                  // not a number
    i = 0;
    if (isdigit(c))              // collect integer part
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')                // collect fraction part
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFFSIZE 100

char buf[BUFFSIZE];  // buffer for ungetch
int bufp = 0;        // next free position in buf

int getch(void) {     // get a (possibly pushed back) character

    int c;
    if (bufp > 0)
        c = buf[--bufp];
    else
        c = getchar();
    return c;
}

void ungetch(int c)  // push back on input
{
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
