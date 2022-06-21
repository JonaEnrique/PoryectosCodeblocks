#define TDA_PILA_IMPL_ESTATICA
#include "../TDAPila/TDAPila.h"

void crearPila(Pila* pp)
{
    pp->tope = 0;
}

booleano apilar(Pila* pp, const void* elem, size_t tamElem)
{
    if(tamElem + sizeof(size_t) > TAM_PILA - pp->tope) // (Elemento + su tama�o, a insertar) > Espacio disponible en la pila
        return FALSO;

    memcpy(pp->vPila + pp->tope, elem, tamElem); // Apilo elemento
    pp->tope += tamElem; // Muevo cursor
    *(size_t*)(pp->vPila + pp->tope) = tamElem; // Esto es igual a hacer memcpy, pero es mas "rapido" // Apilo tamaño de elemento
    /* memcpy(pp->vPila + pp->tope, tamElem, sizeof(size_t))*/
    pp->tope += sizeof(size_t); // Muevo cursor

    return VERDADERO;
}

booleano desapilar(Pila* pp, void* elem, size_t tamElem)
{
    if(pp->tope == 0) // Si la pila est� vacia, no desapilo nada
        return FALSO;

    pp->tope -= sizeof(size_t);
    size_t tamElemAp = *(size_t*)(pp->vPila + pp->tope);
    pp->tope -= tamElemAp;
    memcpy(elem, pp->vPila + pp->tope, min(tamElem, tamElemAp));

    return VERDADERO;
}
booleano verTopeDePila(const Pila* pp, void* elem, size_t tamElem)
{
    if(pp->tope == 0)
        return FALSO;

    int tope = pp->tope; // Hago otra variable porque no quiero que se "desapile" el tope
    tope -= sizeof(size_t);
    size_t tamElemAp = *(size_t*)(pp->vPila + tope);
    tope -= tamElemAp;
    memcpy(elem, pp->vPila + tope, min(tamElem, tamElemAp));

    return VERDADERO;
}

booleano pilaVacia(const Pila* pp)
{
//    return pp->tope == 0 ? VERDADERO:FALSO;
    return pp->tope == 0;
}

booleano pilaLlena(const Pila* pp, size_t tamElem)
{
//    int cmp = (TAM_PILA - pp->tope) - tamElem;
//    return cmp < 0 ? FALSO:VERDADERO;


    return tamElem + sizeof(size_t) > TAM_PILA - pp->tope;
}

void vaciarPila(Pila* pp)
{
    pp->tope = 0;
}
