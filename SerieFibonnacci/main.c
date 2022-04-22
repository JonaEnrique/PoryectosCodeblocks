#include <stdio.h>
#include <stdlib.h>

int fibonacci(int);

int main()
{
    int num;

    printf("Ingresar numero para ver si pertenece a la serie Fibonacci: ");
    scanf("%d", &num);

    fibonacci(num) ? printf("Pertenece.\n") : printf("NO pertenece.\n");

    system("pause");

    return 0;
}

int fibonacci(int num)
{
    int ant = 0, act = 1, sum = 1, esFibonacci = 0;

    while(num >= sum)
    {
        if(sum == num)
            esFibonacci = 1;

        printf("%d\n", sum);
        sum = ant + act;

        ant = act;
        act = sum;
    }

    return esFibonacci;
}
