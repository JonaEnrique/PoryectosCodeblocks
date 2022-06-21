#define TDA_PILA_IMPL_DINAMICA

#include <stdlib.h>
#include <string.h>
#include "../TDAPila/TDAPila.h"

void crearPila(Pila* pp)
{
    *pp = NULL;// --> Hacemos que la pila apunte a NULL, o sea a ningun nodo
}

booleano apilar(Pila* pp, const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem);

    if(!nue || !elemNodo) // Siempre tengo que preguntar si se reservo la memoria
    {
        // No pasa nada si le mandas NULL a free
        free(nue);
        free(elemNodo);
        return FALSO;
    }

    nue->elem = elemNodo; // Reservo memoria para el elemento, hago apuntar a elem al pedazo de memoria que reservo elemNodo
    nue->tamElem = tamElem;
    nue->sig = *pp;

    *pp = nue; // == pp = &nue ?
    memcpy(elemNodo, elem, tamElem); // Asigno el elemento --> Antes ya reserve la memoria para el elemento

    return VERDADERO;
}

booleano desapilar(Pila* pp, void* elem, size_t tamElem)
{
    if(!*pp) // Verificamos si la pila está vacia
        return FALSO;

    Nodo* nae = *pp; // Agarramos el nodo del tope, o sea el nodo a eliminar(nae)

    memcpy(elem, nae->elem, min(tamElem, nae->tamElem)); // Copiamos el elemento al puntero que nos llego de main
    *pp = nae->sig; // Asigamos el nuevo tope, o sea el siguiente

    /*Liberamos la memoria del nodo desapilado*/
    free(nae->elem);
    free(nae);

    return VERDADERO;
}

booleano verTopeDePila(const Pila* pp, void* elem, size_t tamElem)
{
    if(!*pp) // Verificamos si la pila está vacia
        return FALSO;

    Nodo* tope = *pp; // Agarramos el tope, o sea el nodo a copiarle el elemento

    memcpy(elem, tope->elem, min(tamElem, tope->tamElem)); // Copiamos el elemento al puntero que nos llego d main

    return VERDADERO;
}

booleano pilaLlena(const Pila* pp, size_t tamElem)
{
    void* nodo = malloc(sizeof(Nodo));
    void* elem = malloc(tamElem);

    free(nodo);
    free(elem);

    return !nodo || !elem;
}

booleano pilaVacia(const Pila* pp)
{
    return !(*pp);
}

void vaciarPila(Pila* pp)
{
    Nodo* nae = *pp; // Agarramos el tope a eliminar

    while(nae) // Verificamos si es que ya está vacio --> apuntamos a NULLS
    {
        *pp = nae->sig; // Sacamos el tope de la pila, asignando a la pila el siguiente nodo
        free(nae->elem); // Liberamos la memoria del elemento del nodo del tope que eliminamos
        free(nae); // Liberamos la memoria del nodo del tope que eliminamos

        nae = *pp; // Agarramos el nuevo tope para eliminarlo
    }
}
