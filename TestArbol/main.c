#include <stdio.h>
#include <stdlib.h>

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define TAM_VEC 7

typedef struct
{
    char nombreYapellido[50];
    int edad;
    int dni;
}Persona;

int cmpInt(const void* elem1, const void* elem2);
void imprimirEnteroArbol(void* elem, void* datosImprimir, int nivel);
void imprimirPersonaArbol(void* elem, void* datosImprimir, int nivel);
void mostrarEntero(void* elem, void* datos);
int cmpPersona(const void* persona1, const void* persona2);

int main()
{
    Arbol arbol;
    crearArbol(&arbol);

    Persona vecPer[TAM_VEC] = { {"Aaaaa", 21, 54884848},
                                {"Ccccc", 30, 89489158},
                                {"Eeeee", 26, 78415541},
                                {"Ggggg", 48, 15200524},
                                {"Iiiii", 54, 15151110},
                                {"Jjjjj", 01, 45151120},
                                {"Lllll", 02, 51511515}  };
    int i;

    for(i = 0; i < TAM_VEC; i++)
        insertarEnArbol(&arbol, &vecPer[i], sizeof(Persona), cmpPersona, NULL);

    imprimirArbol(&arbol, imprimirPersonaArbol, NULL);
//    for(int i = 0; i < TAM_VEC; i++)
//    {
//        printf("%s\n  %d\n  %d\n");
//    }

    //vaciarArbol(&arbol);

    return 0;
}

int cmpInt(const void* elem1, const void* elem2)
{
    return *(int*)elem1 - *(int*)elem2;
}

void imprimirEnteroArbol(void* elem, void* datosImprimir, int nivel)
{
    int i;

    for(i = 0; i < nivel; i++)
        putchar('\t');

    printf("%d\n", *(int*)elem);
}

void mostrarEntero(void* elem, void* datos)
{
    printf("%d ", *(int*)elem);
}

int cmpPersona(const void* persona1, const void* persona2)
{
    return ((Persona*)persona1)->dni - ((Persona*)persona2)->dni;
}

void imprimirPersonaArbol(void* elem, void* datosImprimir, int nivel)
{
    int i;

    for(i = 0; i < nivel; i++)
        putchar('\t');

    printf("   %s\n", ((Persona*)elem)->nombreYapellido);

    for(i = 0; i < nivel; i++)
        putchar('\t');

    printf("  %d\n", ((Persona*)elem)->dni);

    for(i = 0; i < nivel; i++)
        putchar('\t');

    printf("     %d\n", ((Persona*)elem)->edad);
}

/*
    int elems[] = {5, 3, 7, 2, 1, 6, 4, 9, 8, 10};
    int elem;

    for(int i = 0; i < 10; i++)
    {
        insertarEnArbol(&arbol, &elems[i], sizeof(int), cmpInt, NULL);
    }

    imprimirArbol(&arbol, imprimirEnteroArbol, NULL);
    printf("\n-------------------------------------------\n");

    elem = 5;
    eliminarDeArbol(&arbol, &elem, sizeof(int), cmpInt);
    imprimirArbol(&arbol, imprimirEnteroArbol, NULL);
    printf("\n-------------------------------------------\n");

    elem = 7;
    eliminarDeArbol(&arbol, &elem, sizeof(int), cmpInt);
    imprimirArbol(&arbol, imprimirEnteroArbol, NULL);
    printf("\n-------------------------------------------\n");

    elem = 6;
    eliminarDeArbol(&arbol, &elem, sizeof(int), cmpInt);
    imprimirArbol(&arbol, imprimirEnteroArbol, NULL);
    printf("\n-------------------------------------------\n");

    elem = 10;
    eliminarDeArbol(&arbol, &elem, sizeof(int), cmpInt);
    imprimirArbol(&arbol, imprimirEnteroArbol, NULL);
   printf("\n-------------------------------------------\n");

    printf("\nRecorridos de arbol: \n");

    printf("Arbol en orden: ");
    recorrerArbolEn(&arbol, mostrarEntero, NULL);
    putchar('\n');
    printf("Arbol en pre-orden: ");
    recorrerArbolPre(&arbol, mostrarEntero, NULL);
    putchar('\n');
    printf("Arbol en pos-orden: ");
    recorrerArbolPos(&arbol, mostrarEntero, NULL);
    putchar('\n');
*/
