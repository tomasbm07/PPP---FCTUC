#include <stdio.h>
#include "lib.h"

int main() {
    int v_inteiros[] = {4, 1, 3, 2, 5};
    int v_ponteiros[] = {};
    int size = sizeof(v_inteiros) / sizeof(v_inteiros[0]);
    ex1a(v_inteiros, size);
    return 0;
}
