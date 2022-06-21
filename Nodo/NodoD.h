#ifndef NODOD_H
#define NODOD_H

#include "../Comun/Comun.h"
#include <stddef.h>

typedef struct SNodoD
{
    void* elem;
    size_t tamElem;
    struct SNodoD *ant;
    struct SNodoD *sig;
}NodoD;

NodoD* crearNodoD(const void* elem, size_t tamElem);
void destruirNodoD(NodoD* nae, void* elem, size_t tamElem);
void destruirNodoSinGuardarD(NodoD* nae);

#endif // NODOD_H
