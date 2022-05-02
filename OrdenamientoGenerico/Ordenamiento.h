#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <stddef.h> // stdio tambien esta

typedef int (*Cmp)(const void*, const void*);

void ordenarGenBurbujeo(int* vector, int ce, size_t tamElem, Cmp cmp);
void ordenarGenSeleccion(void* vector, int ce, size_t tamElem, Cmp cmp);
void ordenarGenInsersion(int* vector, int ce, size_t tamElem, Cmp cmp);

#endif // ORDENAMIENTO_H
