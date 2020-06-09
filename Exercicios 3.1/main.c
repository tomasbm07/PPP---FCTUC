#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *start = NULL;

void inserir_valor_inicio(int num);

void print_list();

void ordenar();


int main() {
    int arr[] = {4, 7, 8, 9, 1, 47, 78, 2, 6, 8, 8, 6, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = size - 1; i >= 0; --i) {
        inserir_valor_inicio(arr[i]);
    }

    ordenar();
    print_list();

    return 0;
}

void inserir_valor_inicio(int num) {
    struct node *temp;
    temp = (struct node *) malloc(sizeof(struct node)); // malloc da return a um pointer com o size (struct node)
    temp->data = num; // colocar o valor
    if (start == NULL) {//é o 1º valor a ser colocado na lista
        start = temp;
        start->next = NULL;
    } else { // se n for o 1º valor da lista
        temp->next = start;
        start = temp;
    }
}

void print_list() {
    struct node *temp;
    temp = start;
    while (temp->next != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

void ordenar() {
    struct node *temp;
    int aux = 0;
    temp = (struct node *) malloc(sizeof(struct node));
    while(temp->next != NULL){

    }

}
