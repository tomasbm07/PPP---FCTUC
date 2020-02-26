#include <stdio.h>
#include <stdlib.h>

int main() {
    //idk();
    //ex1();
    //ex2();
    //ex3();
    //ex4();
    //ex5();
    //ex6();
    //ex7();
    //ex8();
    //ex9();
    //ex10();
    //ex11();
    //ex12();
    //ex13();
    //ex14();
    //ex15();
    //ex16();
    ex17();

    return 0;
}

void idk() {
    printf("Hello");
}

void ex1() {
    int peso, idade;
    printf("Digite o seu peso: ");
    scanf("%d", &peso);
    printf("Digite a sua idade: ");
    scanf("%d", &idade);

    printf("O José tem %d anos e pesa %d", idade, peso);

}

void ex2() {
    int num;
    printf("Digite um numero: ");
    scanf("%d", &num);

    if ((num % 2) == 0)
        printf("O numero é par");
    else
        printf("O numero é impar");
}

void ex3() {
    int num1, num2, impar, a, b;

    printf("Digite 2 numeros: ");
    scanf("%d %d", &num1, &num2);

    a = num1 % 2;
    b = num2 % 2;

    if (a == 0 && b == 0)
        printf("ambos sao pares e a sua soma é: %d", num1 + num2);
    else if (a != 0 && b != 0)
        printf("ambos sao impares e o seu produto é: %d", num1 * num2);
    else {

        if (a != 0)
            impar = num1;
        else if (b != 0)
            impar = num2;

        printf("os numeros nao sao do mesmo tipo logo o numero impar é: %d", impar);
    }

}

void ex4() {
    float num1, num2, num3;

    printf("Digite 3 numeros: ");
    scanf("%f %f %f", &num1, &num2, &num3);

    if (num1 > num2 && num1 > num3)
        printf("O maior dos 3 é: %.2f", num1);
    else if (num2 > num1 && num2 > num3)
        printf("O mair dos 3 é: %.2f", num2);
    else if (num3 > num1 && num3 > num2)
        printf("O mair dos 3 é: %.2f", num3);
}

void ex5() {
    int idade;

    printf("Digite a sua idade: ");
    scanf("%d", &idade);
    if (idade <= 12)
        printf("Isento de Pagamento");
    else if (idade >= 13 && idade <= 24)
        printf("Bilhete radical");
    else if (idade >= 25 && idade <= 36)
        printf("Bilhete light");
    else if (idade >= 37 && idade <= 48)
        printf("Bilhete normal");
    else if (idade >= 49 && idade <= 60)
        printf("Bilhete light");
    if (idade >= 61)
        printf("Isento de Pagamento");
}

void ex6() {
    int horas, minutos, new_horas;

    printf("Digite uma hora no formato 24 horas (Ex -> 20:40): ");
    scanf("%d:%d", &horas, &minutos);

    if (horas > 24 || horas < 0 || minutos > 60 || minutos < 0)
        printf("Erro");
    else if (horas > 0 && horas < 12)
        printf("%d:%d -> %d:%d AM", horas, minutos, horas, minutos);
    else if (horas >= 12 && horas < 24)
        printf("%d:%d -> %d:%d PM", horas, minutos, horas - 12, minutos);
    else if (horas == 24)
        printf("%d:%d -> 00:%d AM", horas, minutos, minutos);
}

void ex7() {
    float nota;

    printf("Digite uma nota entre 0 e 20: ");
    scanf("%f", &nota);

    if (nota < 0.0 || nota > 20.0)
        printf("Erro");
    else if (nota >= 0.0 && nota <= 9.0)
        printf("Insufuciente");
    else if (nota >= 10.0 && nota <= 13.0)
        printf("Suficiente");
    else if (nota >= 14.0 && nota <= 16.0)
        printf("Bom");
    else if (nota >= 17.0 && nota <= 20.0)
        printf("Excelente");
}

void ex8() {  // Errado no mes de dezembro mas sem paciencia para corrigir :)
    int dia, mes;

    printf("Digite um dia e mes no formato DD/MM: ");
    scanf("%d/%d", &dia, &mes);

    if (dia >= 21 && mes >= 3 && dia < 21 && mes < 5)
        printf("Primavera");
    else if (dia >= 21 && mes >= 5 && dia < 23 && mes < 8)
        printf("Verão");
    else if (dia >= 21 && mes >= 12 && dia < 21 && mes < 3)
        printf("Inverno");
    else if (dia >= 23 && mes >= 8 && dia < 21 && mes < 12)
        printf("Outono");
}

void ex9() {
    int num[] = {};
    int lower = 0;
    int upper = 6;
    srand(time(0));
    for (int i = 0; i < 2; i++) {
        num[i] = (rand() % (upper - lower + 1) + lower);
        printf("%d\n", num[i]);
    }
    printf("A diferença entre os numeros é: %d\n\n", abs(num[0] - num[1]));
}

void ex10() {
    int mes;
    printf("Digite um numero de um mês: ");
    scanf("%d", &mes);
    switch (mes) {
        case 1:
            printf("Janeiro");
            break;
        case 2:
            printf("Fevereiro");
            break;
        case 3:
            printf("Março");
            break;
        case 4:
            printf("Abril");
            break;
        case 5:
            printf("Maio");
            break;
        case 6:
            printf("Junho");
            break;
        case 7:
            printf("Julho");
            break;
        case 8:
            printf("Agosto");
            break;
        case 9:
            printf("Setembro");
            break;
        case 10:
            printf("Outrubro");
            break;
        case 11:
            printf("Novembro");
            break;
        case 12:
            printf("Dezembro");
            break;
    }
}

void ex11() {
    int num[5] = {};

    printf("Digite um codigo com 4 numeros: ");
    scanf("%1d%1d%1d%1d", &num[0], &num[1], &num[2], &num[3]);

    if (((num[0] + num[1] + num[2] + num[3]) % 2) == 0) {
        num[4] = 0;
        printf("O novo código é: ");
        printf("%d%d%d%d%d", num[0], num[1], num[2], num[3], num[4]);
    } else {
        num[4] = 1;
        printf("O novo código é: ");
        printf("%d%d%d%d%d", num[0], num[1], num[2], num[3], num[4]);
    }
}

void ex12() {
    int limite = 5, soma = 0;
    for (int i = 0; i < limite + 1; i++)
        soma += i;
    printf("%d", soma);
}

void ex13() {
    int limite = 5;
    int soma = 0;

    for (int i = 1; i < limite; i++) {
        soma += i;
        if (soma >= limite) {
            printf("%d\n", soma);
            printf("%d\n", i);
            break;
        }
    }
}

void ex14() {
    int num;
    printf("Digite a quantidade de numeros: ");
    scanf("%d", &num);

    int idk[] = {};
    for (int i = 0; i < num; i++) {
        printf("Digite um numero: ");
        scanf("%d", &idk[i]);

    }
}

void ex15() {
    int linhas;

    printf("Digite o numero de linhas: ");
    scanf("%d", &linhas);

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j <= i; j++) {
            printf("* ");
            if (j == i)
                printf("\n");
        }

}

void ex16() {
    int space, rows, count = 0, count1 = 0;
    printf("Digite o numero de linhas: ");
    scanf("%d", &rows);

    for (int i = 1; i <= rows; ++i) {
        for (space = 1; space <= rows - i; ++space) {
            printf("  ");
            ++count;
        }
        for (int j = 0; j < rows; j++) {
            count1++;
            printf("%3d ", count1);
            if (j == i - 1)
                break;
        }
        printf("\n");
    }
}

void ex17() {
    int count = 0, dia = 0;

    for (int i = 0; i <= 40; i++) {
        if((i % 5) == 0){
            count++;
            if (count%2 == 0) {
                dia++;
                switch (dia) {
                    case 1:
                        printf("D");
                        break;
                    case 2:
                        printf("S");
                        break;
                    case 3:
                        printf("T");
                        break;
                    case 4:
                        printf("Q");
                        break;
                    case 5:
                        printf("Q");
                        break;
                    case 6:
                        printf("S");
                        break;
                    case 7:
                        printf("S");
                        break;
                }
            }
        }
        else
            printf(" ");
        if (i == 40)
            printf("\n");
    }




}