#include <stdio.h>
#include <stdlib.h>

int* direcElemInt(int* v, int cantElem,int elem);

int main()
{
    int v[5] = {1, 2, 3, 4, 5};

    printf("%p %p", &v[0], direcElemInt(v, 5, 3));

    return 0;
}

int* direcElemInt(int* v, int cantElem, int elem)
{
    int* fin = v + cantElem + 1;

    while(v <= fin)
    {
        if(*v == elem)
            return v;
        v++;
    }

    return NULL;
}
