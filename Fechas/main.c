#include "Fecha.h"

int main()
{
    int d, m, a;

    do
    {
        printf("Ingrese una fecha: ");
        scanf("%d%d%d", &d, &m , &a);
    }while(d < 1 || m < 1 || a < 1601);

    if(esFechaValida(d, m, a))
        printf("La fecha es valida");
    else
        printf("La fecha NO es valida");

    return 0;
}
