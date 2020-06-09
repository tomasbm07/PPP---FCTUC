#include <stdio.h>

void str_up(char *s) {
    for (int i = 0; s[i]; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] += 'A' - 'a';
}

void str_copy(char *to, char *from) {
    int i = 0;
    while (*from != '\0') {
        *to = *from;
        from++;
        to++;
    }
}

int strl_len(char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void remove_spaces(char *s) {
    int i = 0;
    int size = strl_len(s);
    if (size == 0)
        return;
    else {
        // trim right
        while (s[i] == ' ') {
            i--;
        }
        s[i] = '\0';

        // trim left
        i = 0;
        for (; s[i] == ' '; ++i);
        if (i > 0)
            str_copy(s, &s[i]);
    }
}

void encrypt(char *s) {
    static char crypt[] = {'D', 'E', 'I', 'A', 'B', 'C', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'Y', 'X', 'W', 'V', 'U',
                           'T', 'S', 'R', 'Q', 'P', 'O', 'N', 'M'}; // 26
    str_up(s);
    int b = strl_len(s);
    for (int i = 0; i < b; i++) {
        if (s[i] > 'A' && s[i] < 'Z') {
            s[i] = crypt[s[i] - 'A'];
        } else
            continue;
    }
}

void decrypt(char *s) {
    static char crypt[] = {'D', 'E', 'I', 'A', 'B', 'C', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'Y', 'X', 'W', 'V', 'U',
                           'T', 'S', 'R', 'Q', 'P', 'O', 'N', 'M'}; // 26

    static char de_crypt[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                              'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; // 26
    int b = strl_len(s);
    for (int i = 0; i < b; i++) {
        if (s[i] > 'A' && s[i] < 'Z') {
            int j = 0;
            while(crypt[j] != s[i]){
                j++;
            }
            s[i] = de_crypt[j];
        } else
            continue;
    }

}


int main() {
    char line[] = "    -Era uma    vez        ";
    char idk[] = "def";
    //remove_spaces(line);
    encrypt(idk);
    printf("%s\n", idk);
    decrypt(idk);
    printf("%s", idk);

    //printf("-");
    return 0;
}
