#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nombre[] = "Jonathan", salida[20];
    unsigned int edad = 21;

    char nombre1[20] = "", entrada[20];
    unsigned int edad1 = 0;

    // sprintf
    sprintf(salida, "%s %u", nombre, edad); // nombre edad --> salida

    printf("%s\n", salida);

    // sscanf
    printf("\nIngrese nombre y edad, separados por un espacio: ");
    gets(entrada);

    sscanf(entrada, "%s %u", nombre1, &edad1); //entrada --> nombre1 edad1

    printf( "Has escrito: %s\n", entrada );
    printf( "Nombre: %s. Edad: %d\n", nombre1, edad1 );

    return 0;
}
