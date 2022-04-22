#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct
{
    int vec[TAM];
    int cantElem;
}
Vector;

void crearVector(Vector* vector);
void eliminarDuplicados(Vector* vector, int elem);
void mostrarVector(const Vector* vector);

int main()
{
    Vector vec = {{3, 7, 6, 5, 3, 3, 0, 2, 3, 3}, 10};

    printf("Vector antes de eliminar duplicados: \n");
    mostrarVector(&vec);

    puts("\n");

    eliminarDuplicados(&vec, 3);

    printf("Vector despues de eliminar duplicados: \n");
    mostrarVector(&vec);
    printf("%d eliminados.\n", TAM - vec.cantElem);

    return 0;
}

void crearVector(Vector* vector)
{
    vector->cantElem = 0;
}

void eliminarDuplicados(Vector* vector, int elem)
{
    int  *pEliminador = vector->vec,
         *pCursor = vector->vec,
         *fin = vector->vec + vector->cantElem -1;

    while(pCursor <= fin)
    {
        while(*pCursor == elem)
        {
            while(pEliminador <= fin)
            {
                *pEliminador = *(pEliminador + 1);
                pEliminador++;
            }

            vector->cantElem--;
            pEliminador = pCursor;
        }

        pCursor++;
        pEliminador++;
    }
}

void mostrarVector(const Vector* vector)
{
    int i;

    for(i = 0; i < vector->cantElem; i++)
        printf("%d ", vector->vec[i]);

    printf("\n");
}
