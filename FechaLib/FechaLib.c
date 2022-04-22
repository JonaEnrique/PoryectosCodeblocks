#include "FechaLib.h"

#define esBisiesto(anio) (((anio) % 4 == 0 && (anio) % 100 != 0) || (anio) % 400 == 0 ? 1 : 0)

//int esBisiesto(int anio); // Solamente yo la puedo ver, no te la ofrezco sino que la utilizo yo para hacer una funcion que si vas a poder utilizar
int cantDiasMes(int mes, int anio);

booleano esFechaValida(const Fecha* fecha)
{
    if(fecha->anio >= ANIO_BASE)
        if(fecha->mes >= 1 && fecha->mes <= 12)
            if(fecha->dia >= 1 && fecha->dia <= cantDiasMes(fecha->mes, fecha->anio))
                return VERDADERO;

    return FALSO;
}

int cantDiasMes(int mes,int anio)
{
    const static int cdm[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];

    //    int cantDiasMes = 31;
//
//    if(mes == 4 || mes == 6 || mes == 9)
//        cantDiasMes = 30;
//
//    if(mes == 2)
//    {
//        if(esBisiesto(anio))
//            cantDiasMes = 29;
//        else
//            cantDiasMes = 28;
//    }
//
//    return cantDiasMes;

//    switch(mes)
//    {
//    case 4:
//    case 6:
//    case 9:
//    case 11: return 0;
//
//    case 2:
//        if(esBisiesto(anio))
//            return 29;
//        else
//            return 28;
//    }
//
//    return 31;
}

//booleano esBisiesto(int anio)
//{
//    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0 ? 1 : 0;
//}

int cantDiasAnio(int anio)
{
    return 365+esBisiesto(anio);
}

int diaDelAnio(const Fecha* f)
{
    int dias=f->dia,i;

    for(i=1;i<f->mes;i++)
        dias+=cantDiasMes(i,f->anio);
    return dias;

    /*
    int acum = 0;

    acum += f->dia;

    int cantDiasAcumXMes[][13] =
    {
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
    };

    return acum + cantDiasAcumXMes[esBisiesto(f->anio)][f->mes]; */
}

int diferenciaDeDiasEntreFechasN(const Fecha* f1,const Fecha* f2)
{
    int dif = diaDelAnio(f2) - diaDelAnio(f1);
    int anioAct= f1 -> anio;

    while(anioAct < f2 -> anio)
    {
        dif += cantDiasAnio(anioAct);
        anioAct++;
    }

    return dif;
}

int sumaDiasEntreAnios(int anioAnt,int anioAct)
{
    int i,dias=0;

    for(i=anioAnt+1;i<anioAct;i++)
        dias+=365+esBisiesto(i);

    return dias;
}

Fecha sumaDiasAFecha(const Fecha* f, int dias)
{
    Fecha fechaCopia = *f;
    int cdm;

    fechaCopia.dia += dias;

    while(fechaCopia.dia > (cdm = cantDiasMes(fechaCopia.mes, fechaCopia.anio)))
    {
        fechaCopia.dia -= cdm;
//        fechaCopia.mes++;

//        if(fechaCopia.mes == 13)
//        {
//            fechaCopia.mes = 1;
//            fechaCopia.anio++;
//        }
        fechaCopia.anio += fechaCopia.mes/12;
        fechaCopia.mes = fechaCopia.mes % 12 +1;
    }

    return fechaCopia;
}

Fecha sumarFechas(const Fecha* f1,const Fecha* f2)
{
    const Fecha fechaBase = {1, 1, 1601};
    Fecha nuevaFecha;
    int diasASumar = diferenciaDeDiasEntreFechasN(&fechaBase, f2);

    nuevaFecha = sumaDiasAFecha(f1, diasASumar);

    return nuevaFecha;
}
