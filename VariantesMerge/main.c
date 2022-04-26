#include <stdio.h>
#include <stdlib.h>

#define TAM_VEC1 5
#define TAM_VEC2 5

void vec_union(int* vec1, int* vec2, int tam1, int tam2);
void vec_interseccion(int* vec1, int* vec2, int tam1, int tam2);
void vec_restaAmenosB(int* vec1, int* vec2, int tam1, int tam2);
void vec_restaBmenosA(int* vec1, int* vec2, int tam1, int tam2);
void vec_difSimetrica(int* vec1, int* vec2, int tam1, int tam2);

int main()
{
    int vec1[TAM_VEC1] = {1, 2, 4, 7, 9} , vec2[TAM_VEC2] = {0, 2, 3, 7, 10};

    printf("Union:\n");
    vec_union(vec1, vec2, TAM_VEC1, TAM_VEC2);

    printf("\nInterseccion:\n");
    vec_interseccion(vec1, vec2, TAM_VEC1, TAM_VEC2);

    printf("\nA-B:\n");
    vec_restaAmenosB(vec1, vec2, TAM_VEC1, TAM_VEC2);

    printf("\nB-A:\n");
    vec_restaBmenosA(vec1, vec2, TAM_VEC1, TAM_VEC2);

    printf("\nDiferencia simetrica:\n");
    vec_difSimetrica(vec1, vec2, TAM_VEC1, TAM_VEC2);

    return 0;
}

void vec_union(int* vec1, int* vec2, int tam1, int tam2)
{
    int *fin1 = vec1 + tam1 -1, *fin2 = vec2 + tam2 -1;
    int cmp;

    while(vec1 <= fin1 && vec2 <= fin2)
    {
        cmp = *vec1 - *vec2;

        if(cmp == 0) // Si son iguales va a ir a parar uno solo
        {
            printf("%d ", *vec1);
            vec1++;
            vec2++;
        }
        else if(cmp < 0)
        {
            printf("%d ", *vec1);
            vec1++;
        }
        else
        {
            printf("%d ", *vec2);
            vec2++;
        }
    }

    if(vec1 <= fin1)
    {
        printf("%d ", *vec1);
        vec1++;
    }

    if(vec2 <= fin2)
    {
        printf("%d ", *vec2);
        vec2++;
    }
}

void vec_interseccion(int* vec1, int* vec2, int tam1, int tam2)
{
    int *fin1 = vec1 + tam1 -1, *fin2 = vec2 + tam2 -1;
    int cmp;

    while(vec1 <= fin1 && vec2 <= fin2)
    {
        cmp = *vec1 - *vec2;

        if(cmp == 0) // Si son iguales va a ir a parar uno solo
        {
            printf("%d ", *vec1);
            vec1++;
            vec2++;
        }
        else if(cmp < 0)
            vec1++;
        else
            vec2++;
    }
}

void vec_restaAmenosB(int* vec1, int* vec2, int tam1, int tam2)
{
    int *fin1 = vec1 + tam1 -1, *fin2 = vec2 + tam2 -1;
    int cmp;

    while(vec1 <= fin1 && vec2 <= fin2)
    {
        cmp = *vec1 - *vec2;

        if(cmp == 0)
        {
            vec1++;
            vec2++;
        }
        else if(cmp < 0)
        {
            printf("%d ", *vec1);
            vec1++;
        }
        else
        {
            vec2++;
        }
    }

    if(vec1 <= fin1)
    {
        printf("%d ", *vec1);
        vec1++;
    }
}

void vec_restaBmenosA(int* vec1, int* vec2, int tam1, int tam2)
{
    int *fin1 = vec1 + tam1 -1, *fin2 = vec2 + tam2 -1;
    int cmp;

    while(vec1 <= fin1 && vec2 <= fin2)
    {
        cmp = *vec1 - *vec2;

        if(cmp == 0) // Si son iguales va a ir a parar uno solo
        {
            vec1++;
            vec2++;
        }
        else if(cmp < 0)
        {
            vec1++;
        }
        else
        {
            printf("%d ", *vec2);
            vec2++;
        }
    }

    if(vec2 <= fin2)
    {
        printf("%d ", *vec2);
        vec2++;
    }
}

void vec_difSimetrica(int* vec1, int* vec2, int tam1, int tam2)
{
    int *fin1 = vec1 + tam1 -1, *fin2 = vec2 + tam2 -1;
    int cmp;

    while(vec1 <= fin1 && vec2 <= fin2)
    {
        cmp = *vec1 - *vec2;

        if(cmp == 0)
        {
            vec1++;
            vec2++;
        }
        else if(cmp < 0)
        {
            printf("%d ", *vec1);
            vec1++;
        }
        else
        {
            printf("%d ", *vec2);
            vec2++;
        }
    }

    if(vec1 <= fin1)
    {
        printf("%d ", *vec1);
        vec1++;
    }

    if(vec2 <= fin2)
    {
        printf("%d ", *vec2);
        vec2++;
    }
}

