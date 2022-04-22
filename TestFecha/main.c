#include <stdio.h>
#include <stdlib.h>
#include "../FechaLib/FechaLib.h"

#include <locale.h>
#include <windows.h>

#include "../Validacion/Validacion.h"

int main()
{
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    Fecha f = {1, 1, 1601};
    Fecha f1 = {7, 4, 2022};

    printf("Dias ya pasados del año 2001: %d\n", diaDelAnio(&f));
    printf("Dias ya pasados del año 2022: %d\n", diaDelAnio(&f1));
    printf("Dias entre los años: %d\n", sumaDiasEntreAnios(f.anio, f1.anio));

    printf("Diferencia entre las dos fechas: %d\n", diferenciaDeDiasEntreFechasN(&f, &f1));

//    Fecha fecha;
//
//    do
//    {
//        printf("Ingrese una fecha (dd/mm/aaaa): ");
//        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio );
//
//        if(esFechaValida(&fecha))
//            printf("La fecha es valida\n");
//        else
//            printf("La fecha NO es valida\n");
//    }
//    while(continuar("Desea ingresar otra fecha? (s/n): "));

//    Fecha f1 = {1/2/1601}, f2 = {7/4/2022}, resultado;
//
//    resultado = sumarFechas(&f1, &f2);
//
//    printf("%d/%d/%d\n", resultado.dia, resultado.mes, resultado.anio);

    return 0;
}

