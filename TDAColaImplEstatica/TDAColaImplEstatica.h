#ifndef TDACOLAIMPLESTATICA_H
#define TDACOLAIMPLESTATICA_H

#include <stddef.h>

#define TAM_COLA 50000

typedef struct
{
    char vec[TAM_COLA];
    unsigned frente;
    unsigned fondo;
    size_t tamDisponible;
}
Cola;

#endif // TDACOLAIMPLESTATICA_H
