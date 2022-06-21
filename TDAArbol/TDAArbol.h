#ifndef TDAARBOL_H
#define TDAARBOL_H

#include <stddef.h>
#include <string.h>
#include "../Comun/Comun.h"

#ifdef TDA_ARBOL_IMPL_DINAMICA
    #include "../TDAArbolImplDinamica/TDAArbolImplDinamica.h"
#endif

typedef enum
{
    COMPLETO, BALANCEADO, AVL, DESBALANCEADO
}TipoArbol;

typedef void (*ImprimirElemArbol)(void* elem, void* datosImprimir, int nivel);

void crearArbol(Arbol* pa);
int insertarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
booleano buscarArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);
int alturaArbol(Arbol* pa);
booleano arbolVacio(Arbol* pa);
void recorrerArbolPre(Arbol* pa, Accion accion, void* datosAccion);
void recorrerArbolEn(Arbol* pa, Accion accion, void* datosAccion);
void recorrerArbolPos(Arbol* pa, Accion accion, void* datosAccion);
void vaciarArbol(Arbol* pa);
booleano esArbolCompleto(const Arbol* pa); // Completo hasta el ultimo nivel
booleano esArbolBalanceado(const Arbol* pa); // Completo hasta el penultimo nivel
booleano esArbolAVL(const Arbol* pa);
TipoArbol tipoArbol(const Arbol* pa);
void imprimirArbol(const Arbol* pa, ImprimirElemArbol accion, void* datosImprimir);

#endif // TDAARBOL_H
