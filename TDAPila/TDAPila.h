#ifndef TDAPILA_H
#define TDAPILA_H

#include <stddef.h>
#include <string.h>
#include "../Comun/Comun.h"

#ifdef TDA_PILA_IMPL_ESTATICA
    #include "../TDAPilaImplEstatica/TDAPilaImplEstatica.h"
#else
    #include "../TDAPilaImplDinamica/TDAPilaImplDinamica.h"
#endif


/* Arriba se nos elige el prototipo de pila */

void crearPila(Pila* pp);
booleano apilar(Pila* pp, const void* elem, size_t tamElem);
booleano desapilar(Pila* pp, void* elem, size_t tamElem);
booleano verTopeDePila(const Pila* pp, void* elem, size_t tamElem);
booleano pilaVacia(const Pila* pp);
booleano pilaLlena(const Pila* pp, size_t tamElem);
void vaciarPila(Pila* pp);

#endif // TDAPILA_H
