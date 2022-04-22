#include <stdio.h>
#include <stdlib.h>

#define TODO_OK  0
#define ERR_ARCH 1

#define TAM_VEC 5

int menu();
int crearVecFloat(float* vec, int cantElem);
int buscarMinimo(const float* vec, int cantElem);
float promedioVecPosPares(float* vec, int cantElem);
int generarArchTextFloats(const float* vec, const char* nameArch);
void mostrarVecInverso(float* vec, int cantElem);

int main(int argc, char* argv[])
{
    int op;
    float v[TAM_VEC] = {1, 2, 3, 0, 5};

    do
    {
        op = menu();
    }while(op < 1 || op > 4);

    while(op !=4)
    {
        switch (op)
        {
        case 1:
            printf("Minimo %f\n", v[buscarMinimo(v, TAM_VEC) - 1]);
            break;
        case 2:
            printf("Promedio de las posiciones pares: %f\n", promedioVecPosPares(v, TAM_VEC));
            break;
        case 3:
            mostrarVecInverso(v, TAM_VEC);
            break;
        case 4:
            break;
        }

        printf("\n");

        do
        {
            op = menu();
        }while(op < 0 || op > 4);
    }


//    printf("%d\n", buscarMinimo(v, TAM_VEC));
//    printf("%f", promedioVecPosPares(v, TAM_VEC));
//    generarArchTextFloats(v, argv[1]);

    return 0;
}

int menu()
{
    int op;

    printf("1- Buscar el minimo element\n"
           "2- Calcular el promedio de los valores de las posciones pares\n"
           "3- Mostrar en orden inverso\n"
           "4- Salir\n"
           "Su opcion: ");

    scanf("%d", &op);

    return op;
}

int crearVecFloat(float* vec, int cantElem)
{
    float* finVec = vec + cantElem - 1;

    while (vec <= finVec)
    {
        scanf("%f", vec);
        vec++;
    }

    return TODO_OK;
}

int buscarMinimo(const float* vec, int cantElem)
{
    int i = 0;
    float* min = (float*)vec;
    const float* finVec = vec + cantElem - 1;

    vec++;
    while (vec <= finVec)
    {
        if(*vec < *min)
            min = (float*)vec;
        vec++;
        i++;
    }

//    return (*min)/sizeof(float);
    return i;
}

float promedioVecPosPares(float* vec, int cantElem)
{
    float acumElemPares = 0;
    const float* finVec = vec + cantElem - 1;

    vec++;
    while (vec <= finVec)
    {
        acumElemPares += *vec;
        vec += 2;
    }

    return acumElemPares/cantElem;
}

int generarArchTextFloats(const float* vec, const char* nameArch)
{
    FILE* archFloat = fopen(nameArch, "wt");

    if(!archFloat)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    for(int i = 0; i < TAM_VEC; i++)
        fprintf(archFloat, "%f\n", vec[i]);

    fclose(archFloat);

    return TODO_OK;
}

void mostrarVecInverso(float* vec, int cantElem)
{
    float* finVec = vec + cantElem - 1;

    while (vec <= finVec)
    {
        printf("%f ", *finVec);
        finVec--;
    }

    printf("\n");
}
