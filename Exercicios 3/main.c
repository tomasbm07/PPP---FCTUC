#include <stdio.h>
#include <stdlib.h>

void datas() {
    struct data {
        int dia;
        int mes;
        int ano;
    } data[1024];

    printf("Formato: DD/MM/AAAA\n");
    for (int i = 0; i < 2; ++i) {
        printf("Type a date: ");
        fflush(stdout);
        scanf("%2d/%2d/%4d", &data[i].dia, &data[i].mes, &data[i].ano);
    }

    //comprar 2 datas
    if (data[0].dia == data[1].dia && data[0].mes == data[1].mes && data[0].ano == data[1].ano)
        printf("As datas são iguais\n");
    if (data[0].ano == data[1].ano) { // ano igual
        if (data[0].mes == data[1].mes) { // mes igual
            if (data[0].dia > data[1].dia)
                printf("A 1ª data é posterior á 2ª");
            else
                printf("A 1ª data é anterior á 2ª");
        } else {
            if (data[0].mes > data[1].mes)
                printf("A 1ª data é posterior á 2ª");
            else
                printf("A 1ª data é anterior á 2ª");
        }
    } else {
        if (data[0].ano > data[1].ano)
            printf("A 1ª data é posterior á 2ª");
        else
            printf("A 1ª data é anterior á 2ª");
    }

    //Diferença entre as datas
    int dias, meses, anos;
    dias = abs(data[0].dia - data[1].dia);
    meses = abs(data[0].mes - data[1].mes);
    anos = abs(data[0].ano - data[1].ano);
    printf("\nAs datas diferem em %d dias, %d meses e %d anos", dias, meses, anos);

    //Século
    printf("\n%d/%d/%4d, pertence ao século ", data[0].dia, data[0].mes, data[0].ano);
    if (data[0].ano >= 0) {
        if (data[0].ano <= 100)
            printf("1");
        else if (data[0].ano % 100 == 0)
            printf("%d", data[0].ano / 100);
        else
            printf("%d", data[0].ano / 100 + 1);
    } else printf("\nERRO!\n");
}

void novo(void);

struct data{
    int dia;
    int mes;
    int ano;
};

struct nota{
    int nota_1;
    int nota_2;
    int nota_3;
    int nota_4;
};

struct alunos{
    char nome[60];
    int num;
    struct data data;
    struct nota nota;
} info[30];

int main() {
    /*//Ex. 8.1.1
    datas();*/

    // inicializar a lista
    for (int i = 0; i < 30; i++) {
        info[i].nome[0] = 0;
        info[i].num = 0;
        info[i].data.dia = 0;
        info[i].data.mes = 0;
        info[i].data.ano = 0;
        info[i].nota.nota_1 = 0;
        info[i].nota.nota_2 = 0;
        info[i].nota.nota_3 = 0;
        info[i].nota.nota_4 = 0;
    }


    int escolha;
    while(1){
        printf("0 - Sair\n1 - Inserir dados\n2 - Check\n3 - Listar apartir de uma data\n4 - Melhor média\n5 - Listar aprovados");
        fflush(stdout);
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                novo();
                break;
            case 2:
                //search();
                break;
            case 3:
                //listar_data();
                break;
            case 4:
                //melhor_media();
                break;
            case 5:
                //listar_aprovados();
                break;
            default:
                return 0;
        }
    }
}

void novo(){
    int i = 0;
    while (i < 30 && info[i].nome[0] != 0) {  // procurar a primeira posição vazia
        i++;
    }

    if(i == 30){
        printf("Lista cheia");
        return;
    }


}
