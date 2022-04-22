#include <stdio.h>
#include <stdlib.h>

#define menorEntreDosNumeros(X, Y) ((X)>(Y) ? (Y) : (X))
#define mayorEntreDosNumeros(X, Y) ((X)>(Y) ? (X) : (Y))
#define esNatural(X) ((X)>=0 ? 1:0)

int prodSumasSucesivas(int x, int y);

int main()
{
    int num1, num2;

    do
    {
        printf("Ingrese primer numero: ");
        scanf("%d", &num1);
        printf("Ingrese segundo numero: ");
        scanf("%d", &num2);
    }while(!esNatural(num1) || !esNatural(num2));

    while(num1 != 0)
    {
        printf("Resultado: %d\n\n", prodSumasSucesivas(num1, num2));;

        do
        {
            printf("Ingrese primer numero: ");
            scanf("%d", &num1);
            printf("Ingrese segundo numero: ");
            scanf("%d", &num2);
        }while(!esNatural(num1) || !esNatural(num2));
    }

    return 0;
}

int prodSumasSucesivas(int x, int y)
{
    int mayor = mayorEntreDosNumeros(x, y);
    int menor = menorEntreDosNumeros(x, y);
    int resu;

    for(int i = 0; i < menor; i++)
        resu += mayor;
    return resu;
}
