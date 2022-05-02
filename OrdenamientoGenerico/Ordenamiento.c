#include "Ordenamiento.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Funciones que no quiero que use el usario */
void* buscarMenor(void* inicio, void* fin, size_t tamElem, Cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);

void ordenarGenBurbujeo(int* vector, int ce, size_t tamElem, Cmp cmp)
{
    int i = 1, j;


    if()
}

void ordenarGenSeleccion(void* vector, int ce, size_t tamElem, Cmp cmp)
{
    void* i, *menor;
    void* ultimo = vector + (ce - 1)*tamElem;

    for(i = vector; i <= ultimo; i += tamElem) // i <= ce -2
    {
        menor = buscarMenor(i, ultimo, tamElem, cmp);

        if(menor != i)
            intercambiar(i, menor, tamElem);
    }

}

void* buscarMenor(void* inicio, void* fin, size_t tamElem, Cmp cmp)
{
    void* j, *menor;
    menor = inicio;

    for(j = inicio + tamElem; j <= fin; j += tamElem)
    {
        if(cmp(j, menor) < 0)
            menor = j;
    }

    return menor;
}

void intercambiar(void* a, void* b, size_t tamElem)
{
    char aux[tamElem];

    memcpy(aux, a, tamElem); // aux = a
    memcpy(a, b, tamElem); // a = b
    memcpy(b, aux, tamElem); // b = aux

    /*
    void* aux = malloc(tamElem);

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);

    free(aux);
    */
}

void ordenarGenInsersion(int* vector, int ce, size_t tamElem, Cmp cmp);

/* Memoria dinamica heap?
   Memory leaks?
   Es diferente usar char que memoria dinamica  */
