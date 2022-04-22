#include <stdio.h>
#include <stdlib.h>

#define esDivisor(X, Y) ((X)%(Y)==0 ? 1:0)
#define esNatural(X) ((X)>=0 ? 1:0)

void pda(int num);

int main()
{
    int num;

    do
    {
        printf("Ingrese numero a evlauar: ");
        scanf("%d", &num);
    }while(!esNatural(num));

    while(num != 0)
    {
        pda(num);

        do
        {
            printf("Ingrese numero a evlauar: ");
            scanf("%d", &num);
        }while(!esNatural(num));
    }

    return 0;
}

void pda(int num)
{
    int acumDivisores = 0;

    for(int i = 1; i < num; i++)
        if(esDivisor(num, i))
            acumDivisores += i;

    if(acumDivisores == num)
        printf("PERFECTO\n");
    else
    {
        if(acumDivisores > num)
            printf("ABUNDANTE\n");
        else
            printf("DEFICIENTE\n");
    }
}

/*
if(esDivisor(num, i) == 0)
            printf("%d ", i);
*/
