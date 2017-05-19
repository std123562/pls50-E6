#include <stdio.h>

const dieretis = 2; // mia constant metavliti poy tha xrisimopoiithei os dieretis

// the method below converts the integer to binary display data
void converter (int a) {
    while (a < 0) {
        printf("You have inserted a negative number. Please try again and insert a positive one...\n>> ");// elegxos ean einai arnitikos... ean nai tote zitaei apo ton xristi na to kasna eisagei
        scanf("%d", &a);                        // nea eisagogi arithmou
    }
    int b;                                      // to ypoloipo tis diairesis tha pigainei se ayton ton integer
    do {
        b = a % dieretis;                              // ypologizetai to ypoloipo tis diairesis prota
        a = a / dieretis;                              // ginetai i diairesi kai en synexeia o dieretaios pairnei to apotelesma tis diairesis gia na ginei ksana
        (b == 1)? putchar('1'):putchar('0');    // ean to ypoloipo einai miden ektyposei to miden, ean einai ena ektyponei ena
    } while (a > 0);                            // gia na ksanaginei to loop prepei to apotelesma tis dieresis na einai magalytero toy 0
}


int main()
{
    printf("Please insert below  a positive integer\n>> "); // epilogi eisagogis ston xristi
    int a;
    scanf("%d", &a);                                        // eisagogi tis eisodou ston int a
    converter(a);                                           // klisi tis function converter me eisodo to a
    return 0;
}
