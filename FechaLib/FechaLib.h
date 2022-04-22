#ifndef FECHALIB_H
#define FECHALIB_H

#define ANIO_BASE 1601

//#define VERDADERO 1
//#define FALSO    0

#include "../Comun/Comun.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

booleano esFechaValida(const Fecha* fecha); // Valida fecha
int cantDiasAnio(int anio); // Cantidad de dias del anio pasado por parametro
int diaDelAnio(const Fecha* f); // Cantidad de dias hasta la fecha
int diferenciaDeDiasEntreFechasN(const Fecha* f1,const Fecha* f2); // Cantidad de dias entre dos fechas
int sumaDiasEntreAnios(int anioAnt,int anioAct); // Cantidad de dias entre dos anios sin incluirlos
Fecha sumaDiasAFecha(const Fecha* f, int dias); // Suma de dias a una fecha
Fecha sumarFechas(const Fecha* f1,const Fecha* f2);

#endif // FECHALIB_H
