#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double factoreal(double);
double euler(int, double);

int main()
{
//    double num, m, n;
//
//    printf("Ingresar numero a sacarle el facotoreal: ");
//    scanf("%lf", &num);
//
//    while(num != 0)
//    {
//        printf("Factoreal: %lf\n\n", factoreal(num));
//
//        printf("Ingresar numero a sacarle el facotoreal: ");
//        scanf("%lf", &num);
//    }
//
//    printf("\nNumero combinatorio: \n");
//    printf("m: ");
//    scanf("%lf", &m);
//    printf("n: ");
//    scanf("%lf", &n);
//
//    printf("Resultado de combinatoria: %lf", factoreal(m)/(factoreal(n)*factoreal(m - n)));


    printf("Euler: %lf", euler(20, 0.000000001));

    return 0;
}

double factoreal(double n)
{
    return n ? factoreal(n - 1) * n : 1;
}

//double combinatoria(double m, double n)
//{
//    return n ? factoreal(n - 1) * n : 1;
//}

double euler(int x, double TOL)
{
    double e = 1, termino;
    int i = 1;

    do
    {
        e += pow(x, i)/factoreal(i);
        termino = pow(x, i)/factoreal(i);

        i++;
    }while(termino >= TOL);

    return e;
}
