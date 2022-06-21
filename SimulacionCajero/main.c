#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TDA_COLA_IMPL_ESTATICA
#include "../TDACola/TDACola.h"

#define TAM_VEC 10

void cargarVecEnCola(int* vec, Cola* filaDelCajero);
void cargarVecEnColaGen(void* vec, size_t tamElem, Cola* pc);

int main()
{
//    int enCajero, desencolado, encolado, cantColaVacia = 5, llegoPersona,minutos = 0;
//    int vec[TAM_VEC] = {1, 2, 3, 4, 5, 6 ,7 ,8 ,9 ,10};
//    int cajero[3] = {1, 3, 5};
//    int fila[3] = {1, 5, 9};
//    Cola filaDelCajero;
//
//    crearCola(&filaDelCajero);// IMPORTANTE
//
//    cargarVecEnCola(vec, &filaDelCajero);
//
//    srand(time(NULL));
//
////    printf("%d:\n", minutos);
////    desencolar(&filaDelCajero, &desencolado, sizeof(int));
////    enCajero = cajero[rand() % 3];
////    printf(" Persona numero %d se encuentra en cajero. (%d minutos)\n", desencolado, enCajero);
////
////    llegoPersona = fila[rand() % 3];
//
////    minutos++;
//
//    enCajero = 0;
//    llegoPersona = 0;
//    int band = 0;
//
//    while(cantColaVacia)
//    {
//        minutos < 10 ? printf("00:0%d\n", minutos) : printf("00:%d\n", minutos);
//        if(enCajero == 0)
//        {
//            if(band == 1)
//                printf("  Persona numero %d se fue del cajero.\n", desencolado);
//
//            desencolar(&filaDelCajero, &desencolado, sizeof(int));
//            enCajero = cajero[rand() % 3];
//
//            printf("  Persona numero %d se encuentra en cajero. (%d minutos)\n", desencolado, enCajero);
//        }
//
//        if(llegoPersona == 0)
//        {
//            encolado = rand () % (1000-11+1) + 11;
//            printf("  Persona numero %d entro a la fila.\n", encolado);
//
//            encolar(&filaDelCajero, &encolado, sizeof(int));
//            llegoPersona = fila[rand() % 3];
//        }
//
//        llegoPersona--;
//        enCajero--;
//
//        minutos++;
//
//        if(colaVacia(&filaDelCajero))
//            cantColaVacia--;
//
//        band = 1;
//    }
//
//
    int vec[TAM_VEC] = {1, 2, 3, 4, 5, 6 ,7 ,8 ,9 ,10};
    Cola pruebaCola;
    int elem;

    crearCola(&pruebaCola);

    cargarVecEnColaGen(vec, sizeof(int), &pruebaCola);

    while(desencolar(&pruebaCola, &elem, sizeof(int)))
    {
        printf("%d\n", elem);
    }

    return 0;
}

void cargarVecEnCola(int* vec, Cola* pc)
{
    for(int i = 0; i < TAM_VEC; i++)
    {
        if(!colaLlena(pc, sizeof(int)))
            encolar(pc, &vec[i], sizeof(int));
    }

}

void cargarVecEnColaGen(void* vec, size_t tamElem, Cola* pc)
{
    void* fin = vec + ((TAM_VEC - 1)*tamElem);
    void* i;

    for(i = vec; i <= fin; i += tamElem)
    {
        if(!colaLlena(pc, tamElem))
            encolar(pc, i, tamElem);
    }

}

// Merge de tres archivos
