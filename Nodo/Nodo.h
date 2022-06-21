#ifndef NODO_H
#define NODO_H

#include "../Comun/Comun.h"
#include <stddef.h>

typedef struct SNodo
{
    void* elem; // Guarda elemento de tamaño variable, por eso reservamos memoria antes de asignar
    size_t tamElem;
    struct SNodo *siguiente;
}Nodo;

Nodo* crearNodo(const void* elem, size_t tamElem);
void destruirNodo(Nodo* nae, void* elem, size_t tamElem);
void destruirNodoSinGuardar(Nodo* nae);


#endif // NODO_H
