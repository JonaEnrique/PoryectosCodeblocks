#include <stdio.h>
#include <stdlib.h>

#define ERR_ARCH -1
#define TODO_OK 0

#define CANT_ALUM 10
#define CANT_ALUM_MOV 12

typedef struct
{
    int dni;
    char nYa[20];
    float sueldo;
}Alumno;

int generarArchAlumnos(const char* nombreArch);
int mostrarAlumnos(const char* nombreArch);
void mostrarMovAlumnos(Alumno* vecAlum, int cantElem);

int main(int argc, char* argv[])
{
    Alumno vecMovAlumnos[CANT_ALUM_MOV] =  {{0, "Jonathan", 90211},
                                            {0, "Jonathan", 1111},
                                            {1, "Gustavo", 7000},
                                            {2, "Tamara", 8000},
                                            {3, "Dylan", 6000},
                                            {4, "Carlos", 7000},
                                            {5, "Jorge", 5000},
                                            {6, "Pedro", 7500},
                                            {7, "Cristian",1300},
                                            {8, "Nestor", 4300},
                                            {9, "Nahuel",1600},
                                            {10, "Ariel", 1430}
                                           };
    printf("Alumnos:\n");
    generarArchAlumnos(argv[1]);
    mostrarAlumnos(argv[1]);
    printf("\nMovimientos:\n");
    mostrarMovAlumnos(vecMovAlumnos, CANT_ALUM_MOV);

    return 0;
}

int generarArchAlumnos(const char* nombreArch)
{
    FILE* archAlumnos = fopen(nombreArch, "wb");

    if(archAlumnos == NULL)
    {
        printf("Error al abrir el archivo.");
        return ERR_ARCH;
    }

    Alumno vecMovAlumnos[CANT_ALUM] =  {    {0, "Jonathan", 90211},
                                            {1, "Gustavo", 7000},
                                            {2, "Tamara", 8000},
                                            {3, "Dylan", 6000},
                                            {4, "Carlos", 7000},
                                            {5, "Jorge", 5000},
                                            {6, "Pedro", 7500},
                                            {7, "Cristian",1300},
                                            {8, "Nestor", 4300},
                                            {9, "Nahuel",1600}
                                           };
    fwrite(vecMovAlumnos, sizeof(Alumno), CANT_ALUM, archAlumnos);

    fclose(archAlumnos);

    return TODO_OK;
}

int mostrarAlumnos(const char* nombreArch)
{
    FILE* archAlumnos = fopen(nombreArch, "rb");
    Alumno alum;

    if(archAlumnos == NULL)
    {
        printf("Error al abrir el archivo.");
        return ERR_ARCH;
    }

    fread(&alum, sizeof(Alumno), 1, archAlumnos);
    while(!feof(archAlumnos))
    {
       printf("%d %s Sueldo: %.2f\n", alum.dni, alum.nYa, alum.sueldo);

       fread(&alum, sizeof(Alumno), 1, archAlumnos);
    }

    fclose(archAlumnos);

    return TODO_OK;
}

void mostrarMovAlumnos(Alumno* vecAlum, int cantElem)
{
    Alumno* fin = vecAlum + cantElem -1;

    while(vecAlum <= fin)
    {
        printf("%d %s Sueldo: %.2f\n", vecAlum->dni, vecAlum->nYa, vecAlum->sueldo);
        vecAlum++;
    }
}

int actualizarAlumnos(const char* nombreArch, Alumno* vecAlum)
{

}
