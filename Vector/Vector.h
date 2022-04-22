#ifndef VECTOR_H
#define VECTOR_H

#include "../Comun/Comun.h"

#define CAPACIDAD_VECTOR 10

typedef struct
{
    int vec[CAPACIDAD_VECTOR];
    int ce;
}
Vector;

void crearVector(Vector* vector);
booleano insertarEnVectorAlFinal(Vector* vector, int valor);
int insertarEnVectorEnOrdenCDup(Vector* vector, int valor); // Con duplicado
int insertarEnVectorEnOrdenSDup(Vector* vector, int valor); // Sin duplicar
int buscarEnVectorOrdenado(const Vector* vector, int valor);
booleano eliminarDeVectorOrdPorValor(Vector* vector, int valor);
void mostrarVector(const Vector* vector);


#endif // VECTOR_H
