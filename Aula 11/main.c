#include <stdio.h>
#include <string.h>

void str_cat(char *a, char *b, char *s) {
    unsigned long size_a = strlen(a);
    unsigned long size_b = strlen(b);

    for (int i = 0; i < size_a; ++i)
        s[i] = a[i];

    for (int j = 0; j < size_b; ++j) {
        s[size_a + j] = b[j];
        if (j == size_b)
            s[size_a + j] = '\0';
    }
}

void wally(char *s) {
    unsigned long size = strlen(s);
    int flag = 0;

    for (int i = 0; i < size; ++i) {
        if (s[i] == 'W' && s[i + 1] == 'a' && s[i + 2] == 'l' && s[i + 3] == 'l' && s[i + 4] == 'y') {
            printf("Posição: %d", i);
            flag = 1;
        }
    }

    if (flag == 0)
        printf("Palavra não encontrada");
}

void str_search(char *a, char *b) {
    // procurar a em b
    unsigned long size_a = strlen(a);
    unsigned long size_b = strlen(b);

    int tag = 0;

    if (size_a > size_b)
        printf("Erro");
    else {
        for (int i = 0; i < size_b; ++i) {
            if (tag == size_a)
                break;
            tag = 0;
            if (a[0] == b[i]) {
                for (int j = 0; j < size_a; ++j) {
                    if (a[j] == b[i + j]) {
                        if (tag == size_a)
                            break;
                        tag++;
                    } else
                        break;
                }
            }
        }
        if (tag == size_a)
            printf("A está contida em B");
        else
            printf("A não está contida em B");
    }
}

void count_lines() {
    int c, tag = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            tag++;
    }
    printf("Escreveu %d linhas", tag);
}


void mudar_palavra(char *s, char *a, char *b) {
    unsigned long size_a = strlen(a);
    unsigned long size_b = strlen(b);

    int tag = 0;

    for (int i = 0; i < 60; ++i) {
        if (tag == size_a) {
            for (int k = 0; k < size_b; ++k) {
                s[i + k - 1] = b[k]; // substituir por c
            }
        }

        tag = 0;
        if (s[i] == a[0]) { // encontrar b em a
            for (int j = 0; j < size_a; ++j) {
                if (s[i + j] == a[j])
                    tag++;
            }
        }
    }
}


void compress(char *s) {
    int c, i = 0, aux = 0, flag = 0;
    char string[1024], temp = ' ';
    while ((c = getchar()) != '\n') { // Ler uma string da consola até a um \n
        if (c >= '0' && c <= '9') { // Ler apenas numeros
            string[i] = (char) c;
            i++;
        }
    }
    string[i] = '\0'; // Fim da string lida

    unsigned long size = strlen(string);
    char aux_string_1[1024];

    for (int t = 0; t < size; t++) {
        s[t] = ' ';
        if (t == size)
            s[t] = '\0';
    }

    for (int j = 0; j < size; ++j) {
        for (int k = j + 1; k < size; ++k) {
            if (string[j] == string[k]) {
                aux++;
            } else {
                if (aux >= 4) {
                    strcpy(aux_string_1, &string[k]); // destination, string a copiar
                    if (flag == 0) {
                        strncpy(s, string, j);
                        flag++;
                    } else
                        strncpy(&s[j + 4], &string[j], k);
                    s[j] = '\0';
                    s[j] = 'c';
                    s[j + 1] = string[j];
                    s[j + 2] = (char) (aux + '0');
                    s[j + 3] = 'f';
                    s[j + 4] = '\0';
                    strcat(&s[j + 4], aux_string_1);
                }
                aux = 0;
                break;
            }
        }
    }
    s[strlen(s) + 1] = '\0';
}

int main() {
    char line1[] = "Hello World";
    char line2[] = "Bye World";
    char buffer[1024];
    char line[] = "Esta cadeia tem a palavra Wally na posicao 26";
    char a[] = "BBB";
    char b[] = "aaaaaaBBBaaaaa";
    //str_cat(line1, line2, buffer);
    //printf("%s", buffer);
    //wally(line);
    //str_search(a, b);
    //count_lines();
    //char string[] = "aaaBBaaaBaaBBaaaBaaa";
    //mudar_palavra(string, "B", "CD");
    //printf("%s", string);
    char result[1024];
    compress(result);
    printf("%s", result);
    return 0;
}
