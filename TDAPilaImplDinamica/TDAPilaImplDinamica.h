#ifndef TDAPILAIMPLDINAMICA_H
#define TDAPILAIMPLDINAMICA_H

typedef struct SNodo
{
    void* elem;
    size_t tamElem;
    struct SNodo* sig;
}
Nodo;

typedef Nodo* Pila;

#endif // TDAPILAIMPLDINAMICA_H
