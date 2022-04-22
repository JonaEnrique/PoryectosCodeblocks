#include <stdio.h>
#include "Vector.h"

void crearVector(Vector* vector) // Funciona como un constructor
{
    vector->ce = 0;
}


booleano insertarEnVectorAlFinal(Vector* vector, int valor)
{
    if(vector->ce == CAPACIDAD_VECTOR)
        return FALSO;

    vector->vec[vector->ce] = valor;
    vector->ce++;
//    (*ce)++; // el ++ tiene mas precedencia que el *

    return VERDADERO;
}

int insertarEnVectorEnOrdenCDup(Vector* vector, int valor)
{
    if(vector->ce == CAPACIDAD_VECTOR)
        return SIN_MEM;

    int i = vector->ce - 1;

    while(i >= 0 && valor < vector->vec[i])
    {
        vector->vec[i + 1] = vector->vec[i];
        i--;
    }

    vector->vec[i + 1] = valor;


    vector->ce++;

    return TODO_OK;
}

int buscarEnVectorOrdenado(const Vector* vector, int valor)
{
    int i = 0;

    while(vector->vec[i] < valor && i < vector->ce)
        i++;

    if(i == vector->ce || valor < vector->vec[i])
        return NO_ENCONTRADO;
    
    return i;
}

booleano eliminarDeVectorOrdPorValor(Vector* vector, int valor)
{
    int posElim = buscarEnVectorOrdenado(vector, valor);

    if(posElim == NO_ENCONTRADO)
        return FALSO;

    int i;
    
    for(i = posElim; i <= vector->ce - 2; i++)
        vector->vec[i] = vector->vec[i + 1];

    vector->ce--;

    return VERDADERO;
}

void mostrarVector(const Vector* vector)
{
    int i;

    for(i = 0; i < vector->ce; i++)
        printf("%d ", vector->vec[i]);

    printf("\n");
}

