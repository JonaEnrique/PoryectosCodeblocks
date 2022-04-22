#include <stdio.h>
#include <stdlib.h>

#include "../Vector/Vector.h"

int main()
{
    Vector vector;

    crearVector(&vector);

    if(insertarEnVectorAlFinal(&vector, 78))
        printf("Se insertor el valor 78 ene le vector\n");
    else
        printf("No se pudo insertar el valor 78 en el vector\n");

    if(insertarEnVectorAlFinal(&vector, 100))
        printf("Se insertor el valor 100 ene le vector\n");
    else
        printf("No se pudo insertar el valor 100 en el vector\n");

    if(insertarEnVectorAlFinal(&vector, 200))
        printf("Se insertor el valor 200 ene le vector\n");
    else
        printf("No se pudo insertar el valor 200 en el vector\n");

    mostrarVector(&vector);

    if(eliminarDeVectorOrdPorValor(&vector, 100))
        printf("Se elimino el valor 100 del vector\n");
    else
        printf("No se pudo eliminar el valor 100 del vector\n");

    mostrarVector(&vector);

    return 0;
}
