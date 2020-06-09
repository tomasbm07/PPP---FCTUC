#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void ex11_1_8(int argc, char *argv[]);

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        printf("Parâmetro %d: %s\n", i, argv[i]);
        i++;
    }
    ex11_1_8(argc, argv);

    return 0;
}

void ex11_1_8(int argc, char *argv[]) {
    FILE *input, *output;

    // testar se o ficheiro a ser lido existe
    if((input = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        exit(1);
    }

    output = fopen(argv[2], "w");

    int c;
    if (strcmp(argv[3], "-l") == 0) {
        while ((c = getc(input)) != EOF) {
            if (c == '\r') {
                c++;
                c = getc(input);
                c--;
                putc(c, output);
            } else
                putc(c, output);
        }
    } else if (strcmp(argv[3], "-c") == 0) {
        while ((c = getc(input)) != EOF) {
            if (c == '\r') {
                c++;
                putc('\n', output);
            } else
                putc(c, output);
        }
    }

    fclose(input);
    fclose(output);
    exit(0);
}

void filecopy(FILE *ifp, FILE *ofp) {
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
