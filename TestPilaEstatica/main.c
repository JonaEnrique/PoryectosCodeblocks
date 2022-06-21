#include <stdio.h>
#include <stdlib.h>

#include "../PilaEstatica/Pila.h"

int main()
{
    int v[10] =  {1, 2,  3, 4, 5, 6, 7, 8, 9, 10};
    int elem;
    Pila pilaEntero;

    crearPila(&pilaEntero);

    for(int i = 0; i < 10; i++)
        apilar(&pilaEntero, &v[i], sizeof(int));

    verTopeDePila(&pilaEntero, &elem, sizeof(int));
    printf("Tope: %d\n", elem);

    for(int i = 0; i < 10; i++)
    {
        desapilar(&pilaEntero, &elem, sizeof(int));
        printf("%d ", elem);
    }

    return 0;
}

/*Ordenar con dos pilas*/
