#include <stdio.h>
#include <stdlib.h>

#define TDA_ARBOL_IMPL_DINAMICA
#include "../TDAArbol/TDAArbol.h"

#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"

#define TAM_VEC 9

typedef struct
{
    char nombreYapellido[50];
    int edad;
    int dni;
}Persona;

void imprimirEnteroArbol(void* elem, void* datosImprimir, int nivel);
void imprimirPersonaArbol(void* elem, void* datosImprimir, int nivel);
void mostrarEntero(void* elem, void* datos);

int cmpInt(const void* elem1, const void* elem2);
int cmpPersonaDNI(const void* persona1, const void* persona2);
int cmpPersonaNombreYApellido(const void* persona1, const void* persona2);

void actualizarEdad(void* actualizado, const void* actualizador);

int cargarArbolDeArchivoOrdenado_ALU(Arbol* pa, const char* nombreArchivo, size_t tamElem, Cmp cmp);
int cargarArbolDeArchivoOrdenadoRec_ALU(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls);

booleano buscarArbol_ALU(Arbol* pa, void* elem, size_t tamElem, Cmp cmp);

int insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int eliminarDeListaDesordDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar);

int main()
{
    Arbol arbol;
    crearArbol(&arbol);

    Persona vecPer[TAM_VEC] = { {"Aaaaa", 0, 54884848},
                                {"Ccccc", 13, 89489158},
                                {"Eeeee", 21, 78415541},
                                {"Aaaaa", 10, 54884848},
                                {"Ggggg", 8, 15200524},
                                {"Iiiii", 7, 15151110},
                                {"Jjjjj", 5, 45151120},
                                {"Ccccc", 9, 89489158},
                                {"Lllll", 7, 51511515}  };

    Lista listaPersonas;
    crearLista(&listaPersonas);
    int i;

    for(i = 0; i < TAM_VEC; i++)
        insertarEnListaAlFinal(&listaPersonas, &vecPer[i], sizeof(Persona));

    eliminarDeListaDesordDuplicados_ALU(&listaPersonas, cmpPersonaNombreYApellido, actualizarEdad);

    i = 0;
    while(eliminarDeListaPrimero(&listaPersonas, &vecPer[i], sizeof(Persona)))
        i++;

    FILE* archPersonas = fopen("Personas.dat", "wb");

    if(!archPersonas)
        return ERR_ARCHIVO;

    fwrite(vecPer, sizeof(Persona), i, archPersonas);

    fclose(archPersonas);

    cargarArbolDeArchivoOrdenado_ALU(&arbol, "Personas.dat", sizeof(Persona), cmpPersonaNombreYApellido);

    imprimirArbol(&arbol, imprimirPersonaArbol, NULL);

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

int cmpPersonaDNI(const void* persona1, const void* persona2)
{
    return ((Persona*)persona1)->dni - ((Persona*)persona2)->dni;
}

int cmpPersonaNombreYApellido(const void* persona1, const void* persona2)
{
    return strcmp(((Persona*)persona1)->nombreYapellido, ((Persona*)persona2)->nombreYapellido);
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


int cargarArbolDeArchivoOrdenado_ALU(Arbol* pa, const char* nombreArchivo, size_t tamElem, Cmp cmp)
{
    FILE* arch = fopen(nombreArchivo, "rb");

    if(!arch)
    {
        fclose(arch);
        return ERR_ARCHIVO;
    }

    fseek(arch, 0L, SEEK_END);

    int cantReg = ftell(arch) / tamElem;

    cargarArbolDeArchivoOrdenadoRec_ALU(arch, pa, tamElem, cmp, 0, cantReg - 1);

    fclose(arch);

    return TODO_OK;
}

int cargarArbolDeArchivoOrdenadoRec_ALU(FILE* arch, Arbol* pa, size_t tamElem, Cmp cmp, int li, int ls)
{
    if(li > ls)
        return FALSO;

    int m = (li + ls) / 2;
    void* reg = malloc(tamElem);

    fseek(arch, m * tamElem, SEEK_SET);
    fread(reg, tamElem, 1, arch);
    insertarEnArbol_ALU(pa, reg, tamElem, cmp, NULL);

    cargarArbolDeArchivoOrdenadoRec_ALU(arch, pa, tamElem, cmp, li, m - 1);
    cargarArbolDeArchivoOrdenadoRec_ALU(arch, pa, tamElem, cmp, m + 1, ls);

    return TODO_OK;
}

int insertarEnArbol_ALU(Arbol* pa, void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    if(!*pa)
    {
        NodoA* nue = malloc(sizeof(NodoA));
        void* elemNodo = malloc(tamElem);

        if(!nue || !elem)
        {
            free(nue);
            free(elem);

            return SIN_MEM;
        }

        memcpy(elemNodo, elem, tamElem);
        nue->elem = elemNodo;
        nue->hDer = NULL;
        nue->hIzq = NULL;

        *pa = nue;

        return TODO_OK;
    }

    int comp = cmp(elem, (*pa)->elem);

    if(comp == 0)
    {
        if(actualizar)
            actualizar((*pa)->elem, elem);

        return DUPLICADO;
    }

    return insertarEnArbol_ALU(comp < 0 ? &(*pa)->hIzq : &(*pa)->hDer, elem, tamElem, cmp, actualizar);
}

int eliminarDeListaDesordDuplicados_ALU(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return FALSO;

    NodoD* act = *pl, * curDup, * nae;

    while(act->ant)
        act = act->ant;

    curDup = act->sig;

    while(act && curDup)
    {
        while(curDup)
        {
            if(cmp(act->elem, curDup->elem) == 0)
            {
                if(actualizar)
                    actualizar(act->elem, curDup->elem);

                nae = curDup;
                curDup = curDup->sig;

                if(*pl == nae)
                {
                    if(nae->sig)
                        *pl = nae->sig;
                    else
                        *pl = nae->ant;
                }

                if(nae->sig)
                    nae->sig->ant = nae->ant;

                if(nae->ant)
                    nae->ant->sig = nae->sig;

                free(nae->elem);
                free(nae);
            }
            else
                curDup = curDup->sig;
        }

        act = act->sig;

        if(act)
            curDup = act->sig;
    }

    return TODO_OK;
}

void actualizarEdad(void* actualizado, const void* actualizador)
{
    ((Persona*)actualizado)->edad += ((Persona*)actualizador)->edad;
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
