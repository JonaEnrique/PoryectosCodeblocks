#ifndef CADENA_H
#define CADENA_H

#include <ctype.h>

#define esLetra(X) ((X)>='a' && (X)<='z') || ((X)>='A' && (X)<='Z') ? 1:0

typedef enum
{
    FALSO, VERDADERO
}
booleano;

typedef struct
{
    char* ini;
    char* fin;
}
Palabra;

typedef struct
{
    char* cur;
    char* inicad;
    booleano finSec; // Por qué no puedo inicalizarlo? --> Es un tipo de datos, no se puede inicializar?
}
secPal;

void crearSecPal(secPal* sl, const char* cOrig);
booleano finSecPal(const secPal* sl);
void escribirPal(secPal* se, const Palabra* pal);
void escribirCaracter(secPal* se, char caracter);
void reposicionarSecPal(secPal* se, int mov);
void rebobinarSecPal(secPal* se);
void formatearPMayRMin(Palabra* pal); // Primera mayuscula y resto minuscula
void normalizar(const char* cOrig, char* cDest);
void leerPalabra (secPal* sl, Palabra* pal);


#endif // CADENA_H
