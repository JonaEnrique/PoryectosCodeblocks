#include "../Comun/Comun.h"
#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprimirArbolRec(const Arbol* pa, ImprimirElemArbol imprimir, void* datosImprimir, int nivel);
const Arbol* buscarRaizArbol(const Arbol* pa, void* elem, Cmp cmp);
void eliminarRaizArbol(Arbol* pae);

Arbol* menorDeArbol(Arbol* pa);
Arbol* mayorDeArbol(Arbol* pa);

int cargarArbolRec(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls);

int contarNodos(const Arbol* pa); // El usuario no se relaciona con los nodos

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

booleano buscarEnArbol(Arbol* pa, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pa)
        return FALSO;

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        memcpy(elem, (*pa)->elem, min(tamElem, (*pa)->tamElem));
        return VERDADERO;
    }

    return buscarEnArbol(comp > 0 ? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp);
}

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

void vaciarArbol(Arbol* pa)
{
    if(!*pa)
        return;

    vaciarArbol(&(*pa)->hIzq);
    vaciarArbol(&(*pa)->hDer);
    free((*pa)->elem);
    free(*pa);
    *pa = NULL;
}
booleano esArbolCompleto(const Arbol* pa) // Completo hasta el ultimo nivel
{
    int cantNodosArbolEsperada = pow(2, alturaArbol((Arbol*)pa)) - 1;
    int cantNodosArbolReal = contarNodos(pa);

    return cantNodosArbolEsperada == cantNodosArbolReal;
}

int contarNodos(const Arbol* pa)
{
    if(!*pa) // Cuando encuentre un hijo sin arbol, retorna 0 nodos -> NULL
        return 0;

    return contarNodos(&(*pa)->hIzq) + contarNodos(&(*pa)->hDer) + 1; // Suma de nodos de hijo derecho e izquierdo y se le suma la misma raiz que es otro nodo
}

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

int cargarArbolDeArchivoOrdenado(Arbol* pa, const char* nombreArchivo, size_t tamElem, Cmp cmp)
{
    FILE* arch = fopen(nombreArchivo, "rb");

    if(!arch)
    {
        fclose(arch);
        return SIN_MEM;
    }

    fseek(arch, 0L, SEEK_END);

    int cantReg = ftell(arch) / tamElem;

    cargarArbolRec(arch, pa, tamElem, cmp, 0 /* li */, cantReg -1 /* ls */);

    fclose(arch);

    return TODO_OK;
}

int cargarArbolRec(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls)
{
    if(li > ls)
        return TODO_OK;

    void* reg = malloc(tamElem);

    int m = (li + ls) / 2;

    fseek(arch, m * tamElem, SEEK_SET);

    fread(reg, tamElem, 1, arch);

    insertarEnArbol(pa, reg, tamElem, cmp, NULL);

    free(reg);

    cargarArbolRec(arch, pa, tamElem, cmp , li, m - 1);
    cargarArbolRec(arch, pa, tamElem, cmp , m + 1, ls);

    return TODO_OK;
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
