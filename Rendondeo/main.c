#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double num = 1.75348;
    double constante = 0.5;
    double n = 2;

    int numRedondeado = num + (constante/pow(10, n - 1));

    printf("%d", numRedondeado );
//    int cant;
//    int numEntr;
//    double numFloat, numFloatNuev;
//
//    printf("Ingrese numero a redondear: ");
//    scanf("%lf", &num);
//
//    printf("Ingrese cantidad de decimales a redondear: ")
//    scanf("%d", cant);
//
//    numEntr = num + (0.5/)

    return 0;
}
