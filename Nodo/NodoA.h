#ifndef NODOA_H
#define NODOA_H

#include <stddef.h>

typedef struct SNodoA
{
    void* elem;
    size_t tamElem;
    struct SNodoA* hIzq;
    struct SNodoA* hDer;
}NodoA;

NodoA* crearNodoA(const void* elem, size_t tamElem);
void destruirNodoA(NodoA* nae, void* elem, size_t tamElem);
void destruirNodoSinGuardarA(NodoA* nae);

#endif // NODOA_H
