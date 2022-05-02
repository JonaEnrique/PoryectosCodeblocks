#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../OrdenamientoGenerico/Ordenamiento.h"

#define TAM_VEC_EMPL 18

typedef struct
{
    int dni;
    char apellido[20];
    char nombre[20];
    float sueldo;
}Empleado;

int cmpInt(const void* a, const void* b);
int cmpEmpleados(const void* a, const void* b);
void mostrarEmpleados(const Empleado* emp);

int main()
{
    //crear vector desordenado para probar
    int vector[10] = {8, 10, 2, 3, 6, 7, 4, 9, 5, 1};

    ordenarGenSeleccion(vector, 10, sizeof(int), cmpInt);

    for(int i = 0; i < 10; i++)
        printf("%d ", vector[i]);

    puts("");

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
    Empleado* cursorVecEmpl;
    Empleado* fin = vecEmp + TAM_VEC_EMPL - 1;

    ordenarGenSeleccion(vecEmp, TAM_VEC_EMPL, sizeof(Empleado), cmpEmpleados);

    mostrarEmpleados(NULL);
    for(cursorVecEmpl = vecEmp; cursorVecEmpl <= fin;  cursorVecEmpl++)
        mostrarEmpleados(cursorVecEmpl);

    return 0;
}

int cmpInt(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int cmpEmpleados(const void* a, const void* b)
{
    int cmpDNI =((Empleado*)a)->dni - ((Empleado*)b)->dni,
        cmpAPELLIDO = strcmp(((Empleado*)a)->apellido, ((Empleado*)b)->apellido),
        cmpNOMBRE = strcmp(((Empleado*)a)->nombre, ((Empleado*)b)->nombre);

    if(cmpAPELLIDO != 0)
        return cmpAPELLIDO;

    if(cmpNOMBRE != 0)
        return cmpNOMBRE;

    if(cmpDNI != 0)
        return cmpDNI;

    return 0;
}

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
