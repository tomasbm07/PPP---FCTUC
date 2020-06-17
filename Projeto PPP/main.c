#include "Lista.h"


/**
    - Limite da lista é TAMFILA. Como é usada uma lista duplamente ligada em matriz nao é possivel
aumentar a lista, facilmente, conforme necessario.

    - No eunciado é pedido as equipas com os dois melhores e dois piores resultdos. Assim, o programa todas as equipas com as
duas melhores e as duas piores classificações.

    - A funçao update da return a 0 se conseguiu fazer o update dos pontos, ie, a equipa ja estava na lista e foi
ajustados os seus pontos conforme a situaçao, e da return a 1 se nao conseguiu fazer o update, ie, a equipa ainda
nao fazia parte da lista.

    - Como é pedido para o input ser feito em dois ficheiros diferentes, um com as equipas e outro com os resultados,
as fuções get_one_line_equipas e get_one_line_resultados, lêm uma linha do ficheiro das equipas e uma linha do
ficheiro dos resultados, respetivamente.

    - A pasta "gerador" no Projeto, tem o código que gera os 2 ficheiros de entrada a partir de um conjunto de equipas.
Este gerador não faz parte do projeto em si, mas é uma forma de gerar os ficheiros de entrada. O gerador gera os ficheiros
de entrada de mode que todas as equipas joguem contra todas as outras 2 vezes. O gerador tem o cuidado de não gerar um empate
apesar do programa fazer essa verificação.

**/


/*--------------------------------------------------------------------------------------*/
int get_one_line_equipas(FILE *fich_equipas, char *equipa_1, char *equipa_2, int lim, int linha);

int get_one_line_resultados(FILE *fich_resultados, char *result_1, char *result_2, int lim, int linha);

int convert_to_int(char *number, int linha);

/*--------------------------------------------------------------------------------------*/


int main(int argc, char *argv[]) {
    FILE *input_equipas = NULL, *input_resultados = NULL, *output = NULL;
    char equipa_1[TAM_MAX] = "", equipa_2[TAM_MAX] = "", result_1[TAM_MAX] = "", result_2[TAM_MAX] = "";
    char winner[TAM_MAX] = "", looser[TAM_MAX] = "";
    int resultado[2] = {0, 0}, linha = 1;
    struct equipa equipa_aux;

    //Garantir que so sao passados os argumentos necessarios
    //Argumentos são: ficheiro das equipas - ficheiro dos resultados - ficheiro de output
    //arv[0] = cd do .exe
    if (argc < 4) {
        fprintf(stderr, "Devem ser passados os nomes dos ficheiros de entrada e saida\n");
        return 1;
    } else if (argc > 4) {
        fprintf(stderr, "Demasiados argumentos para o programa\n");
        return 1;
    }

    //Open the input file with protection
    if ((input_equipas = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }
    if ((input_resultados = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[2]);
        return 1;
    }

    //Open or create the output file
    if ((output = fopen(argv[3], "w")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[3]);
        return 1;
    }

    inicializar_lista();

    //Loop para ler dos ficheiros de entrada e decidir o vencedor
    while ((get_one_line_equipas(input_equipas, equipa_1, equipa_2, TAM_MAX, linha)) != EOF) {
        //Se ainda houver jogos e nao houver resultados, erro
        if((get_one_line_resultados(input_resultados, result_1, result_2, TAM_MAX, linha)) == EOF){
            fprintf(stderr, "Faltam entradas no ficheiro dos resultados\n");
        }

        //Convert the strings into integers
        resultado[0] = convert_to_int(result_1, linha);
        resultado[1] = convert_to_int(result_2, linha);
        //Verificar os resultados
        //- nao pode ser <0
        //- nao podem ser iguais
        if(resultado[0] < 0 || resultado[1] < 0){
            fprintf(stderr, "Valor nao pode ser negativo\nLinha %d\n", linha);
            return 1;
        }
        if(resultado[0] == resultado[1]){
            fprintf(stderr, "Valores nao podem ser iguais\nLinha %d\n", linha);
            return 1;
        }

        printf("%s Vs %s -> %d - %d\n", equipa_1, equipa_2, resultado[0], resultado[1]);

        //Determine the winner and looser
        if (resultado[0] > resultado[1]) {
            strcpy(winner, equipa_1);
            strcpy(looser, equipa_2);
        } else {
            strcpy(winner, equipa_2);
            strcpy(looser, equipa_1);
        }

        printf("Winner - %s\nLooser - %s\n\n", winner, looser);
        linha++; // number of line read for error

        //Update return 0 se fez update, else return 1, ie, equipa n existe na fila
        if ((update(winner, 2)) != 0) {
            strcpy(equipa_aux.nome, winner);
            equipa_aux.pontos = 2;
            if ((colocar(equipa_aux)) != 0) { //colocar-> return 0 - sucesso; return 1 - falha
                //se cheagar aqui -> Lista cheia
                fprintf(stderr, "Lista cheia. Nao foi possivel colocar %s\n", equipa_aux.nome);
                return 1;
            }
        }

        if ((update(looser, 1)) != 0) {
            strcpy(equipa_aux.nome, looser);
            equipa_aux.pontos = 1;
            if ((colocar(equipa_aux)) != 0) {//colocar-> return 0 - sucesso; return 1 - falha
                //se cheagar aqui -> Lista cheia
                fprintf(stderr, "Lista cheia. Nao foi possivel colocar %s\n", equipa_aux.nome);
                return 1;
            }
        }

    }
    //quando chegar aqui, ja leu as entradas todas do ficheiro das equipas
    if((get_one_line_resultados(input_resultados, result_1, result_2, TAM_MAX, linha)) != EOF){
        fprintf(stderr, "Demasiadas entradas no ficheiro dos resultados\n");
    }


    sort_list();

    //Escrever no ficheiro de output
    fprintf(output, "(Team # Final Score)\n");
    fprintf(output, "---------Top 2 Scores----------\n");
    file_print_top2(output);
    fprintf(output, "-------------------------------\n\n");

    fprintf(output, "---------Bot 2 Scores----------\n");
    file_print_bot2(output);
    fprintf(output, "-------------------------------\n\n");

    fprintf(output, "----------Leaderboard----------\n");
    file_print_list(output);
    fprintf(output, "-------------------------------\n");


    fclose(input_equipas);
    fclose(input_resultados);
    fclose(output);
    return 0;
}


// get next line from input - "lim" includes the terminating zero
//returns the last character
int get_one_line_resultados(FILE *fich_resultados, char *result_1, char *result_2, int lim, int linha) {
    int c = 0, i = 0;
    //Retirar espaços em branco no inicio do ficheiro
    while (isspace(c = fgetc(fich_resultados)));

    //Verificar se a linha esta vazio antes dos loops
    if (c != EOF) {
        if (c == CONTROL) { // check for empty 1st string
            fprintf(stderr, "(num)# -> Numero Invalido\nLinha %d\n", linha);
            exit(1);
        }
        if (!iscntrl(c)) result_1[i++] = c;
    } else
        return c;

    //Ler o 1º numero do resultado
    for (; i < lim-1;) {
        c = fgetc(fich_resultados);
        if (c == EOF)
            return c;
        //Erro se encontrar um \n -> significa que o ficheiro tem o formato errado
        if (c == '\n') {
            result_1[i] = 0;
            fprintf(stderr, "%s -> Erro no formato\nLinha %d\n", result_1, linha);
            exit(1);
        }
        if (c == CONTROL)
            break;
        if (!iscntrl(c)) result_1[i++] = c;
    }

    result_1[i] = 0;
    //Erro se o resultado for uma string vazia
    if ((strcmp(result_1, "")) == 0) {
        fprintf(stderr, "(value)# -> Colocar uma valor\nLinha %d\n", linha);
        exit(1);
    }

    //Ler o 2º numero do resultado
    for (i = 0; i < lim-1;) {
        c = fgetc(fich_resultados);
        if (c == EOF)
            return c;
        if (c == '\n') {
            break;
        }
        if (!iscntrl(c)) result_2[i++] = c;
    }

    result_2[i] = 0;
    //Erro se o resultado for uma string vazia
    if ((strcmp(result_2, "")) == 0) {
        fprintf(stderr, "%s#(value) -> Colocar um valor\nLinha %d\n", result_1, linha);
        exit(1);
    }


    //Return do ultimo carater da linha lida
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich_resultados);
    return c;
}


int get_one_line_equipas(FILE *fich_equipas, char *equipa_1, char *equipa_2, int lim, int linha) {
    int c = 0, i = 0;
    //Retirar espaços em branco no inicio do ficheiro
    while (isspace(c = fgetc(fich_equipas)));

    //Verificar se o ficheiro esta vazio antes dos loops
    if (c != EOF) {
        if (c == CONTROL) { // check for empty 1st string
            fprintf(stderr, "(name)# -> Nome Invalido\nLinha %d\n", linha);
            exit(1);
        }
        if (!iscntrl(c)) equipa_1[i++] = c;
    } else
        return c;

    //Ler o nome da 1ª equipa
    for (; i < lim-1;) {
        c = fgetc(fich_equipas);
        if (c == EOF)
            return c;
        //Erro se houver digitos no nome da equipa
        if (isdigit(c)) {
            equipa_1[i] = 0;
            fprintf(stderr, "%s -> Carateres Invalidos\nLinha %d\n", equipa_1, linha);
            exit(1);
        }
        if (c == CONTROL)
            break;
        //Erro se encontrar um \n -> significa que o ficheiro tem o formato errado. "Blue Wales\n"
        if (c == '\n') {
            equipa_1[i] = 0;
            fprintf(stderr, "%s -> Erro no formato\nLinha %d\n", equipa_1, linha);
            exit(1);
        }
        if (!iscntrl(c)) equipa_1[i++] = c;
    }
    //Se acabar o loop e n houver um # -> Nome demasiado longo
    if (c != CONTROL) {
        equipa_1[i] = 0;
        fprintf(stderr, "%s -> Nome demasiado longo\nLinha %d\n", equipa_1, linha);
        exit(1);
    }
    equipa_1[i] = 0;
    //Erro se o nome da equipa for vazio
    if ((strcmp(equipa_1, "")) == 0) {
        fprintf(stderr, "(name)# -> Nome Invalido\nLinha %d\n", linha);
        exit(1);
    }

    //Ler o nome da 2ª equipa
    for (i = 0; i < lim-1;) {
        c = fgetc(fich_equipas);
        if (c == EOF)
            return c;
        //Erro se houver digitos no nome da equipa
        if (isdigit(c)) {
            equipa_2[i] = 0;
            fprintf(stderr, "%s -> Carateres Invalidos\nLinha %d\n", equipa_2, linha);
            exit(1);
        }
        if (c == '\n')
            break;

        if (!iscntrl(c)) equipa_2[i++] = c;
    }
    equipa_2[i] = 0;

    //Se acabar o loop e n houver um \n -> Nome demasiado longo
    if (i == lim - 1 && c != '\n') {
        fprintf(stderr, "%s -> Nome demasiado longo\nLinha %d\n", equipa_2, linha);
        exit(1);
    }


    //Erro se o nome da equipa for vazio
    if ((strcmp(equipa_2, "")) == 0) {
        fprintf(stderr, "%s#(name) -> Nome Invalido\nLinha %d\n", equipa_1, linha);
        exit(1);
    }

    //Return do ultimo carater da linha lida
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich_equipas);
    return c;
}

//Converter a string para inteiro de forma protegida
int convert_to_int(char number[TAM_MAX], int linha) {
    long int numl;
    int num = 0;
    char *tail;

    errno = 0;
    numl = strtol(number, &tail, 0);
    if (errno) {
        fprintf(stderr, "Transbordo em long\nLinha %d\n", linha);
    }

    // verificar se há carateres inválidos no resultado
    // strtol("123abc") -> 123; tail= "   " (3 espaços vazios das letras no numero)
    while ((*tail) != 0) {
        if (!isspace(*tail)) {
            fprintf(stderr, "%s -> Carateres Inválidos\nLinha %d\n", number, linha);
            exit(1);
        }
        tail++;
    }

    // converter de long para int
    if (numl <= INT_MAX && numl >= INT_MIN) {
        num = (int) numl;
    } else
        fprintf(stderr, "Transbordo em long\nLinha %d\n", linha);

    return num;
}
