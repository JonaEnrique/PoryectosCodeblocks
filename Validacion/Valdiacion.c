#include "Validacion.h"
#include <ctype.h>

int continuar(char* mensaje) // Antes fue booleano
{
    char respuesta;

    puts(mensaje);
    fflush(stdin);
    scanf("%c", &respuesta);
    respuesta = tolower(respuesta);

    while(respuesta != 's' && respuesta != 'n')
    {
        puts("Respuesta invallida.");
        puts("Debe ingresar s ó n: ");
        fflush(stdin);
        scanf("%c", &respuesta);
        respuesta = tolower(respuesta);
    }

    return respuesta == 's';
}
