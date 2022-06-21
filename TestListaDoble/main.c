#include <stdio.h>
#include <stdlib.h>

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TAM_VEC 14

int cmpInt(const void* num1, const void* num2);

int main()
{
    Lista listaDoblePrueba;
    int v[TAM_VEC] = {9, 5, 2, 7, 8, 10, 11, 4, 1, 3, 12, 6, 2, 10};
    int elem = 9;

    crearLista(&listaDoblePrueba);

    for(int i = 0; i < TAM_VEC; i++)
        insertarEnListaOrdAscSinDupl(&listaDoblePrueba, &v[i], sizeof(int), cmpInt);

    //eliminarDeListaOrdPorValor(&listaDoblePrueba, &elem, sizeof(int), cmpInt);
    eliminarDeListaDesordPorValor(&listaDoblePrueba, &elem, sizeof(int), cmpInt);

//    elem = 31;
//
//    insertarEnListaEnPosicion(&listaDoblePrueba, &elem, sizeof(int), 1);

//    verPrimeroDeLista(&listaDoblePrueba, &elem, sizeof(int));
//    printf("\nPrimero de lista: %d\n", elem);

    elem = 10;
    printf("\n%s: %d\n", buscarEnListaOrd(&listaDoblePrueba, &elem, sizeof(int), cmpInt) ? "Encontrado" : "No encontrado", elem);


    while(!listaVacia(&listaDoblePrueba))
    {
        eliminarDeListaPrimero(&listaDoblePrueba, &elem, sizeof(int));
        printf("%d ", elem);
    }

    printf("\n%s: %d\n", buscarEnListaDesord(&listaDoblePrueba, &elem, sizeof(int), cmpInt) ? "Encontrado" : "No encontrado", elem);

    return 0;
}

int cmpInt(const void* num1, const void* num2)
{
    return *((int*)num1) - *((int*)num2);
}
