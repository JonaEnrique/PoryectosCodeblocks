#include <stdio.h>
#include <stdlib.h>

#define TDA_PILA_IMPL_DINAMICA
#include "../TDAPila/TDAPila.h"

#define TAM_VEC 10

int cargarVecEnPila(int* v, int cantElem, Pila* pp);
int ordenarVecConPila(int* v, int cantElem);

int main()
{
    int v[TAM_VEC] = {2, 0, 3, 4, 23, 11, 7, 8, 5, 6}, elem;
    Pila pilaDeEnteros;

    crearPila(&pilaDeEnteros);

//    cargarVecEnPila(v, TAM_VEC, &pilaDeEnteros);

//    for(int i = 0; i < TAM_VEC; i++)
//    {
//        desapilar(&pilaDeEnteros, &elem, TAM_VEC);
//        printf("%d ", elem);
//    }

    printf("Antes de ordenar: \n");
    for(int i = 0; i < TAM_VEC; i++)
        printf("%d ", v[i]);

    puts("\n");

    ordenarVecConPila(v, TAM_VEC);

    printf("Despues de ordenar: \n");
    for(int i = 0; i < TAM_VEC; i++)
        printf("%d ", v[i]);

    return 0;
}

int cargarVecEnPila(int* v, int cantElem, Pila* pp)
{
    v = v + cantElem -1;

    for(int i = 0; i < cantElem; i++)
    {
        apilar(pp, v, sizeof(int));
        v--;
    }

    return TODO_OK;
}

int ordenarVecConPila(int* v, int cantElem)
{
    Pila pila1, pila2;
    int elem;

    crearPila(&pila1);
    crearPila(&pila2);

    for(int i = 0; i < cantElem; i++)
    {
        if(pilaVacia(&pila1) || verTopeDePila(&pila1, &elem, sizeof(int)) < elem)
            apilar(&pila1, &v[i], sizeof(int));
        else
        {
            while(verTopeDePila(&pila1, &elem, sizeof(int)) && v[i] >= elem)
            {
                desapilar(&pila1, &elem, sizeof(int));
                apilar(&pila2, &elem, sizeof(int));
            }

            apilar(&pila1, &v[i], sizeof(int));

            while(!pilaVacia(&pila2))
            {
                desapilar(&pila2, &elem, sizeof(int));
                apilar(&pila1, &elem, sizeof(int));
            }
        }
    }

    for(int i = 0; i < cantElem; i++)
    {
        desapilar(&pila1, &elem, TAM_VEC);
        v[i] = elem;
    }

    return TODO_OK;
}
