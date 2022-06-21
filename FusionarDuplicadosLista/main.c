#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TDA_LISTA_IMPL
#include "../TDALista/TDALista.h"

#include "../Bibliotecas/miString/miString.h"

#define TAM_VEC 14

typedef struct
{
    int cod;
    char nombreComp[20];
    int cantidad;
    float precio;
}
Componente;

typedef int (*Imprimir)(FILE** arch, void* elem, char tipoTxt);

int imprimirEnTxtComponente(FILE** pArch, void* elem, char tipoTxt);

int cargarVecALista(Lista* pl, void* vec, int tamDato, int tamVec);
void mostrarComponentes(void* elem, void* datos);
int cmpCods(const void* cod1, const void* cod2);
int cmpNombr(const void* nombr1, const void* nombr2);
void actualizarStock(void* datoAccion, const void* acciones);
int listaATxt(Lista* pl, size_t tamDatos, const char* nombreArch, Imprimir impre, char tipoTxt);

int txtABin(const char* nomArchBin, const char* nomArchTxt, char tipoTxt);
int trozarCampos(Componente* comp, char* cad, char tipoTxt);
int mostrarArchBinComponentes(const char*  nombreArchComp);

int main()
{
    Componente vecComponentes[TAM_VEC] = { {1000, "J", 1500, 8900},
                                            {1001, "A", 1600, 8901},
                                            {1002, "N", 1700, 8903},
                                            {1003, "Z", 1800, 8904},
                                            {1004, "B", 1900, 8905},
                                            {1005, "H", 2000, 8906},
                                            {1006, "C", 2100, 8907},
                                            {1007, "F", 2200, 8908},
                                            {1003, "Z", 200, 8904},
                                            {1008, "I", 2300, 8909},
                                            {1004, "B", 2, 8905},
                                            {1000, "J", 1500, 8900},
                                            {1009, "E", 2400, 8910},
                                            {1005, "H", 2000, 8906}, };
    Lista listaComponentes;

    crearLista(&listaComponentes);

    cargarVecALista(&listaComponentes, vecComponentes, sizeof(Componente), TAM_VEC);
    eliminarDeListaDesordDuplicados(&listaComponentes, cmpCods, actualizarStock);
    ordenarLista(&listaComponentes, cmpNombr);
    listaATxt(&listaComponentes, sizeof(Componente), "Componentes.txt", imprimirEnTxtComponente, 'V');
    recorrerLista(&listaComponentes, mostrarComponentes, NULL);
    txtABin("Componentes.dat", "Componentes.txt", 'V
            ');
    printf("Archivo bin: \n");
    mostrarArchBinComponentes("Componentes.dat");

    return 0;
}

int cargarVecALista(Lista* pl, void* vec, int tamDato, int tamVec)
{
    void* fin = vec + (tamVec - 1)*tamDato;

    for(void* i = vec; i <= fin; i += tamDato)
        insertarEnListaDesord(pl, i, tamDato);

    return 0;
}

void mostrarComponentes(void* elem, void* datos)
{
    Componente* comp = (Componente*)elem;
    printf("%d %s %d %.0f\n", comp->cod, comp->nombreComp, comp->cantidad, comp->precio);
}

int cmpCods(const void* cod1, const void* cod2)
{
    Componente* comp1 = (Componente*)cod1;
    Componente* comp2 = (Componente*)cod2;

    return comp1->cod - comp2->cod;
}

int cmpNombr(const void* nombr1, const void* nombr2)
{
    Componente* comp1 = (Componente*)nombr1;
    Componente* comp2 = (Componente*)nombr2;

    return strcmp(comp1->nombreComp, comp2->nombreComp);
}

void actualizarStock(void* datoAccion, const void* acciones)
{
    Componente* comp = (Componente*)datoAccion;
    Componente* compDup = (Componente*)acciones;

    comp->cantidad += compDup->cantidad;
}

int listaATxt(Lista* pl, size_t tamDatos, const char* nombreArch, Imprimir impre, char tipoTxt)
{
    FILE* arch = fopen(nombreArch, "wt");
    void* elem = malloc(tamDatos);
    Iterador itL;

    if(!arch)
       return -1;

    crearIterador(&itL, pl);
    primeroDeLista(&itL, elem, tamDatos);

    while(!finLista(&itL) && impre(&arch, elem, tipoTxt))
        siguienteDeLista(&itL, elem, tamDatos);

    free(elem);
    fclose(arch);

    return 0;
}

int imprimirEnTxtComponente(FILE** pArch, void* elem, char tipoTxt)
{
    Componente* comp = (Componente*)elem;
    const char* formato = tipoTxt == 'V' ? "%d|%s|%d|%f\n" : "%4d%-8s%3d%7.0f\n";

    return fprintf(*pArch, formato, comp->cod, comp->nombreComp, comp->cantidad, comp->precio);
}

int txtABin(const char* nomArchBin, const char* nomArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nomArchBin, "wb");
    FILE* archTxt = fopen(nomArchTxt, "rt");

    if(!archBin || !archTxt)
        return -1;

    Componente comp;
    char cad[500];

    while(fgets(cad, sizeof(Componente), archTxt))
    {
        trozarCampos(&comp, cad, tipoTxt);
        fwrite(&comp, sizeof(Componente), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int trozarCampos(Componente* comp, char* cad, char tipoTxt)
{
    if(tipoTxt == 'V')
    {
        char* cursor = mi_strchr(cad, '\n');

        // Precio
        *cursor = '\0';
        cursor = mi_strrchr(cad, '|');
        sscanf(cursor + 1, "%f", &comp->precio);

        //Cantidad
        *cursor = '\0';
        cursor = mi_strrchr(cad, '|');
        sscanf(cursor + 1, "%d", &comp->cantidad);

        //Componente
        *cursor = '\0';
        cursor = mi_strrchr(cad, '|');
        strcpy(comp->nombreComp, cursor + 1);

        //Codigo
        *cursor = '\0';
        sscanf(cad, "%d", &comp->cod);
    }
    else
    {
        char* cursor = mi_strchr(cad, '\n');

        // Precio
        *cursor = '\0';
        cursor -= 7;
        sscanf(cursor, "%f", &comp->precio);

        //Cantidad
        *cursor = '\0';
        cursor -= 4;
        sscanf(cursor, "%d", &comp->cantidad);

        //Componente
        *cursor = '\0';
        cursor -= 8;
        strcpy(comp->nombreComp, cursor);

        //Codigo
        *cursor = '\0';
        sscanf(cad, "%d", &comp->cod);
    }

    return TODO_OK;
}

//int binATxt(const char* nomArchBin, const char* nomArchTxt, char tipoTxt)
//{
//
//}

int mostrarArchBinComponentes(const char*  nombreArchComp)
{
    FILE* archComp = fopen(nombreArchComp, "rb");
    Componente comp;

    if(!archComp)
        return -1;

    fread(&comp, sizeof(Componente), 1, archComp);

    while(!feof(archComp))
    {
        printf("%d %s %d %.2f\n", comp.cod, comp.nombreComp, comp.cantidad, comp.precio);

        fread(&comp, sizeof(Componente), 1, archComp);
    }

    fclose(archComp);

    return TODO_OK;
}
