#include <stdio.h>

void inverter(char str[]) {
    for (int i = 0; i < 10; i++) {
        *(str + i) = *(str + 7 - i);
    }
}

void print_array(char a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", *(a + i));
    }
}

int main() {
    char str[] = "exemplo";
    inverter(str);
    print_array(str, 7);
    return 0;
}
