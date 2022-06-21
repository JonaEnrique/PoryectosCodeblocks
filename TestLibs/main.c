#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define esNumero(X) ((X) >= '0' && (X) <= '9') ? 1:0
//#define esSigno(X) ((X) == '+' || (X) == '-') ? 1:0

#include "../Bibliotecas/miString/miString.h"

int esNumero(char l);
int esSigno(char l);
int miAtoi(const char* numPtr);

int main()
{
//    char* cadenas[] = { "1Hola_",
//                        "15641H1ola",
//                        "1l1_gdfg0",
//                        " 12lsadsa",
//                        "_13lsadsa",
//                        " 1235_8982",
//                        "*15j",
//                        "+18",
//                        "-18",
//                        "++18",
//                        "--18",
//                        " +21",
//                        " + 21",
//                        "+a",
//                        "\s -105"
//                        };
//
//    for(int i = 0; i < 15; i++)
//        printf("Cadena: |%10s|  Atoi original: %10d  Mi atoi: %10d\n",  cadenas[i], atoi(cadenas[i]), miAtoi(cadenas[i]));

    char cad1[500] = "Hola Mundo";
    char cad2[] = "Hola";

    printf("|%s|\n", mi_strstr(cad1, cad2));

//    char condicion[20];
//    int cmp = mi_strncmp(cad1, cad2, 3);
//
//    if(cmp > 0)
//        mi_strcpy(condicion, "Cad1");
//
//    if(cmp == 0)
//        mi_strcpy(condicion, "Iguales");
//
//    if(cmp < 0)
//        mi_strcpy(condicion, "Cad2");
//
//    printf("\n Comparacion: %s \n", condicion);

//    char cad1[500] = "Hola";
//    char cad2[] = " Mundo.";
//    char cad3[500] = "Hola";
//    char cad4[] = " Mundo.";
//
//    printf("|%s|\n", mi_strcat(cad1, cad2));
//    printf("|%s|\n", mi_strcatV2(cad3, cad4));

    //mi_strcpy(cad1, cad2);

    //printf("String: |%s| Cantidad de caranteres: %d\n", cad1, mi_strlen(cad1));

//    char condicion[20];
//
//    if(mi_stricmp(cad1, cad2)>0)
//        mi_strcpy(condicion, "Cad1");
//
//    if(mi_stricmp(cad1, cad2) == 0)
//        mi_strcpy(condicion, "Iguales");
//
//    if(mi_stricmp(cad1, cad2) < 0)
//        mi_strcpy(condicion, "Cad2");
//
//    printf("\n Comparacion: %s \n", condicion);

    return 0;
}

int esNumero(char l)
{
    return (l >= '0' && l <= '9') ? 1:0;
}

int esSigno(char l)
{
    return (l == '+' || l == '-') ? 1:0;
}

int miAtoi(const char* numPtr)
{
    int num = 0, signo = 1, i = 0;
    char* cursor = (char*)numPtr;

    /* Pasamos los espacios */
    while(*cursor == ' ')
        cursor++;

    /*signo y otro filtro*/
    if(esSigno(*cursor))
    {
        if(!esNumero(*(cursor + 1)))
            return 0;

        signo = (*cursor - 44) * -1;
        cursor++;
    }

    if(!esNumero(*cursor))
        return 0;

    while(esNumero(*cursor))
        cursor++;

    cursor--;

    while(esNumero(*cursor))
    {
        num += (*cursor - '0') * pow(10, i);

        i++;
        cursor--;
    }

    return num*signo;
}
