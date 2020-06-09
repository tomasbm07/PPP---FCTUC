// Example from section 4.4 of Brian Kernighan e Dennis Ritchie, The C Programming Language, 2nd edition, Prentice Hall, 1988
#include <stdio.h>
#include <stdlib.h>  // for atof()
#include <math.h>

#define MAXOP 100    // max size of operand or operator
#define NUMBER '0'   // signal that a number was found

int getop(char []);

void push(double);

double pop(void);

void print();

void swap();

void duplica();

void clear();


/* reverse Polish calculator */
int main(void) {
    int type;
    double op2;
    char s[MAXOP];

    fflush(stdout);
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s)); // a to float
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                op2 = pop();
                printf("\t%.8g\n", op2);
                push(op2);
                break;
            case 'p':
                print();
                break;
            case 'c':
                clear();
                break;
            case 'd':
                duplica();
                break;
            case 's':
                swap();
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

// Section where the data structure stack is defined
#define MAXVAL 100

int sp = 0;   //stack pointer
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print() {
    double value = pop();
    push(value);
}

void clear() {
    sp = 0;
}

void duplica(){
    double value, value_2;
    int aux = sp;

}

void swap(){ // swap do 1º com o ultimo
    double value, value_2;
    int aux = sp;
    value = pop();
    sp = 1;
    value_2 = pop();
    push(value);
    sp = aux + 1;
    push(value_2);
}


// section with input character functions
#include <ctype.h>

int getch(void);

void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    fflush(stdout);
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

int getch(void)      // get a (possibly pushed back) character
{
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
