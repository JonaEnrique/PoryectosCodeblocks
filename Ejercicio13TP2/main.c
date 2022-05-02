#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK     0

#define MAXIMA_LONG_CADENA 200
#define TAM_VEC 4
#define TAM_VEC_EMPL 18
#define TAM_VEC_ESTUDIANTE 18

#define ERR_ARCH 9

typedef struct
{
    int dni;
    char apellido[20];
    char nombre[20];
    float sueldo;
}Empleado;

typedef struct
{
    int dni;
    char apellido[20];
    char nombre[20];
    float promedio;
}Estudiantes;

int ordenamientoStrings(char vec[][MAXIMA_LONG_CADENA], int cantElem);
int intercambiar(char* palabra1, char* palabra2);
int mostrarVecDeStrings(char vecDeStrigns[][MAXIMA_LONG_CADENA], int cantElem);

int ordenamientoEmpleados(Empleado* vecEmpleados, int cantEmpl);
void intercambiarEmpleados(Empleado* empl1, Empleado* empl2);
//int mostrarEmpleados(Empleado* empl);

int generarArchivoEmpl(char* nombreArch);
int generarArchivoEst(char* nombreArch);

int actualziarSueldos(const char* nombreArchEmpl, const char* nombreArchEst);

void mostrarEmpleados(const Empleado* emp);
void mostrarEstudiantes(const Estudiantes* est);
int leerYMostrarArchivoEst(char* nombreArchivo);
int leerYMostrarArchivoEmp(char* nombreArchivo);


int main()
{
    generarArchivoEmpl("Empleados.dat");
    generarArchivoEst("Estudiantes.dat");

    printf("\nAntes de actualizar: \n\n");
    printf("Empleados: \n");
    leerYMostrarArchivoEmp("Empleados.dat");
    printf("Estudiantes: \n");
    leerYMostrarArchivoEst("Estudiantes.dat");

    actualziarSueldos("Empleados.dat", "Estudiantes.dat");

    printf("\nDespues de actualizar: \n\n");
    printf("Empleados: \n");
    leerYMostrarArchivoEmp("Empleados.dat");
    printf("Estudiantes: \n");
    leerYMostrarArchivoEst("Estudiantes.dat");

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

    Empleado vecEmp[TAM_VEC_EMPL] =  {  {43563982, "Gomez", "Enriqueta", 15152},
                                        {41355712, "Octavio", "Moya", 1441},
                                        {43936939, "Gladys", "Juarez", 245},
                                        {40790664, "Jose", "Ramos", 2514},
                                        {42936477, "Alexandre", "Acosta", 2514},
                                        {42824401, "Andres", "Antunez", 2514},
                                        {42732871, "Olivia", "Revilla", 2514},
                                        {41342093, "Nadia", "Prados", 2514},
                                        {40388160, "Dylan", "Trigo", 2514},
                                        {40248836, "Angela", "Vallejo", 2514},
                                        {42440260, "Basilio", "Casas", 2514},
                                        {43619246, "Mario", "Pinilla", 2514},
                                        {40590586, "Nicole", "Garces", 2514},
                                        {43089707, "Jaume", "Olmos", 2514},
                                        {41523372, "Bryan", "Valiente", 2514},
                                        {40174314, "Jan", "Duque", 2514},
                                        {43969938, "Nekane", "Guerrero", 2514},
                                        {42043485, "Clara", "Crespo", 2514}
                                        };

    ordenamientoEmpleados(vecEmp, TAM_VEC_EMPL);
    fwrite(vecEmp, sizeof(Empleado), TAM_VEC_EMPL, empleadoA);
    fclose(empleadoA);

    return TODO_OK;
}

int generarArchivoEst(char* nombreArch)
{
    FILE* estudianteA = fopen(nombreArch, "wb");

    if(!estudianteA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }


    Estudiantes vecEst[TAM_VEC_ESTUDIANTE] =  {   {43563982, "Gomez", "Enriqueta", 7},
                                            {41355712, "Octavio", "Moya", 7.5},
                                            {43936939, "Gladys", "Juarez", 6},
                                            {40790664, "Jose", "Ramos", 5.4},
                                            {42936477, "Alexandre", "Acosta", 3},
                                            {42824401, "Andres", "Antunez", 8},
                                            {42732871, "Olivia", "Revilla", 10},
                                            {41342093, "Nadia", "Prados", 9.4},
                                            {40388160, "Dylan", "Trigo", 3.6},
                                            {40248836, "Angela", "Vallejo", 6.7},
                                            {42440260, "Basilio", "Casas", 2},
                                            {43619246, "Mario", "Pinilla", 1},
                                            {40590586, "Nicole", "Garces", 10},
                                            {43089707, "Jaume", "Olmos", 7.9},
                                            {41523372, "Bryan", "Valiente", 8},
                                            {40174314, "Jan", "Duque", 9},
                                            {43969938, "Nekane", "Guerrero", 7},
                                            {42043485, "Clara", "Crespo", 10}
                                        };

    fwrite(vecEst, sizeof(Estudiantes), TAM_VEC_ESTUDIANTE, estudianteA);
    fclose(estudianteA);

    return TODO_OK;
}

int ordenamientoStrings(char vec[][MAXIMA_LONG_CADENA], int cantElem)
{
    int i = 1, j;
    int huboIntercambios = 1;

    while(huboIntercambios && i < cantElem)
    {
        huboIntercambios = 0;

        for(j = 0; j < cantElem - i; j++)
        {
            if(strcmp(vec[j], vec[j +1]) > 0)
            {
                intercambiar(vec[j], vec[j+1]);
                huboIntercambios = 1;
            }
        }

        i++;
    }

    return TODO_OK;
}

int intercambiar(char* palabra1, char* palabra2)
{
    char aux[20];

    strcpy(aux, palabra1);
    strcpy(palabra1, palabra2);
    strcpy(palabra2, aux);

    return TODO_OK;
}

int mostrarVecDeStrings(char vecDeStrigns[][MAXIMA_LONG_CADENA], int cantElem)
{
    int i;

    for(i = 0; i < cantElem; i++)
        printf("%s\n", vecDeStrigns[i]);

    return TODO_OK;
}

int ordenamientoEmpleados(Empleado* vecEmpleados, int cantEmpl)
{
    int i = 1, j, cmp;
    int huboIntercambios = 1;

    while(huboIntercambios && i < cantEmpl)
    {
        huboIntercambios = 0;

        for(j = 0; j < cantEmpl - i; j++)
        {
            cmp = strcmp((vecEmpleados + j)->apellido, (vecEmpleados + j + 1)->apellido);

            if(cmp !=0)
            {
                if(cmp > 0)
                {
                    intercambiarEmpleados(vecEmpleados + j, vecEmpleados + j + 1);
                    huboIntercambios = 1;
                }
            }
            else
            {
                cmp = strcmp((vecEmpleados + j)->nombre, (vecEmpleados + j + 1)->nombre);

                if(cmp != 0)
                {
                    if(cmp > 0)
                    {
                        intercambiarEmpleados(vecEmpleados + j, vecEmpleados + j + 1);
                        huboIntercambios = 1;
                    }
                }
                else
                {
                    cmp = (vecEmpleados + j)->dni - (vecEmpleados + j + 1)->dni;

                    if(cmp != 0)
                    {
                        if(cmp > 0)
                        {
                            intercambiarEmpleados(vecEmpleados + j, vecEmpleados + j + 1);
                            huboIntercambios = 1;
                        }
                    }
                }
            }

//            if(((vecEmpleados + j)->dni - (vecEmpleados + j + 1)->dni) > 0)
//                if(strcmp((vecEmpleados + j)->nombre, (vecEmpleados + j + 1)->nombre) > 0)
//                    if(strcmp((vecEmpleados + j)->apellido, (vecEmpleados + j + 1)->apellido) > 0)
//                    {
//                        intercambiarEmpleados(vecEmpleados + j, vecEmpleados + j + 1);
//                        huboIntercambios = 1;
//                    }

//            cmp = strcmp(vecEmpleados->nombre, (vecEmpleados + 1)->nombre);
//            cmp = (vecEmpleados + j)->dni - (vecEmpleados + j + 1)->dni;
//            if( cmp > 0)
//            {
//                intercambiarEmpleados(vecEmpleados + j, vecEmpleados + j + 1);
//                huboIntercambios = 1;
//            }
        }

        i++;
    }

    return TODO_OK;
}

void intercambiarEmpleados(Empleado* empl1, Empleado* empl2)
{
    Empleado auxEmpl;

    auxEmpl = *empl1;
    *empl1 = *empl2;
    *empl2 = auxEmpl;

//    auxEmpl.dni = empl1->dni;
//    strcpy(auxEmpl->apellido, empl1->apellido);
//    strcpy(auxEmpl->nombre, empl2->nombre);
//    auxEmpl->sueldo = empl1->sueldo;
//
//    empl1->dni = empl2->dni;
//    strcpy(empl1->apellido, empl2->apellido);
//    strcpy(empl1->nombre, empl2->nombre);
//    empl1->sueldo = empl2->sueldo;
//
//    empl2->dni = auxEmpl->dni;
//    strcpy(empl2->apellido, auxEmpl->apellido);
//    strcpy(empl2->nombre, auxEmpl->nombre);
//    empl2->sueldo = auxEmpl->sueldo;
}

//int mostrarEmpleados(Empleado* empl)
//{
//    Empleado* finEmpl = empl + TAM_VEC_EMPL;
//
//    while(empl < finEmpl)
//    {
//        printf("%10s %10s %d\n", empl->apellido, empl->nombre, empl->dni);
//        empl++;
//    }
//
//    return TODO_OK;
//}

void mostrarEmpleados(const Empleado* emp)
{
    if(!emp)
    {
        printf("DNI      APELLIDO   NOMBRE     SUELDO\n");
        printf("========  =========  =========  =======\n");
        return;
    }

    printf("%08d %-10s %-10s %9.2f\n",
               emp->dni,
               emp->apellido,
               emp->nombre,
               emp->sueldo);
}

void mostrarEstudiantes(const Estudiantes* est)
{
    if(!est)
    {
        printf("DNI      APELLIDO   NOMBRE     PROMEDIO\n");
        printf("========  =========  =========  =======\n");
        return;
    }

    printf("%08d %-10s %-10s %.2f\n",
               est->dni,
               est->apellido,
               est->nombre,
               est->promedio);
}

int leerYMostrarArchivoEst(char* nombreArchivo)
{
    Estudiantes est;
    FILE* fp = fopen(nombreArchivo, "rb");

    if(!fp)
    {
        puts("Error de archivo");
        return ERR_ARCH;
    }

    mostrarEstudiantes(NULL);

    fread(&est, sizeof(Estudiantes), 1, fp);
    while(!feof(fp))
    {
        mostrarEstudiantes(&est);
        fread(&est, sizeof(Estudiantes), 1, fp);
    }

    fclose(fp);

    return TODO_OK;
}

int leerYMostrarArchivoEmp(char* nombreArchivo)
{
    Empleado emp;
    FILE* fp = fopen(nombreArchivo, "rb");

    if(!fp)
    {
        puts("Error de archivo");
        return ERR_ARCH;
    }

    mostrarEmpleados(NULL);

    fread(&emp, sizeof(Empleado), 1, fp);
    while(!feof(fp))
    {
        mostrarEmpleados(&emp);
        fread(&emp, sizeof(Empleado), 1, fp);
    }

    fclose(fp);

    return TODO_OK;
}

int actualziarSueldos(const char* nombreArchEmpl, const char* nombreArchEst)
{
    FILE* archEmpl = fopen(nombreArchEmpl,"r+b");
    FILE* archEst = fopen(nombreArchEst,"rb");

    if(!archEmpl || !archEst)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl;
    Estudiantes est;

    fread(&empl, sizeof(Empleado), 1, archEmpl);
    fread(&est, sizeof(Estudiantes), 1, archEst);
    while( !feof(archEmpl) && !feof(archEst))
    {
        if(est.promedio >= 7)
        {
            empl.sueldo += (empl.sueldo * 0.0728);

            fseek(archEmpl, -1*(long)sizeof(Empleado), SEEK_CUR);
            fwrite(&empl, sizeof(Empleado), 1, archEmpl);
            fseek(archEmpl, 0L, SEEK_CUR);
        }

        fread(&empl, sizeof(Empleado), 1, archEmpl);
        fread(&est, sizeof(Estudiantes), 1, archEst);
    }

    fclose(archEmpl);
    fclose(archEst);

    return TODO_OK;
}
