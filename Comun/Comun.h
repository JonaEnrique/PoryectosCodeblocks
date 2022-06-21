#ifndef COMUN_H
#define COMUN_H

#define min(X,Y) ((X) <= (Y)) ? (X):(Y)
#define max(X,Y) ((X) >= (Y)) ? (X):(Y)

typedef int (*Cmp)(const void*, const void*);
typedef void (*Actualizar)(void*, const void*);
typedef void (*Mostrar)(const void*);
typedef void (*Accion)(void* elem, void* datos); // Se pone el nombre de los parametros para saber qué mandar --> 22:00 clase 25, porque son dos void*
typedef int (*Condicion)(const void* elem);

typedef enum
{
    FALSO, VERDADERO
}
booleano;

#define TODO_OK        0
#define SIN_MEM        1
#define DUPLICADO      2
#define NO_ENCONTRADO -1
#define ERR_ARCHIVO    3

#endif // COMUN_H
