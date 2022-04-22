#include "Cadena.h"

void normalizar(const char* cOrig, char* cDest)
{
    Palabra pal;
    secPal sl, se;

    /*Podria analizar si pudo crear la secuencia*/
    crearSecPal(&sl, cOrig); // Cursor para palabra original
    crearSecPal(&se, cDest); // Cursor para palabra de destino

    leerPalabra(&sl, &pal); // Leo palabra de la cadena original desde el cursor que apunta a la caden orginal

    while(!finSecPal(&sl) || !(sl.finSec)) // Verficamos que el cursor no este en el fin de linea, pero lo tenemos que incluir porque sino no nos escribe la ult pal, por eso 2da condi
    {
        escribirPal(&se, &pal); // Escribimos la palabra en la cadena de destino
        escribirCaracter(&se, ' '); // Ponemos el espacio

        leerPalabra(&sl, &pal); // Vuelvo a leer
    }
    reposicionarSecPal(&se, -1); // Corremos el cursor de destino uno antes porque se quedo con un espacio y queremos pisar eso
    escribirCaracter(&se, '\0'); // Ponemos barra 0  en el destino

    rebobinarSecPal(&se); //Rebobinamos, hace FALSO tambien

    /*Formateamos la palabra destino*/
    leerPalabra(&se, &pal);
    while(!finSecPal(&se) || !(se.finSec))
    {
        formatearPMayRMin(&pal);

        leerPalabra(&se, &pal); // Vuelvo a leer
    }
}

void leerPalabra(secPal* sl, Palabra* pal)
{
    /*Nos movemos hasta encontrar una letra*/
    while((*sl->cur != '\0') && (!esLetra(*sl->cur)))
        sl->cur++;

    /*Verificamos que no haya sido fin de linea (No haya terminado por la primera condicion) */
    if(*sl->cur == '\0')
    {
        sl->finSec = VERDADERO; // Corta el while cuando salga de esta funcion
        return;
    }

    /*Colocamos el cursor en el incio de la palabra*/
    pal->ini = sl->cur;

    /*Nos movemos mientras siga siendo letra con el fin de buscar el final de la plalabra*/
    while((*sl->cur != '\0') && (esLetra(*sl->cur)))
        sl->cur++;

    /*Colocamos el cursor en el fin de la palabra*/
    pal->fin = sl->cur-1; // Es -1 porque el cursor quedo parado donde no encontro una letra o donde encontro el fin de linea
    /* Si es que encontro el fin de linea, hay que darle una se�al porque sino no es escribe la palabra porque no entra al while*/
}

void crearSecPal(secPal* sl, const char* cOrig)
{
    sl->cur = (char*)cOrig;
    sl->inicad = (char*)cOrig;
    sl->finSec = FALSO; // ?
}

void escribirPal(secPal* se, const Palabra* pal)
{
    char* cursor = pal->ini;

    while(cursor <= pal->fin)
    {
        *se->cur = *cursor;

        cursor++;
        (se->cur)++;
    }

    /* Dejamos que el cursor quede una posicion despues de la ultima letra de la parada (tal cual como salio del while)
       asi queda en condicion para poner alguna otra cosa*/
}

void escribirCaracter(secPal* se, char caracter)
{
    *se->cur = caracter; //  la -> tiene mayor precedencia que casi todos los operadores
    se->cur++;
}

void reposicionarSecPal(secPal* se, int mov)
{
    se->cur += mov;
}

void rebobinarSecPal(secPal* se)
{
    se->cur = se->inicad;
}

void formatearPMayRMin(Palabra* pal)
{
    char* cursor = pal->ini;

    *cursor = toupper(*cursor);
    cursor++;

    while(cursor <= pal->fin)
    {
        if(esLetra(*cursor))
            *cursor = tolower(*cursor);
        cursor++;
    }
}

booleano finSecPal(const secPal* sl)
{
    return *sl->cur == '\0' ? VERDADERO:FALSO;
}

/* Hacer funciones de string por caracter de forma clasica y por estas funcioens*/
