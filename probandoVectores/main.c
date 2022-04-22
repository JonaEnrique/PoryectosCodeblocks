#include <stdio.h>
#include <stdlib.h>

#define TAM_VEC 10

void intercambiar(int* x, int* y);
void mostrarVec(int v[], int tam);

int main()
{
    int vec[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numAInsertar = 9, posAInsertar = 3;
    int* auxFin = vec + TAM_VEC - 1;
    int* posInsert = vec + posAInsertar - 1;

    printf("Vector antes de insertar un nuevo numero: ");
    mostrarVec(vec, TAM_VEC);

    puts("\n");

    while(auxFin > posInsert)
    {
        *auxFin = *(auxFin - 1);
        auxFin--;
    }

    *auxFin = numAInsertar;

    printf("Vector antes de despues un nuevo numero: ");
    mostrarVec(vec, TAM_VEC);

    return 0;
}

void intercambiar(int* x, int* y)
{
    int auxY = *y;

    *y = *x;
    *x = auxY;
}

void mostrarVec(int v[], int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%d ", v[i]);
}
