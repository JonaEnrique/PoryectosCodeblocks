#include "../Comun/Comun.h"
#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
#include "stdlib.h"

void imprimirArbolRec(const Arbol* pa, ImprimirElemArbol imprimir, void* datosImprimir, int nivel);
const Arbol* buscarRaizArbol(const Arbol* pa, void* elem, Cmp cmp);
void eliminarRaizArbol(Arbol* pae);
Arbol* menorDeArbol(Arbol* pa);
Arbol* mayorDeArbol(Arbol* pa);

void crearArbol(Arbol* pa)
{
    *pa = NULL;
}

int insertarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    if(!*pa) // -> Caso base es que el arbol este vacio
    {
        *pa = crearNodoA(elem, tamElem);

        return !*pa ? SIN_MEM : TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0) // Otro caso base si es que es duplicado
    {
        if(actualizar)
            actualizar((*pa)->elem, elem);

        return DUPLICADO;
    }

    return insertarEnArbol(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp, actualizar);
/*
    int comp;

    while (*pa)
    {
        comp = cmp(elem, (*pa)->elem);

        if(comp == 0)
        {
            if(actualizar)
                actualizar((*pa)->elem, elem);

            return DUPLICADO;
        }

        if(comp < 0)
            pa = &(*pa)->hIzq;
        else
            pa = &(*pa)->hDer;
    }

    *pa = crearNodoA(elem, tamElem); // Lo creo y lo engancho

    return !*pa? SIN_MEM : TODO_OK;
*/
}
booleano buscarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);

booleano eliminarDeArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    Arbol* pae = (Arbol*)buscarRaizArbol(pa, elem, cmp);

    if(!pae) // Pregunto sin desreferenciar porque estoy preguntando si lo encontro, y puede ser NULL
        return FALSO;

    memcpy(elem, (*pae)->elem, min(tamElem, (*pae)->tamElem));
    free((*pae)->elem); // Elimina el elemento no el nodo

    eliminarRaizArbol(pae); // Elimina el nodo no el elemento

    return TODO_OK;
}

const Arbol* buscarRaizArbol(const Arbol* pa, void* elem, Cmp cmp)
{
    if(!*pa)
        return NULL;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
        return pa;

    return buscarRaizArbol(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, elem, cmp);
}

void eliminarRaizArbol(Arbol* pae)
{
    if(!(*pae)->hIzq && !(*pae)->hDer) // Caso base es que tiene dos hijos
    {
        free(*pae); // -> Libera el nodo
        *pae = NULL; // -> Lo desengancha
        return;
    }

    int hi = alturaArbol(&(*pae)->hIzq);
    int hd = alturaArbol(&(*pae)->hDer);

    Arbol* par = hi > hd ? mayorDeArbol(&(*pae)->hIzq) : menorDeArbol(&(*pae)->hDer); // Puntero al arbol reemplazante

    (*pae)->elem = (*par)->elem;
    (*pae)->tamElem = (*par)->tamElem;

    eliminarRaizArbol(par);
}

booleano arbolVacio(Arbol* pa)
{
    return !*pa;
}

int alturaArbol(Arbol* pa)
{
   if(!*pa)
        return 0;

    return max(alturaArbol(&(*pa)->hIzq), alturaArbol(&(*pa)->hDer)) + 1;
}

Arbol* menorDeArbol(Arbol* pa) // Siempre recibo un puntero no vacio de eliminar porque antes pregunte si tenia hijos -> Ver eliminarRaizArbol
{
    if(!(*pa)->hIzq)
        return pa;

    return menorDeArbol(&(*pa)->hIzq);
}

Arbol* mayorDeArbol(Arbol* pa) // Siempre recibo un puntero no vacio de eliminar porque antes pregunte si tenia hijos -> Ver eliminarRaizArbol
{
    if(!(*pa)->hDer)
        return pa;

    return mayorDeArbol(&(*pa)->hDer);
}


void recorrerArbolPre(Arbol* pa, Accion accion, void* datosAccion)
{
    if(!*pa)
        return;

    accion((*pa)->elem, datosAccion); // La accion siempre va a ir
    recorrerArbolPre(&(*pa)->hIzq, accion, datosAccion);
    recorrerArbolPre(&(*pa)->hDer, accion, datosAccion);
}

void recorrerArbolEn(Arbol* pa, Accion accion, void* datosAccion)
{
    if(!*pa)
        return;

    recorrerArbolEn(&(*pa)->hIzq, accion, datosAccion);
    accion((*pa)->elem, datosAccion);
    recorrerArbolEn(&(*pa)->hDer, accion, datosAccion);
}

void recorrerArbolPos(Arbol* pa, Accion accion, void* datosAccion)
{
    if(!*pa)
        return;

    recorrerArbolPos(&(*pa)->hIzq, accion, datosAccion);
    recorrerArbolPos(&(*pa)->hDer, accion, datosAccion);
    accion((*pa)->elem, datosAccion);
}

void vaciarArbol(Arbol* pa);
booleano esArbolCompleto(const Arbol* pa); // Completo hasta el ultimo nivel
booleano esArbolBalanceado(const Arbol* pa); // Completo hasta el penultimo nivel
booleano esArbolAVL(const Arbol* pa);
TipoArbol tipoArbol(const Arbol* pa);

void imprimirArbol(const Arbol* pa, ImprimirElemArbol imprimir, void* datosImprimir)
{
    imprimirArbolRec(pa, imprimir, datosImprimir, 0);
}

void imprimirArbolRec(const Arbol* pa, ImprimirElemArbol imprimir, void* datosImprimir, int nivel)
{
    if(!*pa)
        return;

    imprimirArbolRec(&(*pa)->hDer, imprimir, datosImprimir, nivel + 1);
    imprimir((*pa)->elem, datosImprimir, nivel);
    imprimirArbolRec(&(*pa)->hIzq, imprimir, datosImprimir, nivel + 1);
}

//void crearArbol(Arbol* pa)
//{
//    pa = NULL;
//}
//
//int insertarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
//{
//    if(!*pa)
//    {
//        NodoA* nodoAInsertar = malloc(sizeof(NodoA*));
//        void* elemNodo = malloc(tamElem);
//
//        if(!nodoAInsertar || !elemNodo)
//        {
//            free(nodoAInsertar);
//            free(elemNodo);
//
//            return FALSO;
//        }
//
//        memcpy(elem, elemNodo, tamElem);
//        nodoAInsertar->elem = elem;
//        nodoAInsertar->tamElem = tamElem;
//        nodoAInsertar->hDer = NULL;
//        nodoAInsertar->hIzq = NULL;
//
//        *pa = nodoAInsertar;
//    }
//
//    int cmp = cmp(elem, (*pa)->elem);
//
//    if(cmp == 0)
//        return DUPLICADO;
//
//    return insertarEnArbol()
//}
