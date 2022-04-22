#include <stdio.h>
#include <stdlib.h>

#include "../Cadena/Cadena.h"

char miTolower(char c);
char* miStrcpy(char* s1, const char* s2);

int main()
{
//    char s1[12];
//    char s2[12] = "Hola mundo";
//
//    miStrcpy(s1, s2);
//
//    puts(s1);

    const char pal[] = "----                           -hOla.put, mundo-como´´esTAS   --";
    char destPal[100];

    normalizar(pal, destPal);

    printf("|%s|\n", destPal);

    return 0;
}

 char miTolower(char c)
 {
     if(c >= 'A' && c <= 'Z')
        c += 32;

     return c;
 }

 char* miStrcpy(char* s1, const char* s2)
 {
     char* auxS1 = s1;
     char* auxS2 = (char*)s2;

     while(*auxS2 != '\0')
     {
         *auxS1 = *auxS2;
         auxS1++;
         auxS2++;
     }

     *auxS1 = '\0';

     return s1;
 }
