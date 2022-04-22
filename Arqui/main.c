#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int num;
    int dni;
    int edad;
    char c;
    float f;
}Persona;

int main()
{
    char palabra[5] = "Hola";
    int v[5] = {72, 111, 108, 97, 0};
    char* p = (char*)v;
//    float num;
//    printf("%c: ", p[0]);
//    printf("%d", '\0');
    printf("%c", p[1]);

    //Hice un cambioo

//    Persona per;
//    Persona* puntPer = &per;
//
//    printf("%p\n", &per);
//    printf("%p\n", &(per.num));
//    printf("%p\n", &(per.dni));
//    printf("%p\n", &(per.edad));
//    printf("%p\n", &(per.c));
//    printf("%p\n", &(per.f));


//    unsigned int a = 0x47000018; // 1024.75
//
//    float f = *((float*)&a);
//    printf("%f\n", f);

    return 0;
}
