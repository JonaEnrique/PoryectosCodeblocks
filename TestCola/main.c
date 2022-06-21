#include <stdio.h>
#include <stdlib.h>

#define TDA_COLA_IMPL_DINAMICA
#include "../TDACola/TDACola.h"

#define TAM_VEC 10

typedef struct
{
    char nombre[10];
    int edad;
    float sueldo;
}Persona;

void crearArchivoPersona(const char* nombreArch, Persona* vecPersona);
void mostrarArchivoPersona(const char* nombreArch);

int main()
{
    Persona vec[TAM_VEC] = {{"Jonathan", 21, 150000},
                            {"Pedro", 22, 4884},
                            {"Juan", 23, 545},
                            {"Victor", 24, 4878},
                            {"Ariel", 25, 4984},
                            {"Nahuel", 26, 950},
                            {"Luciano", 27, 488},
                            {"Franco", 28, 7445},
                            {"Rodrigo", 29, 488},
                            {"Alejo", 30, 4884}  };
    Persona per;
    Cola colaPersonas;

    crearArchivoPersona("Persona.dat", vec);
    mostrarArchivoPersona("Persona.dat");

    FILE* archPersona = fopen("Persona.dat", "rb");

    if(!archPersona)
        printf("No se pudo abrir el archivo.\n");

    crearCola(&colaPersonas);

    fread(&per, sizeof(Persona), 1, archPersona);
    while(!feof(archPersona))
    {
        encolar(&colaPersonas, &per, sizeof(Persona));

        fread(&per, sizeof(Persona), 1, archPersona);
    }

    fclose(archPersona);

    archPersona = fopen("Persona.dat", "wb");

    if(!archPersona)
        printf("No se pudo abrir el archivo.\n");

    while(desencolar(&colaPersonas, &per, sizeof(Persona)))
    {
        per.sueldo = 1;

        fwrite(&per, sizeof(Persona), 1, archPersona);
    }

    fclose(archPersona);

    printf("\n");
    mostrarArchivoPersona("Persona.dat");

    return 0;
}

void crearArchivoPersona(const char* nombreArch, Persona* vecPersona)
{
    FILE* archPersona = fopen(nombreArch, "wb");

    if(!archPersona)
        printf("No se pudo abrir el archivo.\n");

    Persona* finVecPersona = vecPersona + TAM_VEC - 1;

    while(vecPersona != finVecPersona)
    {
        fwrite(vecPersona, sizeof(Persona), 1, archPersona);
        vecPersona++;
    }

    fclose(archPersona);
}

void mostrarArchivoPersona(const char* nombreArch)
{
    FILE* archPersona = fopen(nombreArch, "rb");

    if(!archPersona)
        printf("No se pudo abrir el archivo.\n");

    Persona per;

    fread(&per, sizeof(Persona), 1, archPersona);
    while(!feof(archPersona))
    {
        printf("%8s %4d %8.2f\n", per.nombre, per.edad, per.sueldo);
        fread(&per, sizeof(Persona), 1, archPersona);
    }

    fclose(archPersona);
}

/* Cargar archivo Personas.bin en una cola y actualizar sueldos */
/* Txt */
