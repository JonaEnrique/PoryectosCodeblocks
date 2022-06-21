#ifndef TDACOLA_H
#define TDACOLA_H

#include <stddef.h>
#include <string.h>
#include "../Comun/Comun.h"

#ifdef TDA_COLA_IMPL_ESTATICA
    #include "../TDAColaImplEstatica/TDAColaImplEstatica.h"
#endif

#ifdef TDA_COLA_IMPL_DINAMICA
    #include "../TDAColaImplDinamica/TDAColaImplDinamica.h"
#endif

#ifdef TDA_COLA_IMPL_DINAMICA_CIRCULAR
    #include "../TDAColaImplDinamicaCircular/TDAColaImplDinamicaCircular.h"
#endif


/* Arriba se nos elige el prototipo de pila */

void crearCola(Cola* pc);
booleano encolar(Cola* pc, const void* elem, size_t tamElem);
booleano desencolar(Cola* pc, void* elem, size_t tamElem);
booleano verFrenteDeCola(Cola* pc, void* elem, size_t tamElem);
booleano colaVacia(const Cola* pc);
booleano colaLlena(const Cola* pc, size_t tamElem);
void vaciarCola(Cola* pc);

#endif // TDACOLA_H
