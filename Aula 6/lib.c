#include "lib.h"

double fatorial(int n) {
    if (n >= 2)
        return (n * fatorial(n - 1));
    else
        return (1);
}

double fib(int n) {
    if (n == 1 || n == 2)
        return 1;
    else
        return (fib(n - 1) + fib(n - 2));
}