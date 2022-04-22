#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Cadena/Cadena.h"

/* Ver la diferencia entre un vector char y un puntero char */

void copiarHastaCaracter(char* palO, char* palD, char c);
int compPalabras(Palabra* pal1, Palabra* pal2);

int main()
{
    int contPalabras = 0;
    char texto[] = "lHola.mundo.que.tal.lHola.arbol.maiz.lHola.p";
    Palabra prPalabra, pal;
    secPal sl;

    crearSecPal(&sl, texto);

    leerPalabra(&sl, &prPalabra);
    leerPalabra(&sl, &pal);

    while(!finSecPal(&sl) || !(sl.finSec))
    {
        if(compPalabras(&prPalabra, &pal))
            contPalabras++;

        leerPalabra(&sl, &pal);
    }

    printf("Cantidad de veces que se repite la primera palabra en todo el texto: %d\n", contPalabras);

    return 0;
}

void copiarHastaCaracter(char* palO, char* palD, char c)
{
    while(*palO != c)
    {
        *palD = *palO;

        palD++;
        palO++;
    }

    *palO = '\0';
}

int compPalabras(Palabra* pal1, Palabra* pal2)
{
    char p1[20]; // -> ¿Es como pedir memoria?
    char p2[20]; // -> ¿Es como pedir memoria?
    char* cursor1 = p1;
    char* cursor2 = p2;

    copiarHastaCaracter(pal1->ini, cursor1, '.');
    copiarHastaCaracter(pal2->ini, cursor2, '.');

    while(*cursor1 == *cursor2)
    {
        cursor1++;
        cursor2++;
    }

    return *cursor1 - *cursor2;
}
