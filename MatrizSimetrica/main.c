#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 5
#define TAM_COLUM 5

int matrizSimetrica(int m[TAM_FILA][TAM_COLUM]);

int main()
{
    int m[TAM_FILA][TAM_COLUM] = {  {1, 2, 3, 4, 4},
                                    {2, 0, 7, 4, 4},
                                    {3, 7, 1, 1, 1},
                                    {4, 4, 1, 1, 1},
                                    {4, 4, 1, 1, 1} };

    if(matrizSimetrica(m))
        printf("Es simetrica.\n");
    else
        printf("NO es simetrica.\n");

//    int i, j, cont = 0;
//
//    for(i = 0; i < 3; i++)
//    {
//        for(j = 1 + i; j <= 3; j++)
//        {
//            if(m[i][j] == m[j][i])
//                cont++;
//        }
//    }
//
//    if(cont == 6)
//        printf("Es simetrica.\n");
//    else
//        printf("NO es simetrica.\n");

    return 0;
}

int matrizSimetrica(int m[TAM_FILA][TAM_COLUM])
{
    int i, j, esSimetrica = 1;

    for(i = 0; i < TAM_FILA - 1; i++)
        for(j = 1 + i; j <= TAM_FILA - 1; j++)
            if(m[i][j] != m[j][i])
                esSimetrica = 0;

    return esSimetrica;
}
