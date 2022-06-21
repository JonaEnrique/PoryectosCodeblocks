#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TDA_PILA_IMPL_DINAMICA
#include "../TDAPila/TDAPila.h"

#define ERROR_PILA_LLENA 1
#define TAM_RES 1001
#define ERROR_VEC_RES_LLENO 1001

#define aBin(n) ((n) - '0')
#define aChar(n) ((n) + '0')

booleano apilarCeros(Pila* pp, unsigned cantCeros);
booleano apilarNumero(Pila* pp, const char* numero);
booleano desapilarNumero(Pila* pp, char* numero, size_t tamNumero);

int main(int argc, char* argv[]) /* SOLO LINKEAR UNA LIBRERIA */
{
    Pila p1, p2, pr;


    crearPila(&p1);
    crearPila(&p2);
    crearPila(&pr);

    int cantDigN1 = strlen(argv[1]);
    int cantDigN2 = strlen(argv[2]);

    int difDig = cantDigN1 - cantDigN2;

    if(!apilarCeros(difDig < 0 ? &p1 : &p2, abs(difDig)))
    {
        printf("No hay memoria");
        return ERROR_PILA_LLENA;
    }

    if(!apilarNumero(&p1, argv[1]) || !apilarNumero(&p2, argv[2]))
    {
        printf("No hay memoria");
        return ERROR_PILA_LLENA;
    }

    int dr, ac = 0;
    char d1c, d2c, drc, ac1c = '1';

    while (!pilaVacia(&p1))
    {
        desapilar(&p1, &d1c, sizeof(char));
        desapilar(&p2, &d2c, sizeof(char));

        dr = aBin(d1c) + aBin(d2c) + ac;
        ac = dr / 10;
        drc = aChar(dr % 10);

        if(!apilar(&pr, &drc, sizeof(char)))
            return ERROR_PILA_LLENA;
    }

    if(ac > 0)
        if(!apilar(&pr, &ac1c, sizeof(char)))
            return ERROR_PILA_LLENA;

    char numeroRes[TAM_RES];

    if(!desapilarNumero(&pr, numeroRes, TAM_RES))
        return ERROR_VEC_RES_LLENO;

    puts(numeroRes);

    return 0;
}

booleano apilarCeros(Pila* pp, unsigned cantCeros)
{
    char cero = '0';

    for(unsigned i = 0; i < cantCeros; i++)
        if(!apilar(pp, &cero, sizeof(char)))
            return FALSO;

    return VERDADERO;
}

booleano apilarNumero(Pila* pp, const char* numero)
{
    const char* i = numero; // const char* const i = numero; --> No se puede modificar nada

    while(*i)
    {
        if(!apilar(pp, i, sizeof(char)))
            return FALSO;
        i++; // Puedo modificar el puntero pero no el contenido
    }

    return VERDADERO;
}

booleano desapilarNumero(Pila* pp, char* numero, size_t tamNumero)
{
    char* carAct = numero;
    char* ultCar = numero + tamNumero - 1;

    while(!pilaVacia(pp) && carAct < ultCar)
    {
        desapilar(pp, carAct, sizeof(char));
        carAct++;
    }

    if(!pilaVacia(pp))
        return FALSO;

    *carAct = '\0';

    return VERDADERO;
}
