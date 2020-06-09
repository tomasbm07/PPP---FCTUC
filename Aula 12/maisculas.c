#include <stdio.h>

char minusculas[][8] = {"a", "á", "à", "ã", "â", "b", "c", "ç", "d", "e", "é", "è", "ê", "f", "g", "h", "i", "í", "ì",
                        "î", "j", "k", "l", "m", "n", "o", "ó", "ò", "õ", "ô", "p", "q", "r", "s", "t", "u", "ú", "ù",
                        "û", "v", "w", "x", "y", "z", "\0"};
char maiusculas[][8] = {"A", "Á", "À", "Ã", "Â", "B", "C", "Ç", "D", "E", "É", "È", "Ê", "F", "G", "H", "I", "Í", "Ì",
                        "Î", "J", "K", "L", "M", "N", "O", "Ó", "Ò", "Õ", "Ô", "P", "Q", "R", "S", "T", "U", "Ú", "Ù",
                        "Û", "V", "W", "X", "Y", "Z", "\0"};

static int e_min(const char *cs, int *pm, int *ptam);

static int comp_mchar(const char *um, const char *outro);

/* devolve a string que recebe com todas as minúsculas alteradas para maiúsculas */
void toupper_l(char *line) {
    int cb; // contador de bytes processados
    int j, pos, tam_c;

    cb = 0;
    while (line[cb] != 0) {

        if (e_min(&line[cb], &pos, &tam_c)) // ver se o carater armazenado a partir de line[cb] é uma minúscula
        {
            for (j = 0; j < tam_c; j++) {    // passar de minúscula para maiúscula
                line[cb] = maiusculas[pos][j];
                cb++;
            }
        } else
            cb++;
    }
}

// determina se o carater recebido é uma minúscula
// devolve zero se não é minúscula;
// devolve um se é minúscula, caso em que devolve em (*pm) a posição dessa minúscula na matriz "minusculas",
//                e em (*ptam) o número de bytes do carater
static int e_min(const char *cs, int *pm, int *ptam) {
    int j = 0, tc;
    while (minusculas[j][0] != 0) {
        if ((tc = comp_mchar(&minusculas[j][0], cs))) {
            // encontramos uma minúscula
            *ptam = tc;
            *pm = j;
            return 1;
        }
        j++;
    }
    return 0;
}


// comparar dois carateres multibyte, sob a forma de string, tendo o primeiro de ser terminado por zero
// devolve zero se são diferentes; devolve o número de bytes do carater se são iguais
static int comp_mchar(const char *um, const char *outro) {
    int i = 0;
    while (um[i] != 0) {
        if (um[i] != outro[i])
            return 0;
        i++;
    }
    return i;
}
