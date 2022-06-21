#include "Nodo.h"
#include "NodoD.h"
#include "NodoA.h"
#include <stdlib.h>
#include <string.h>

Nodo* crearNodo(const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(tamElem); // Necesito reservar espacio en el elemento del nodo para almacenar algo

    if (!nue || !elemNodo) {
        free(nue);
        free(elemNodo);
        return NULL;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue -> tamElem = tamElem;
    nue -> siguiente = NULL;

    return nue;
}

void destruirNodo(Nodo* nae, void* elem, size_t tamElem)
{
    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
    free(nae->elem);
    free(nae);

    /* En elem me puede venir solo un campo, pero esta funcion devuelve
    los datos completos.

    Ejemplo:

    Me llego por elem el dato de dni de un alumno, pero antes de eliminarlo yo piso
    a elem con todos los datos del alumno. Ahora en vez de tener solo el dni en elem
    tengo todos los datos */
}

void destruirNodoSinGuardar(Nodo* nae)
{
    free(nae->elem);
    free(nae);
}

// Lista Doble

NodoD* crearNodoD(const void* elem, size_t tamElem)
{
    NodoD* nue = (NodoD*)malloc(sizeof(NodoD));
    void* elemNodo = malloc(tamElem); // Necesito reservar espacio en el elemento del nodo para almacenar algo

    if (!nue || !elemNodo) {
        free(nue);
        free(elemNodo);
        return NULL;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue -> tamElem = tamElem;
    nue -> sig = NULL;
    nue->ant = NULL;

    return nue;
}

void destruirNodoD(NodoD* nae, void* elem, size_t tamElem)
{
    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
    free(nae->elem);
    free(nae);
}

void destruirNodoSinGuardarD(NodoD* nae)
{
    free(nae->elem);
    free(nae);
}

//Arbol

NodoA* crearNodoA(const void* elem, size_t tamElem)
{
    NodoA* nue = (NodoA*)malloc(sizeof(NodoA));
    void* elemNodo = malloc(tamElem); // Necesito reservar espacio en el elemento del nodo para almacenar algo

    if (!nue || !elemNodo) {
        free(nue);
        free(elemNodo);
        return NULL;
    }

    memcpy(elemNodo, elem, tamElem);
    nue->elem = elemNodo;
    nue-> tamElem = tamElem;
    nue-> hIzq = NULL;
    nue-> hDer = NULL;

    return nue;
}

void destruirNodoA(NodoA* nae, void* elem, size_t tamElem)
{
    memcpy(elem, nae->elem, min(tamElem, nae->tamElem));
    free(nae->elem);
    free(nae);
}

void destruirNodoSinGuardarA(NodoA* nae)
{
    free(nae->elem);
    free(nae);
}
