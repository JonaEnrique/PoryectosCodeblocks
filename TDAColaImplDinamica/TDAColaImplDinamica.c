#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"

void crearCola(Cola* pc)
{
    pc->frente = pc->fondo = NULL;
}

booleano encolar(Cola* pc, const void* elem, size_t tamElem)
{
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    void* elemNodo = malloc(sizeof(tamElem));

    if(!nue || !elemNodo)
    {
        free(nue);
        free(elemNodo);

        return FALSO;
    }

    memcpy(elemNodo, elem, tamElem);

    nue->elem = elemNodo;
    nue->tamElem = tamElem;
    nue->siguiente = NULL;

    if(pc->fondo)
        pc->fondo->siguiente = nue;
    else
        pc->frente = nue;

    pc->fondo = nue;

    return VERDADERO;
}

booleano desencolar(Cola* pc, void* elem, size_t tamElem)
{
    if(!pc->frente)
         return FALSO;

    Nodo* nae = pc->frente;
    pc->frente = nae->siguiente;

    if(!pc->frente)
        pc->fondo = NULL;

    memcpy(elem, nae->elem, min(nae->tamElem, tamElem));

    free(nae->elem);
    free(nae);

    return VERDADERO;
}

booleano verFrenteDeCola(Cola* pc, void* elem, size_t tamElem)
{
    if(!pc->frente)
         return FALSO;

    Nodo* frente = pc->frente;

    memcpy(elem, frente, min(frente->tamElem, tamElem));

    return VERDADERO;
}

booleano colaVacia(const Cola* pc)
{
    return pc->frente == NULL;
}

booleano colaLlena(const Cola* pc, size_t tamElem)
{
    void* nodo = malloc(sizeof(Nodo));
    void* elem = malloc(tamElem);

    free(nodo);
    free(elem);

    return !nodo || !elem;
}

void vaciarCola(Cola* pc)
{
    Nodo* nae;
    Nodo* frente = pc->frente;

    while(frente)
    {
        nae = frente;
        frente = nae->siguiente;

        free(nae->elem);
        free(nae);
    }
    pc->frente = pc->fondo = NULL;
}
