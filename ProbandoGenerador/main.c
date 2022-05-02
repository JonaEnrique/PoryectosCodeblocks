#include <stdio.h>
#include <stdlib.h>

int generarArchTxt(const char* nombreArchTxt);

int main()
{
    printf("Hello world!\n");
    return 0;
}

int generarArchTxt(const char* nombreArchTxt)
{
    FILE* archTxt = fopen(nombreArchTxt, "rt");
    if(!archTxt)
        return 2;


}
