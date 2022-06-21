#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"

#define TAM_VEC 16

int cmpInts(const void* num1, const void* num2);
int cmpCads(const void* cad1, const void* cad2);
void actualizarCad(void* cadAAct, const void* cad);
int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);

int main()
{
    int vec[TAM_VEC] = {5, 6, 3, 4, 1, 2, 3, 7, 8, 9};
    int elem;

    char vCads[TAM_VEC][20] = {"I","C", "A", "B", "J", "D", "F","I", "I", "G", "H", "E", "A", "G", "B", "K"};
    char cad[20];

    Lista listaPrueba;
    Iterador it;

    crearLista(&listaPrueba); // IMPORTANTE

    /* IMPORTANTE: NO desreferenciar NULL */

//    for(int i = 0; i < TAM_VEC; i++)
//        insertarEnListaOrd(&listaPrueba, &vec[i], sizeof(int), cmpInts);
//
//    crearIterador(&i, &listaPrueba); // ya va a poner a i en el primero de la lista
//    primeroDeLista(&i, &elem, sizeof(int));
//
//    while(!finLista(&i))
//    {
//        printf("%d ", elem);
//
//        siguienteDeLista(&i, &elem, sizeof(int));
//    }

    for(int i = 0; i < TAM_VEC; i++)
        insertarEnListaDesord(&listaPrueba, vCads[i], sizeof(char*));

//    strcpy(cad, "A");
//    eliminarDeListaDesord(&listaPrueba, cad, sizeof(char*), cmpCads);

    //eliminarDuplicadosDeListaDesord(&listaPrueba, cmpCads);
    //insertarOActualizarEnListaDesordAsc(&listaPrueba, "Fiumba", sizeof(char*), cmpCads, actualizarCad);
    //eliminarDeListaOrdDuplicados_ALU(&listaPrueba, cmpCads, actualizarCad);

    ordenarLista(&listaPrueba, cmpCads);

    crearIterador(&it, &listaPrueba); // ya va a poner a i en el primero de la lista
    primeroDeLista(&it, cad, sizeof(char*));

    while(!finLista(&it))
    {
        printf("%s ", cad);

        siguienteDeLista(&it, cad, sizeof(char*));
    }

    return 0;
}

int cmpInts(const void* num1, const void* num2)
{
    int* num_1 = (int*)num1;
    int* num_2 = (int*)num2;

    return (*num_1) - (*num_2);
}

int cmpCads(const void* cad1, const void* cad2)
{
    char* cad_1 = (char*)cad1;
    char* cad_2 = (char*)cad2;

    int cmp = strcmp(cad_1, cad_2);

    return cmp;
}

void actualizarCad(void* cadAAct, const void* cad)
{
    char* cad_1 = (char*)cadAAct;
    char* cad_2 = (char*)cad;

    strcpy(cadAAct, cad);
}

int eliminarDeListaOrdDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    while(*pl && (*pl)->siguiente)
    {
        if(cmp((*pl)->elem, (*pl)->siguiente->elem) == 0)
        {
            //actualizar((*pl)->elem, (*pl)->sig->elem);

            Nodo* nodoAEliminar = (*pl)->siguiente;
            (*pl)->siguiente = nodoAEliminar->siguiente;

            free(nodoAEliminar->elem);
            free(nodoAEliminar);
        }
        else
            pl = &(*pl)->siguiente;
    }

    return TODO_OK;
}

//int eliminarDeListaOrdDuplicadosV2_ALU(Lista* pl, void elem,Cmp cmp, Actualizar actualizar)
//{
//    while(*pl && (*pl)->siguiente)
//    {
//        if(cmp((*pl)->elem, (*pl)->siguiente->elem) == 0)
//        {
//            //actualizar((*pl)->elem, (*pl)->sig->elem);
//
//            Nodo* nodoAEliminar = (*pl)->siguiente;
//            (*pl)->siguiente = nodoAEliminar->siguiente;
//
//            free(nodoAEliminar->elem);
//            free(nodoAEliminar);
//        }
//        else
//            pl = &(*pl)->siguiente;
//    }
//
//    return TODO_OK;
//}
