#ifndef TDALISTAIMPLDINAMICADOBLE_H
#define TDALISTAIMPLDINAMICADOBLE_H

#include "../Nodo/NodoD.h"

typedef NodoD* Lista;

typedef struct
{
    NodoD* primero;
    NodoD* act;
}
Iterador;

#endif // TDALISTAIMPLDINAMICADOBLE_H
