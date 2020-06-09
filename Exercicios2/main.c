#include <stdio.h>
#include "lib.h"

int main() {
    /*int data[5];

    printf("Enter elements:\n");
    for (int i = 0; i < 5; ++i)
        scanf("%d", data + i); // avançar no array, como em AC array + x byte

    printf("\nYou entered: \n");
    for (int i = 0; i < 5; ++i)
        printf("%d\n", *(data + i));*/

    // EX 6.1 4)
    /* int n;
     printf("Enter the number of elements:\n");
     scanf("%d", &n);
     double arr_1[n], arr_2[n];
     printf("Enter elements:\n");
     for (int i = 0; i < n; i++)
         scanf("%lf", &arr_1[i]); // lf(long float) -> double

     for (int i = 0; i < n; i++)
         scanf("%lf", &arr_2[i]);

     soma_vetores(arr_1, arr_2, n);
     print_array(arr_1, n);*/

    /*// Ex. 6.1 5)
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", arr + i);

    print_array(arr, n);
    double_impares(arr, n);
    print_array(arr, n);
*/

    /* //Ex 6.1 6)
     int n;
     printf("Enter the size of the array: ");
     scanf("%d", &n);
     int arr[n];
     load_array(arr, n);
     print_array(arr, n);
     printf("")
     max_array(arr, n);*/

    //Ex.7.3.1
    int c, i = 0;
    char word[1024];
    printf("Type a word: ");
    fflush(stdout);
    while ((c = getchar()) != '\n') {
        if (c >= 'a' && c <= 'z') {
            word[i] = (char) c;
            i++;
        }
    }
    word[i] = '\0';
    printf("%s", word);

    char dictionary[][20] = {"palavra01", "palavra02", "palavra03"};
    int d_size = sizeof(dictionary) / sizeof(dictionary[0]);
    for (int j = 0; j < d_size; j++) {
        find_words(dictionary[j]);
    }


    return 0;
}
