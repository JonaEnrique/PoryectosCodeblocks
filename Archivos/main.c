#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK     0

#define ERR_ARCH    1
#define ERR_TROZADO 2

#define TAM_VEC     10
#define TAM_SUELDO  10
#define TAM_DNI     8
#define TAM_NYA     10
#define TAM_LINEA   28

#define PARAM_ARCH_EMPL         1
#define PARAM_AUMENTO           2
#define PARAM_ARCH_EMPL_BINATXT 3
#define PARAM_TIPO_TXT          4
#define PARAM_ARCH_EMPL_TXTABIN 5

typedef struct
{
    char nYa[10];
    int dni;
    float sueldo;
}
Empleado;

int generarArchivo(char* nombreArch);
int mostrarEmpleados(char* nombreArch);
int mostrarEmpleadosTXT(char* nombreArchTXT, char tipoTxt);
int actualizarSueldos(char* nombreArch, char* aumento);
int binATxt(const char* archOrigen, const char* archDestino, char tipoTxt);
int txtAbin(const char* archOrigen, const char* archDestino, char tipoTxt);
int trozarCampos(const char* cadEmpl, Empleado* empl, char tipoTxt);

int main(int argc, char* argv[])
{
    generarArchivo(argv[PARAM_ARCH_EMPL]);
//    printf("\nSueldos antes de actualiza: \n");
//    mostrarEmpleados(argv[1]);

    printf("  Archivo binario original: \n");
    mostrarEmpleados(NULL);
    mostrarEmpleados(argv[PARAM_ARCH_EMPL]);

    printf("\n  Archivo binario original a txt: \n");
    binATxt(argv[PARAM_ARCH_EMPL], argv[PARAM_ARCH_EMPL_BINATXT], argv[PARAM_TIPO_TXT][0]);
    mostrarEmpleados(NULL);
    mostrarEmpleadosTXT(argv[PARAM_ARCH_EMPL_BINATXT], argv[PARAM_TIPO_TXT][0]);

    printf("\n  Archivo txt a binario copia: \n");
    txtAbin(argv[PARAM_ARCH_EMPL_BINATXT], argv[PARAM_ARCH_EMPL_TXTABIN], argv[PARAM_TIPO_TXT][0]);
    mostrarEmpleados(NULL);
    mostrarEmpleados(argv[PARAM_ARCH_EMPL_TXTABIN]);

//    actualizarSueldos(argv[1], argv[2]);
//
//    printf("\nSueldos actualziados: \n");
//    mostrarEmpleados(argv[1]);

    return 0;
}

int generarArchivo(char* nombreArch)
{
    FILE* empleadoA = fopen(nombreArch, "wb");

    if(!empleadoA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl[TAM_VEC] = {
                        {"Jonathan", 548451, 151515},
                        {"Nahuel", 48418, 100000},
                        {"Usuario0", 1111, 100000},
                        {"Usuario1", 2222, 200000},
                        {"Usuario2", 3333, 300000},
                        {"Usuario3", 4444, 400000},
                        {"Usuario4", 5555, 500000},
                        {"Usuario5", 6666, 600000},
                        {"Usuario6", 7777, 700000},
                        {"Usuario7", 8888, 800000}
                        };
    fwrite(empl, sizeof(Empleado), TAM_VEC, empleadoA);
    fclose(empleadoA);

    return TODO_OK;
}

int mostrarEmpleados(char* nombreArch)
{
    if(!nombreArch)
    {
        printf("   NOMBRE    DNI      SUELDO\n");
        printf("  -------- --------  ---------\n");
        return TODO_OK;
    }

    FILE* empleadoA = fopen(nombreArch, "rb");

    if(!empleadoA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl;

    fread(&empl, sizeof(Empleado), 1, empleadoA);

    while(!feof(empleadoA))
    {
        printf("%10s %8d %10.2f\n", empl.nYa, empl.dni, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, empleadoA);
    }

    fclose(empleadoA);

    return TODO_OK;
}

int mostrarEmpleadosTXT(char* nombreArchTXT, char tipoTxt)
{
    if(!nombreArchTXT)
    {
        printf("   NOMBRE    DNI      SUELDO\n");
        printf("  -------- --------  ---------\n");
        return TODO_OK;
    }

    FILE* empleadoA = fopen(nombreArchTXT, "rt");

    if(!empleadoA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl;
    char cadEmpl[200];

    while(fgets(cadEmpl, sizeof(cadEmpl), empleadoA)) // fgets lee hasta un \n --> Le agrega un \n\0
    {
        trozarCampos(cadEmpl, &empl, tipoTxt);
        printf("%10s %8d %10.2f\n", empl.nYa, empl.dni, empl.sueldo);
    }
//    while(fscanf(empleadoA, "%s%d%f", empl.nYa, &empl.dni, &empl.sueldo) != EOF)
//    {
//        printf("%10s %08d %10.2f\n", empl.nYa, empl.dni, empl.sueldo);
//    }

    fclose(empleadoA);

    return TODO_OK;
}

int actualizarSueldos(char* nombreArch, char* aumento)
{
    FILE* empleadosA = fopen(nombreArch,"r+b");

    if(!empleadosA)
    {
        puts("Error absoluto.");
        return ERR_ARCH;
    }

    Empleado empl;

    fread(&empl, sizeof(Empleado), 1, empleadosA);

    while(!feof(empleadosA))
    {
        empl.sueldo += empl.sueldo*(atof(aumento)/100);

        fseek(empleadosA, -(long)sizeof(Empleado), SEEK_CUR);
        fwrite(&empl, sizeof(Empleado), 1, empleadosA);
        fseek(empleadosA, 0L, SEEK_CUR);
        fread(&empl, sizeof(Empleado), 1, empleadosA);
    }

    fclose(empleadosA);

    return TODO_OK;
}

int binATxt(const char* archOrigen, const char* archDestino, char tipoTxt)
{
    FILE* archBin = fopen(archOrigen, "rb");
    FILE* archTxt = fopen(archDestino, "wt");
    Empleado empl;
    char* formato = tipoTxt=='V' ? "%s|%d|%f\n" : "%10s%8d%10.2f\n";

    if(!archBin || !archTxt)
    {
        printf("Error al abrir alguno de los archivos.");
        return ERR_ARCH;
    }

    fread(&empl, sizeof(Empleado), 1, archBin);
    while(!feof(archBin))
    {
        fprintf(archTxt, formato, empl.nYa, empl.dni, empl.sueldo);
        fread(&empl, sizeof(Empleado), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int txtAbin(const char* archOrigen, const char* archDestino, char tipoTxt)
{
    FILE* archBin = fopen(archDestino, "wb");
    FILE* archTxt = fopen(archOrigen, "rt");
//    char* formato = tipoTxt=='V' ? "%s|%d|%f\n" : "%10s%8d%10.2f\n";

    if(!archBin || !archTxt)
    {
        printf("Error al abrir alguno de los archivos.");
        return ERR_ARCH;
    }

    Empleado empl;
    char cadEmpl[200];

    while(fgets(cadEmpl, sizeof(cadEmpl), archTxt)) // fgets lee hasta un \n --> Le agrega un \n\0
    {
        trozarCampos(cadEmpl, &empl, tipoTxt);
        fwrite(&empl, sizeof(Empleado), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int trozarCampos(const char* cadEmpl, Empleado* empl, char tipoTxt)
{
    if(tipoTxt == 'V')
    {
        char* caracter = strchr(cadEmpl, '\n');
        *caracter = '\0';

        /* SUELDO */
        caracter = strrchr(cadEmpl, '|');
//        sscanf(caracter, "%|f", &empl->sueldo);
        sscanf(caracter + 1, "%f", &empl->sueldo);
        *caracter = '\0';

        /* DNI */
        caracter = strrchr(cadEmpl, '|');
        sscanf(caracter + 1, "%d", &empl->dni);
        *caracter = '\0';

        /* N Y A */
        strcpy(empl->nYa, cadEmpl);

        return TODO_OK;
    }

    if(tipoTxt == 'F')
    {
        char* caracter = (char*)cadEmpl + TAM_LINEA;
        *caracter = '\0';

        /* SUELDO */
        caracter -= TAM_SUELDO;
        sscanf(caracter, "%f", &empl->sueldo);
        *caracter = '\0';

        /* DNI */
        caracter -= TAM_DNI;
        sscanf(caracter, "%d", &empl->dni);
        *caracter = '\0';

        /* N Y A */
        strcpy(empl->nYa, cadEmpl);

        return TODO_OK;
    }

    return ERR_TROZADO;
}
