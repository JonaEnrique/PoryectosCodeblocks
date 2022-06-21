#define TDA_COLA_IMPL_DINAMICA_CIRCULAR

#include "../TDACola/TDACola.h"

void crearCola(Cola* pc)
{
    *pc = NULL;
}

booleano encolar(Cola* pc, const void* elem, size_t tamElem)
{
    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return FALSO;
    
    if(*pc)
    {
        nue->siguiente = (*pc)->siguiente;
        (*pc)->siguiente = nue;
    }
    else
    {
        nue->siguiente = nue;
    }

    *pc = nue;
    
    return VERDADERO;
}

booleano desencolar(Cola* pc, void* elem, size_t tamElem);
booleano verFrenteDeCola(Cola* pc, void* elem, size_t tamElem);
booleano colaVacia(const Cola* pc);
booleano colaLlena(const Cola* pc, size_t tamElem);
void vaciarCola(Cola* pc);



// Clase 8 55:00