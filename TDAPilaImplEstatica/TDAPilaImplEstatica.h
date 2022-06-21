#ifndef TDAPILAIMPLESTATICA_H
#define TDAPILAIMPLESTATICA_H

//typedef enum {VERDADERO = 1, FALSO=0} booleano;
//#define min(x, y) ((x) < (y)? (x) : (y))
//#define max(x, y) ((x) > (y)? (x) : (y))

#define TAM_PILA 1000

typedef struct
{
    char vPila[TAM_PILA];
    int tope;
}
Pila;

#endif // TDAPILAIMPLESTATICA_H
