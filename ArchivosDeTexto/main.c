#include <stdio.h>
#include <stdlib.h>

#define TODO_OK  0
#define ERR_ARCH 1

#define TAM_VEC 2

typedef struct
{
    char nYa[10];
    int dni;
    float sueldo;
}
Empleado;

int generarArchivo(char* nombreArch);

int main(int argc, char* argv[])
{
    generarArchivo(argv[1]);

    return 0;
}

int generarArchivo(char* nombreArch)
{
    FILE* archEmpleado = fopen(nombreArch, "wt");

    if(!archEmpleado)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl[TAM_VEC] = {
                        {"Jonathan", 548451, 151515},
                        {"Nahuel", 48418, 100000}
                        };

    for(int i = 0; i < TAM_VEC; i++)
        fprintf(archEmpleado, "%s|%d|%f\n", empl[i].nYa, empl[i].dni, empl[i].sueldo);

    fclose(archEmpleado);

    return TODO_OK;
}
