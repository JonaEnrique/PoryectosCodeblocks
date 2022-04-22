#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_EMPL 6
#define TAM_AUMENTOS 14
#define TODO_OK 0
#define ERR_ARCH -1

typedef struct
{
    char nYa[20];
    int dni;
    float sueldo;
}Empleado;

typedef struct
{
    int dni;
    float sueldo;
}Aumento;

int generarArchivoEmpl(char* nombreArch);
int generarArchivoAumentos(char* nombreArch);
int mostrarEmpleados(char* nombreArch);
int mostrarAumentos(char* nombreArch);
int merge(char* nombreArch1, char* nombreArch2);


int main(int argc, char* argv[])
{
    generarArchivoEmpl(argv[2]);
    generarArchivoAumentos(argv[1]);

    printf("Archivo empleados: \n");
    mostrarEmpleados(argv[2]);

    printf("\nArchivo aumentos: \n");

    mostrarAumentos(argv[1]);

    printf("\nArchivo empleado despues del merge0: \n");

    merge(argv[2], argv[1]);

    mostrarEmpleados(argv[2]);


    return 0;
}

int generarArchivoEmpl(char* nombreArch)
{
    FILE* empleadoA = fopen(nombreArch, "wb");

    if(!empleadoA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl[TAM_EMPL] = {
                        {"A", 1, 500},
                        {"B", 2, 200},
                        {"C", 3, 100},
                        {"D", 4, 120},
                        {"E", 5, 250},
                        {"F", 6, 230}};
    fwrite(empl, sizeof(Empleado), TAM_EMPL, empleadoA);
    fclose(empleadoA);

    return TODO_OK;
}

int generarArchivoAumentos(char* nombreArch)
{
    FILE* archAumentos = fopen(nombreArch, "wb");

    if(!archAumentos)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Aumento aumentos[TAM_AUMENTOS] = {
                        {0, 50},
                        {0, 50},
                        {2, 50},
                        {2, 100},
                        {3, 100},
                        {4, 40},
                        {4, 50},
                        {6, 10},
                        {6, 10},
                        {6, 10},
                        {6, 10},
                        {6, 12},
                        {7, 10},
                        {7, 10}
                        };
    fwrite(aumentos, sizeof(Aumento), TAM_AUMENTOS, archAumentos);
    fclose(archAumentos);

    return TODO_OK;
}

int mostrarEmpleados(char* nombreArch)
{
    FILE* empleadoA = fopen(nombreArch, "rb");

    if(!empleadoA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl;

    fread(&empl, sizeof(Empleado), 1, empleadoA);

    while(!feof(empleadoA))
    {
        printf("%s %d %f\n", empl.nYa, empl.dni, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, empleadoA);
    }

    return TODO_OK;
}

int mostrarAumentos(char* nombreArch)
{
    FILE* archAumetos = fopen(nombreArch, "rb");

    if(!archAumetos)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Aumento empl;

    fread(&empl, sizeof(Aumento), 1, archAumetos);

    while(!feof(archAumetos))
    {
        printf("%d %f\n", empl.dni, empl.sueldo);
        fread(&empl, sizeof(Aumento), 1, archAumetos);
    }

    return TODO_OK;
}

int merge(char* nombreArch1, char* nombreArch2)
{
    Empleado emp, empNuevo;
    Aumento aument;
    int comp;
    char nomTemp[20] = "arch.temp";

    FILE* archEmpleados = fopen(nombreArch1, "rb");
    FILE* archAumentos = fopen(nombreArch2, "rb");
    FILE* archEmpleadosTemp = fopen(nomTemp, "wb");

    fread(&emp, sizeof(Empleado), 1, archEmpleados);
    fread(&aument, sizeof(Aumento), 1, archAumentos);

    while(!feof(archEmpleados) && !feof(archAumentos))
    {
        comp = emp.dni - aument.dni;

        if(comp < 0) // Termina el aumento y se escribez
        {
            fwrite(&emp, sizeof(Empleado), 1, archEmpleadosTemp);
            fread(&emp, sizeof(Empleado), 1, archEmpleados);
        }
        else if(comp == 0) // Aumento de sueldo
        {
            emp.sueldo += aument.sueldo;
            fread(&aument, sizeof(Aumento), 1, archAumentos);
        }
        else // Empleado nuevo
        {
            empNuevo.dni = aument.dni;
            empNuevo.sueldo = aument.sueldo;
            strcpy(empNuevo.nYa, "Nuevo"); // Arreglar despues

            fread(&aument, sizeof(Aumento), 1, archAumentos);
            while(aument.dni == empNuevo.dni)
            {
                empNuevo.sueldo += aument.sueldo;
                fread(&aument, sizeof(Aumento), 1, archAumentos);
            }

            fwrite(&empNuevo, sizeof(Empleado), 1, archEmpleadosTemp);
        }
    }

    while(!feof(archEmpleados))
    {
        fwrite(&emp, sizeof(Empleado), 1, archEmpleadosTemp);
        fread(&emp, sizeof(Empleado), 1, archEmpleados);
    }

    while(!feof(archAumentos))
    {
        empNuevo.dni = aument.dni;
        empNuevo.sueldo = aument.sueldo;
        strcpy(empNuevo.nYa, "Nuevo"); // Arreglar despues

        fread(&aument, sizeof(Aumento), 1, archAumentos);
        while(!feof(archAumentos) && aument.dni == empNuevo.dni)
        {
            empNuevo.sueldo += aument.sueldo;
            fread(&aument, sizeof(Aumento), 1, archAumentos);
        }

        fwrite(&empNuevo, sizeof(Empleado), 1, archEmpleadosTemp);
    }


    fclose(archEmpleados);
    fclose(archAumentos);
    fclose(archEmpleadosTemp);

    remove(nombreArch1);
    rename(nomTemp, nombreArch1);

    return TODO_OK;
}
