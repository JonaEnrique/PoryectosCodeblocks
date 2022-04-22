#include <stdio.h>
#include <stdlib.h>

#include "../Vector/Vector.h"
#include "../Comun/Comun.h"

booleano sonDisjuntos(Vector* v1, Vector* v2);

int main()
{
    Vector v1 = {{1, 2, 3}, 3} ,
           v2 = {{7, 8, 9, 10}, 4} ;

    int sonDisj = sonDisjuntos(&v1, &v2);

    if(sonDisj)
        printf("Son disjuntos.");
    else
        printf("NO son disjuntos.");

    return 0;
}

booleano sonDisjuntos(Vector* v1, Vector* v2)
{
    int *cursorVec1 = v1->vec,
        *cursorVec2 = v2->vec,
        *finVec1 = v1->vec + v1->ce - 1,
        *finVec2 = v2->vec + v2->ce - 1;

    while(cursorVec1 <= finVec1)
    {
        while(cursorVec2 <= finVec2)
        {
            if(*cursorVec1 == *cursorVec2)
                return FALSO;

            cursorVec2++;
        }

        cursorVec2 = v2->vec;
        cursorVec1++;
    }

    return VERDADERO;
}
