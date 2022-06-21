#include "miString.h"

char *mi_strchr(char *s, int c)
{
    while(*s && *s != c)
        s++;

    if(!*s)
        return 0;

    return s;
}

char *mi_strrchr(char *s, int c)
{
    char* inicioCad = s;

    while(*s) // Llevamos al final al puntero
        s++;

    while(s >= inicioCad && *s != c)
        s--;

    if(!*s)
        return 0;

    return s;
}

size_t mi_strlen(const char *s)
{
    size_t cantCaracters = 0;

    while(*s)
    {
        s++;
        cantCaracters++;
    }

    return cantCaracters;
}

char *mi_strcat(char* s1, char *s2)
{
    char* dest = s1;

    while(*dest)
        dest++;

    while((*dest = *s2) != '\0')
    {
        s2++;
        dest++;
    }

    return s1;
}

char *mi_strcatV2(char* s1, char *s2)
{
    char* dest = s1;

    while(*dest)
        dest++;

    while(*s2)
    {
        *dest = *s2;

        s2++;
        dest++;
    }

    *dest = '\0';

    return s1;
}

char *mi_strcpy(char *s1, const char *s2)
{
    char* inicioS1 = s1;

    while((*s1++ = *s2) != '\0')
        s2++;

    return inicioS1;
}

int mi_strcmp(const char *s1, const char *s2)
{
    while(*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }

    return *s1 - *s2;
}

int mi_stricmp(const char *s1, const char *s2)
{
    while(*s1 && (mi_toupper(*s1) == mi_toupper(*s2))) // Importante los parentesis
    {
        s1++;
        s2++;
    }

    return (mi_toupper(*s1)) - (mi_toupper(*s2)); // Importante los parentesis
}

int mi_strncmp(const char *s1, const char *s2, size_t n)
{
    if(n == 0)
        return 0;

    while(*s1 && (mi_toupper(*s1) == mi_toupper(*s2)) && --n) // Importante los parentesis // --n primero resta -> va a hacer uno menos y está bien
    {
        s1++;
        s2++;
    }

    return (mi_toupper(*s1)) - (mi_toupper(*s2)); // Importante los parentesis
}

//char *mi_strstr(const char *s1, const char *s2)
//{
//    const char* inicioS1 = s1;
//    const char* inicioSubCadS2 = 0;
//
//    while(*s2)
//    {
//        if(*s1 && *s1 == *s2)
//            inicioSubCadS2 = s2;
//
//        while(*s1 && *s1 == *s2)
//        {
//            s1++;
//            s2++;
//        }
//
//        if(!*s1)
//            return (char*)inicioSubCadS2;
//
//        if(*s1 != *s2)
//            s1 = inicioS1;
//
//        if(*s2)
//            s2++;
//    }
//
//    return 0;
//}

char *mi_strstr(const char *s1, const char *s2)
{
    size_t tam = mi_strlen(s2);

    while(*s1 && mi_strncmp(s1, s2, tam)) // Cuano mi_strncmp de 0, es porque existe la subcadena, si s1 llega a 0 no está la subcadena
        s1++;

    return *s1 ? ((char*)s1) : 0;
}





