//abrir o terminal no diretorio do ficheiro
//Usar o comando ./gerador.exe para correr o programa

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include<time.h> 

#define TAM_MAX 50

int get_one_line(FILE *fich, char *nome, int lim);

int main(int argc, char *argv[]) {
	
	FILE *input = NULL, *equipas = NULL, *resultados = NULL;
	char nome[TAM_MAX] = "";
	int count = 1, i;
	
	
    //Abrir o ficheiro passado como argumento de forma protegida
    if ((input = fopen("Equipas.txt", "r")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return 1;
    }
	
	//Abrir ou criar o ficheiro de output
	equipas = fopen("C:\\Users\\tomas\\Desktop\\Projeto PPP\\cmake-build-debug\\Input_1.txt", "w");
    resultados = fopen("C:\\Users\\tomas\\Desktop\\Projeto PPP\\cmake-build-debug\\Input_2.txt", "w");
	
	//get the number of teams from file
	while((get_one_line(input, nome, TAM_MAX)) != EOF){
		//printf("%2d  %s\n",count, nome);
		count++;
	}
	fseek(input, 0, SEEK_SET);
	
	//Criar um array de strings
	char nomes[count][TAM_MAX];
	
	//Colocar as strings num array
	i = 0;
	while((get_one_line(input, nome, TAM_MAX)) != EOF){
		strcpy(nomes[i], nome);
		i++;
	}
	
	srand(time(0)); //set seed para gerar sempre valores aleatórios
	
	//Loop gera todas as combinaçoes possiveis da seguinte forma:
	//Todas as equipas jogam contra as outras todas 2 vezes
	//nao jogando, obviamente, contra eles próprios nehuma vez
	for(int j = 0; j < count - 1; j++){
		for(int k =  0; k < count - 1; k++){
			if (k == j)
				continue;
			int aux1 = rand()%150; // gerar um numero entre 0 e 149
			int aux2 = rand()%150;
			while(aux1 == aux2){ // garantir que os valores são diferentes
                aux2 = rand()%150;
			}

			fprintf(equipas, "%s#%s\n", nomes[j], nomes[k]);
            fprintf(resultados, "%d#%d\n", aux1, aux2);

			printf("%s # %s # %d # %d\n", nomes[j], nomes[k], aux1, aux2);
		}
	}
	
	fclose(input);
	fclose(equipas);
	fclose(resultados);
    return 0;
}

/* get next line from input - "lim" includes the terminating zero */
int get_one_line(FILE *fich, char *nome, int lim) { //returns the last character
    int c, i, d = 0;
    i = 0;
    //Retirar espaços em branco no inicio do ficheiro
    while (isspace(c = fgetc(fich)));
    if (c != EOF) {
        if (!iscntrl(c)) nome[i++] = c;
    } else
        return c;

    //Ler o nome da 1ª equipa
    for (; i < lim - 1; d++) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        //Erro se houver digitos no nome da equipa
        if (isdigit(c)) {
            nome[i] = 0;
            fprintf(stderr, "%s -> Erro na leitura da linha\n", nome);
            exit(1);
        }
        if (c == '\n')
            break;

        if (!iscntrl(c)) nome[i++] = c;
    }

	nome[i] = 0;
    //Erro se o nome da equipa for vazio
    if ((strcmp(nome, "")) == 0) {
        fprintf(stderr, "Nome Invalido\n");
        exit(1);
    }

    //Return do ultimo carater do ficheiro
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}