#include <stdio.h>
#include <stdlib.h>
#include "../Comun/Comun.h"

#define PARAM_PRODUTOS     1
#define PARAM_MOVIMIENTOS  2
#define MAX_NOMBRE_ARCH 101
#define MAX_DESCR 101

typedef struct
{
    int codigo;
    char nombre[MAX_DESCR];
    int cantidad;
    float precio;
}
Producto;


int mostrarProductos(const char*nomArch);
int mostrarMovimientos(const char*nomArch);
int actulizarProductos(const char*nomProds, const char* nomMovs);

int main(int argc, char* argv[])
{
    mostrarProductos(argv[PARAM_PRODUTOS]);
    mostrarMovimientos(argv[PARAM_MOVIMIENTOS]);

    actulizarProductos(argv[PARAM_PRODUTOS], argv[PARAM_MOVIMIENTOS]);

    mostrarProductos(argv[PARAM_PRODUTOS]);

    return 0;
}

int actualizarProductos(const char*nomProds, const char* nomMovs)
{
    FILE* archProds = fopen(nomProds, "rb");
    FILE* archMovs = fopen(nomMovs, "rb");

    if(archProds == NULL || archMovs == NULL)
    {
        printf("Errore al abrir los archivos.\n");
        return ERR_ARCHIVO;
    }

    char nombreTmp[MAX_NOMBRE_ARCH];
    cambiarExtension(nomProds, nombreTmp, "tmp");
    FILE* archProdsTemp = fopen(nombreTmp, "wb");

    if(archProdsTemp == NULL)
    {
        printf("Errore al abrir el archivo temporal\n");
        return ERR_ARCHIVO;
    }

    Producto prod, prodNue, mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProds);
    fread(&mov, sizeof(Producto), 1, archMovs);

    while(!feof(archProds) && !feof(archMovs))
    {
        comp = prod.codigo - mov.codigo;

        if(comp == 0) // Actulizar stock producto existente.
        {
            prod.cantidad += mov.cantidad;
            fread(&mov, sizeof(Producto), 1, archMovs);
        }else if(comp < 0) // Porducto sin movimientos.
        {
            fwrite(&prod,  sizeof(Producto), 1, archProdsTemp);
            fread(&prod, sizeof(Producto), 1, archProds);
        }
        else // Porducto nuevo.
        {
            prodNue = mov; // Esto no va a ser asi sino tienen la misma estructura

            fread(&mov, sizeof(Producto), 1, archMovs);
            while(!feof(archMovs) && prodNue.codigo == mov.codigo)
            {
                prodNue.cantidad += mov.cantidad;
                fread(&mov, sizeof(Producto), 1, archMovs);
            }

            fwrite(&prodNue, sizeof(Producto), 1 , archProdsTemp);
        }
    }

    while(!feof(archProds))
    {
        fwrite(&prod,  sizeof(Producto), 1, archProdsTemp);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    while(!feof(archMovs))
    {
        prodNue = mov; // Esto no va a ser asi sino tienen la misma estructura

        fread(&mov, sizeof(Producto), 1, archMovs);
        while(!feof(archMovs) && prodNue.codigo == mov.codigo)
        {
            prodNue.cantidad += mov.cantidad;
            fread(&mov, sizeof(Producto), 1, archMovs);
        }

        fwrite(&prodNue, sizeof(Producto), 1 , archProdsTemp);
    }

    fclose(archProds);
    fclose(archMovs);
    fclose(archProdsTemp);

    remove(nomProds);
    rename(nombreTmp, nomProds);

    return TODO_OK;
}

int mostrarMovimientos(const char*nomArch);
int mostrarProductos(const char*nomArch);
