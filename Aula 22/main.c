#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXNOME 50

int get_one_line(FILE * fich, char *linha, int lim);

int main() {
    FILE *file = NULL, *out_file_bin = NULL, *out_file_int = NULL;
    char nome_fich[MAXNOME];

    // pedir nome do ficheiro que contém os dados
    while(file == NULL) {
        printf("Nome do ficheiro de dados? ");
        if (get_one_line(stdin, nome_fich, MAXNOME + 1) == EOF)
            return 0;
        file = fopen(nome_fich, "r");
        if (file == NULL)
            fprintf(stderr,"Ficheiro não existe\n");
    }

    long int size;
    int size_array;
    fseek(file, 0, SEEK_END); // seek to end of file
    size = ftell(file); // size = tamaho em bytes do ficheiro
    size_array = size/sizeof(int);
    printf("%ld -- %d", size, size_array);
    fseek(file, 0, SEEK_SET); // seek back to beginning of file

    int aux[size_array];
    char line[MAXNOME];
    int i = 0;
    while((get_one_line(file, line, MAXNOME + 1)) != EOF){
        aux[i] = (int) strtol(line, NULL, 0);
        i++;
    }

    out_file_bin = fopen("output_bin.txt", "w");
    fwrite(aux, sizeof(line[0]),size_array ,out_file_bin);

    out_file_bin = fopen("output_bin.txt", "r");

    int aux_2[size_array];
    fread(aux_2, sizeof(int), size_array, out_file_bin);
    out_file_int = fopen("output_int.txt", "w");
    for(int j = 0; j < size_array; j++)
        fprintf(out_file_int, "%d\n", aux[j]);

    fclose(file);
    fclose(out_file_bin);
    fclose(out_file_int);
    return 0;
}


int get_one_line(FILE * fich, char *linha, int lim) { //returns o ultimo char da linha
    int c, i;
    i = 0;
    //While para ver se o ultimo carater lido é EOF
    while (isspace(c = fgetc(fich))); // ispace(c) -> return 0 if c = ' ', else return 1
    if (c != EOF) {
        if (!iscntrl(c)) linha[i++] = c;
    } else
        return c;

    for (; i < lim - 1;) {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == ',')
            c = '\n';
        if (c == '\n')
            break;
        if (!iscntrl(c)) linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}
