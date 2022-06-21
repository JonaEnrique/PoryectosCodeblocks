#include <stdio.h>
#include <stdlib.h>

#define TDA_PILA_IMPL_ESTATICA
#include "../TDAPila/TDAPila.h"

#define TAM_PAL_CODPROD 8
#define TAM_PAL_DESCRIP 16
#define TAM_PAL_PROVEED 16

#define CANT_PRODS 10

#define CANT_OPCIONES 4

typedef struct
{
    int d;
    int m;
    int a;
}Fecha;

typedef struct
{
    char codProd[TAM_PAL_CODPROD];
    char descrip[TAM_PAL_DESCRIP];
    char proveed[TAM_PAL_PROVEED];
    Fecha fechaDeCompra;
    Fecha fechaDeVencimiento;
    int cant;
    float precioDeCompra;
    float precioDeVenta;
}Producto;

int generarArchProds(const char* nombreArch);
int mostrarArchProds(const char* nombreArch);
int cargarArchEnPila(const char* nombreArch, Pila* pp);
int cargarPilaEnArch(const char* nombreArch, Pila* pp);
int menu(const char* mensaje, const char* mensajeDeError, int cantOps);

int main()
{
    int i, opcion, cantProds = 10;
    Producto prod;
    Pila pilaProd;
    const char mensaje[] = "\nElija una opcion:\n 0-Salir\n 1- Apilar\n 2-Desapilar\n 3-Ver tope\nSu opcion -> ";
    const char mensajeDeError[] = "Opcion no valida, vuelva a ingresdar. Su opcion -> ";

    crearPila(&pilaProd); // IMPORTANTE

    generarArchProds("datos.h");
    printf("Archivo: \n");
    mostrarArchProds("datos.h");
    cargarArchEnPila("datos.h", &pilaProd);

    opcion = menu(mensaje, mensajeDeError, CANT_OPCIONES);
    system("cls");

    while(opcion)
    {
        switch(opcion)
        {
        case 1: puts("\nVamos a pilar un nuevo elemento:");

                printf("Codigo de producto: ");
                scanf("%s", prod.codProd);

                printf("Descripcion: ");
                scanf("%s", prod.descrip);

                printf("Proveedor: ");
                scanf("%s", prod.proveed);

                printf("Fecha de compra: ");
                scanf("%d/%d/%d", &prod.fechaDeCompra.d, &prod.fechaDeCompra.m, &prod.fechaDeCompra.a);

                printf("Fecha de vencimiento: ");
                scanf("%d/%d/%d", &prod.fechaDeVencimiento.d, &prod.fechaDeVencimiento.m, &prod.fechaDeVencimiento.a);

                printf("Cantidad: ");
                scanf("%d", &prod.cant);

                printf("Precio de compra: ");
                scanf("%f", &prod.precioDeCompra);

                printf("Precio de venta: ");
                scanf("%f", &prod.precioDeVenta);

                if(!apilar(&pilaProd, &prod, sizeof(Producto)))
                    printf("No se pudo apilar.");
            break;
        case 2: if(!desapilar(&pilaProd, &prod, sizeof(Producto)))
                {
                    printf("No se puede desapilar más");
                    system("pause");
                }
                else
                {
                    printf("Producto desapilado: %s\n", prod.codProd);
                    system("pause");
                    cantProds--;
                }
            break;
        case 3: if(!verTopeDePila(&pilaProd, &prod, sizeof(Producto)))
                    printf("Pila vacia.\n");
                else
                {
                    printf("%8s %8s %8s %02d/%02d/%4d %02d/%02d/%4d %3d %4.2f %4.2f\n", prod.codProd, prod.descrip, prod.proveed,
                        prod.fechaDeCompra.d, prod.fechaDeCompra.m, prod.fechaDeCompra.a,
                        prod.fechaDeVencimiento.d, prod.fechaDeVencimiento.m, prod.fechaDeVencimiento.a,
                        prod.cant, prod.precioDeCompra, prod.precioDeVenta);
                    system("pause");
                }
            break;
        }

        system("cls");

        opcion = menu(mensaje, mensajeDeError, CANT_OPCIONES);
        system("cls");
    }

    if(pilaVacia(&pilaProd)) // Si la pila me queda vacia se elimina el archivo
    {
        printf("Se elimino el archivo.");
    }


    printf("\nPila: \n");
//    for(i = 0; i < cantProds; i++)
//    {
//        desapilar(&pilaProd, &prod, sizeof(Producto));
//
//        printf("%8s %8s %8s %02d/%02d/%4d %02d/%02d/%4d %3d %4.2f %4.2f\n", prod.codProd, prod.descrip, prod.proveed,
//               prod.fechaDeCompra.d, prod.fechaDeCompra.m, prod.fechaDeCompra.a,
//               prod.fechaDeVencimiento.d, prod.fechaDeVencimiento.m, prod.fechaDeVencimiento.a,
//               prod.cant, prod.precioDeCompra, prod.precioDeVenta);
//    }

    cargarPilaEnArch("Productos.txt", &pilaProd);

    return 0;
}

int generarArchProds(const char* nombreArch)
{
    Producto vProds[CANT_PRODS] = {
    {"A001111", "Leche", "Pepito", {8,7,2015}, {8,7,2022}, 50, 150.05, 151.05},
    {"A002222", "Queso", "Juancho", {9,6,2017}, {8,3,2022}, 18, 115.6, 16.6},
    {"A003333", "Arroz", "Esteban", {10,4,2020}, {18,5,2022}, 35, 220.07, 221.07},
    {"A004444", "Pan", "Carlos", {21,3,2013}, {8,9,2022}, 64, 352.05, 353.05},
    {"A005555", "Yogurt", "Pedro", {1,1,2017}, {28,7,2022}, 25, 555.05, 556.05},
    {"A006666", "Harina", "Ignacio", {4,9,2018}, {8,7,2022}, 27, 789.05, 790.05},
    {"A007777", "Azucar", "Juan", {2,2,2019}, {8,7,2022}, 31, 152.05, 153.05},
    {"A008888", "Cereal", "Pepito", {5,4,2022}, {8,7,2022}, 105, 751.05, 752.05},
    {"A009999", "Manteca", "Juancho", {21,9,2021}, {8,7,2022}, 78, 369.05, 370.05},
    {"A001010", "Jugos", "Carlos", {15,7,2014}, {8,7,2022}, 69, 410.05, 411.05}
    };

    FILE* archProds = fopen(nombreArch, "wb");
    if(!archProds)
        return ERR_ARCHIVO;

    fwrite(vProds, sizeof(Producto), CANT_PRODS, archProds);

    fclose(archProds);

    return TODO_OK;
}

int mostrarArchProds(const char* nombreArch)
{
    FILE* archProds = fopen(nombreArch, "rb");
    if(!archProds)
        return ERR_ARCHIVO;
    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        printf("%8s %8s %8s %02d/%02d/%4d %02d/%02d/%4d %3d %4.2f %4.2f\n", prod.codProd, prod.descrip, prod.proveed,
               prod.fechaDeCompra.d, prod.fechaDeCompra.m, prod.fechaDeCompra.a,
               prod.fechaDeVencimiento.d, prod.fechaDeVencimiento.m, prod.fechaDeVencimiento.a,
               prod.cant, prod.precioDeCompra, prod.precioDeVenta);

        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return TODO_OK;
}

int cargarArchEnPila(const char* nombreArch, Pila* pp)
{
    Producto prod;
    size_t tamProd = sizeof(Producto);
    FILE* archProds = fopen(nombreArch, "rb");
    if(!archProds)
        return ERR_ARCHIVO;

    fread(&prod, tamProd, 1, archProds);
    while(!feof(archProds))
    {
//        prod.precioDeCompra = 0;
        apilar(pp, &prod, tamProd);
        fread(&prod, tamProd, 1, archProds);
    }

    fclose(archProds);

    return TODO_OK;
}

int menu(const char* mensaje, const char* mensajeDeError, int cantOps)
{
    int op;
    int error = 0;
    printf("%s", mensaje);

    do
    {
        if(error)
            printf("%s", mensajeDeError);
        scanf("%d", &op);
    }while((error = (op < 0 || op >= cantOps)));

    return op;
}

int cargarPilaEnArch(const char* nombreArch, Pila* pp)
{
    FILE* archTxtProductos = fopen(nombreArch, "wt");
    if(!archTxtProductos)
        printf("No se pudo abrir el archivo.");

    Producto prod;

    while(desapilar(pp, &prod, sizeof(Producto)))
    {
        fprintf(archTxtProductos, "%8s %8s %8s %02d/%02d/%4d %02d/%02d/%4d %3d %4.2f %4.2f\n", prod.codProd, prod.descrip, prod.proveed,
               prod.fechaDeCompra.d, prod.fechaDeCompra.m, prod.fechaDeCompra.a,
               prod.fechaDeVencimiento.d, prod.fechaDeVencimiento.m, prod.fechaDeVencimiento.a,
               prod.cant, prod.precioDeCompra, prod.precioDeVenta);
        printf("%8s %8s %8s %02d/%02d/%4d %02d/%02d/%4d %3d %4.2f %4.2f\n", prod.codProd, prod.descrip, prod.proveed,
               prod.fechaDeCompra.d, prod.fechaDeCompra.m, prod.fechaDeCompra.a,
               prod.fechaDeVencimiento.d, prod.fechaDeVencimiento.m, prod.fechaDeVencimiento.a,
               prod.cant, prod.precioDeCompra, prod.precioDeVenta);
    }

    fclose(archTxtProductos);

    return TODO_OK;
}
