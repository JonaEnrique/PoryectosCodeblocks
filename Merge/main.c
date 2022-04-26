#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../Comun/Comun.h"

#define ERR_PUNTO 52 // Error de punto

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

int generarProductos(const char* nomArchivoProds);
int generarMovimientos(const char* nomArchivoMovs);
int mostrarProductos(const char*nomArch);
int mostrarMovimientos(const char*nomArch);
int actualizarProductos(const char*nomProds, const char* nomMovs);
int cambiarExtension(const char* nombreOriginal, char* nombreCambiado, const char* extension);

int main(int argc, char* argv[])
{
    generarProductos(argv[PARAM_PRODUTOS]);
    generarMovimientos(argv[PARAM_MOVIMIENTOS]);

    puts("Productos: \n");
    mostrarProductos(argv[PARAM_PRODUTOS]);
    puts("Movimientos: \n");
    mostrarProductos(argv[PARAM_MOVIMIENTOS]);

    actualizarProductos(argv[PARAM_PRODUTOS], argv[PARAM_MOVIMIENTOS]);

    puts("Productos actualizados: \n");
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

int mostrarProductos(const char*nomArch)
{
    FILE* archProds = fopen(nomArch, "rb");

    if(archProds == NULL)
    {
        printf("Errore al abrir los archivos.\n");
        return ERR_ARCHIVO;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);

    while(!feof(archProds))
    {
        printf("Codigo: %d ", prod.codigo);
        printf("Nombre: %s ", prod.nombre);
        printf("Cantidad: %d ", prod.cantidad);
        printf("Precio: %.2f", prod.precio);
        printf("\n");

        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return TODO_OK;
}

int generarProductos(const char* nomArchivoProds)
{
    FILE* archProds = fopen(nomArchivoProds, "wb");

    if(archProds == NULL)
    {
        printf("Errore al abrir los archivos.\n");
        return ERR_ARCHIVO;
    }

    Producto prod;

    prod.codigo = 1;
    strcpy(prod.nombre, "Leche");
    prod.cantidad = 10;
    prod.precio = 2.5;

    fwrite(&prod, sizeof(Producto), 1, archProds);

    prod.codigo = 2;
    strcpy(prod.nombre, "Huevos");
    prod.cantidad = 20;
    prod.precio = 1.5;

    fwrite(&prod, sizeof(Producto), 1, archProds);

    prod.codigo = 3;
    strcpy(prod.nombre, "Pan");
    prod.cantidad = 30;
    prod.precio = 1.0;

    fwrite(&prod, sizeof(Producto), 1, archProds);

    prod.codigo = 4;
    strcpy(prod.nombre, "Aceite");
    prod.cantidad = 40;
    prod.precio = 3.5;

    fwrite(&prod, sizeof(Producto), 1, archProds);

    prod.codigo = 5;
    strcpy(prod.nombre, "Sal");
    prod.cantidad = 50;
    prod.precio = 0.5;

    fwrite(&prod, sizeof(Producto), 1, archProds);

    fclose(archProds);

    return TODO_OK;
}

int generarMovimientos(const char* nomArchivoMovs)
{
    FILE* archMovs = fopen(nomArchivoMovs, "wb");

    if(archMovs == NULL)
    {
        printf("Errore al abrir los archivos.\n");
        return ERR_ARCHIVO;
    }

    Producto mov;

    mov.codigo = 1;
    mov.cantidad = 10;

    fwrite(&mov, sizeof(Producto), 1, archMovs);

    mov.codigo = 2;
    mov.cantidad = 20;

    fwrite(&mov, sizeof(Producto), 1, archMovs);

    mov.codigo = 3;
    mov.cantidad = 30;

    fwrite(&mov, sizeof(Producto), 1, archMovs);

    mov.codigo = 4;
    mov.cantidad = 40;

    fwrite(&mov, sizeof(Producto), 1, archMovs);

    mov.codigo = 5;
    mov.cantidad = 50;

    fwrite(&mov, sizeof(Producto), 1, archMovs);

    fclose(archMovs);

    return TODO_OK;
}

int cambiarExtension(const char* nombreOriginal, char* nombreCambiado, const char* extension)
{
    strcpy(nombreCambiado, nombreOriginal);
    char* punto= strrchr(nombreCambiado, '.');

    if(!punto)
        return ERR_PUNTO;

    strcpy(punto + 1, extension);

    return TODO_OK;
}
