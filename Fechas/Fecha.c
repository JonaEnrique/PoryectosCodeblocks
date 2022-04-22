#include "Fecha.h"

int esBisiesto(int a)
{
    return a % 4 == 0 || (a % 100 == 0 && a % 400 == 0) ? 1 : 0;

}

int cantDiasDelMes(int m, int a)
{
    int cantDiasXMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int cantDiasXMesBis[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(esBisiesto(a))
        return cantDiasXMesBis[m - 1];
    else
        return cantDiasXMes[m - 1];
}

int esFechaValida(int d, int m , int a)
{
    if(a >= 1601)
        if(m >= 1 && m <= 12)
            if(d >= 1 && d <= cantDiasDelMes(m, a))
                return 1;
    return 0;
}
