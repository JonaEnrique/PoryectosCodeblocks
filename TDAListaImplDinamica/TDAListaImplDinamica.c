#define TDA_LISTA_IMPL_DINAMICA
#include "../TDALista/TDALista.h"
#include <string.h>

Lista* buscarMenorDeLista(Lista* pl, Cmp cmp); // va acá?

void crearLista(Lista* pl)
{
    *pl = NULL;
}

booleano verPrimeroDeLista(const Lista* pl, void* elem, size_t tamElem)
{
   if(!*pl)
        return FALSO;

    memcpy(elem, (*pl)->elem, min(tamElem, (*pl)->tamElem));

    return VERDADERO;
}

int insertarEnListaOrdAscSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    while (*pl && Cmp((*pl)->elem, elem) < 0) // El orden si importa
        pl = &(*pl)->siguiente;

    if(*pl && Cmp((*pl)->elem, elem) == 0)
        return DUPLICADO;

    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return SIN_MEM;

    nue->siguiente = *pl; // 1
    *pl = nue; // 2

    return TODO_OK;
}

int insertarEnListaOrdDescSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp Cmp)
{
    while (*pl && Cmp((*pl)->elem, elem) > 0) // El orden si importa
        pl = &(*pl)->siguiente;

    if(*pl && Cmp((*pl)->elem, elem) == 0)
        return DUPLICADO;

    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return SIN_MEM;

    nue->siguiente = *pl; // 1
    *pl = nue; // 2

    return TODO_OK;
}

int insertarEnListaOrdAscConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp Cmp)
{
    while (*pl && Cmp((*pl)->elem, elem) < 0) // El orden si importa
        pl = &(*pl)->siguiente;

    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue) // Preguntar siempre despues de crear un nodo
        return SIN_MEM;

    nue->siguiente = *pl; // 1 -> engancha el siguiente
    *pl = nue; // 2 ->engancha nuevo nodo

    return TODO_OK;
}

int insertarEnListaOrdDescConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp Cmp)
{
    while (*pl && Cmp((*pl)->elem, elem) > 0) // El orden si importa
        pl = &(*pl)->siguiente;

    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue) // Preguntar siempre despues de crear un nodo
        return SIN_MEM;

    nue->siguiente = *pl; // 1 -> engancha el siguiente
    *pl = nue; // 2 ->engancha nuevo nodo

    return TODO_OK;
}

int insertarEnListaDesord(Lista* pl, const void* elem, size_t tamElem)
{
    while(*pl)
        pl = &(*pl)->siguiente;

    Nodo* nue = crearNodo(elem, tamElem);

    if(!nue)
        return SIN_MEM;

    nue->siguiente = *pl; // 1
    *pl = nue; // 2

    return TODO_OK;
}

int insertarOActualizarEnListaOrdAsc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    while(*pl && cmp(elem, (*pl)->elem) > 0)
        pl = &(*pl)->siguiente;

    if(*pl && cmp(elem, (*pl)->elem) == 0)
    {
        actualizar((*pl)->elem, elem);
        return TODO_OK;
    }

    Nodo* nodoAInsertar = crearNodo(elem, tamElem);

    if(!nodoAInsertar)
        return SIN_MEM;

    nodoAInsertar->siguiente = *pl;
    *pl = nodoAInsertar;

    return TODO_OK;
}

int insertarOActualizarEnListaOrdDesc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar)
{
    while(*pl && cmp(elem, (*pl)->elem) < 0)
        pl = &(*pl)->siguiente;

    if(*pl && cmp(elem, (*pl)->elem) == 0)
    {
        actualizar((*pl)->elem, elem);
        return TODO_OK;
    }

    Nodo* nodoAInsertar = crearNodo(elem, tamElem);

    if(!nodoAInsertar)
        return SIN_MEM;

    nodoAInsertar->siguiente = *pl;
    *pl = nodoAInsertar;

    return TODO_OK;
}

int insertarEnListaAlInicio(Lista* pl, const void* elem, size_t tamElem)
{
    Nodo* nodoAInsertar = crearNodo(elem, tamElem);

    if(!nodoAInsertar)
        return SIN_MEM;

    nodoAInsertar->siguiente = *pl;
    *pl = nodoAInsertar;

    return TODO_OK;
}

int insertarEnListaAlFinal(Lista* pl, const void* elem, size_t tamElem)
{
    while(*pl) // Llevo el nodo al final
        pl = &(*pl)->siguiente;

    Nodo* nodoAInsertar = crearNodo(elem, tamElem);

    if(!nodoAInsertar)
        return SIN_MEM;

    nodoAInsertar->siguiente = *pl;
    *pl = nodoAInsertar;

    return TODO_OK;
}

int insertarEnListaEnPosicion(Lista* pl, const void* elem, size_t tamElem, unsigned pos)
{
    int i = 1;

    while(*pl && i < pos)
    {
        pl = &(*pl)->siguiente;

        i++;
    }

    //if(!*pl) // No se pudo insertar? o Inserto a lo ultimo?
        //return 0;

    Nodo* nodoAInsertar = crearNodo(elem, tamElem);

    if(!nodoAInsertar)
        return SIN_MEM;

    nodoAInsertar->siguiente = *pl;
    *pl = nodoAInsertar;

    return TODO_OK;
}

booleano eliminarDeListaOrdAsc(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    while(*pl && cmp(elem, (*pl)->elem) < 0) // Recorro
        pl = &(*pl)->siguiente;

    /*Sino se encontro va a ser negativo porque al estar en una lista ordenada se sabe que si es menor que el actual
    no se encontro*/
    if(!*pl || cmp(elem, (*pl)->elem) < 0) // Verifico sino llegue al final de la lista o el elemento no se encontro
        return FALSO;

    Nodo* nae = *pl; // No hace falta crear el nodo PORQUE ESTOY SACANDO UNO DE LA LISTA
    *pl = nae->siguiente; //(*pl)->siguiente

    destruirNodo(nae, elem, tamElem);

    return VERDADERO;
}

booleano eliminarDeListaOrdDesc(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    while(*pl && cmp(elem, (*pl)->elem) > 0) // Recorro
        pl = &(*pl)->siguiente;

    /*Sino se encontro va a ser negativo porque al estar en una lista ordenada se sabe que si es menor que el actual
    no se encontro*/
    if(!*pl || cmp(elem, (*pl)->elem) < 0) // Verifico sino llegue al final de la lista o el elemento no se encontro
        return FALSO;

    Nodo* nae = *pl; // No hace falta crear el nodo PORQUE ESTOY SACANDO UNO DE LA LISTA
    *pl = nae->siguiente; //(*pl)->siguiente

    destruirNodo(nae, elem, tamElem);

    return VERDADERO;
}

booleano eliminarDeListaDesord(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    while(*pl && cmp(elem, (*pl)->elem) != 0) // Recorro
        pl = &(*pl)->siguiente;

    if(!*pl)
        return FALSO; // No se encontro

    Nodo* nae = *pl; // No hace falta crear el nodo PORQUE ESTOY SACANDO UNO DE LA LISTA
    *pl = nae->siguiente; //(*pl)->siguiente

    destruirNodo(nae, elem, tamElem);

    return VERDADERO;
}

int eliminarDuplicadosDeListaOrd(Lista* pl, Cmp cmp) // Se puede cambiar
{
    while(*pl && (*pl)->siguiente)
    {
        while(*pl && (*pl)->siguiente && cmp((*pl)->elem, (*pl)->siguiente->elem) != 0)
            pl = &(*pl)->siguiente;

        if(!*pl || !(*pl)->siguiente)
            return 0;

        Nodo* nae = *pl; // No hace falta crear el nodo PORQUE ESTOY SACANDO UNO DE LA LISTA
        *pl = nae->siguiente; //(*pl)->siguiente

        destruirNodoSinGuardar(nae);
    }

    return 1;
}

int eliminarDuplicadosDeListaDesord(Lista* pl, Cmp cmp)
{
    if(!*pl || !(*pl)->siguiente)
        return 0;

    Lista* plCursor;

    while(*pl)
    {
        plCursor = &(*pl)->siguiente;

        while(*plCursor)
        {
            if(cmp((*pl)->elem, (*plCursor)->elem) == 0)
            {
                Nodo* nae = *plCursor; // No hace falta crear el nodo PORQUE ESTOY SACANDO UNO DE LA LISTA
                *plCursor = nae->siguiente; //(*pl)->siguiente

                destruirNodoSinGuardar(nae);
            }
            else
                plCursor = &(*plCursor)->siguiente; // Avanzo nomas cuando no desenganche, si desenganche "avanzo solo"
        }

        pl = &(*pl)->siguiente;
    }

    return 1;
}

booleano eliminarDeListaOrdPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    int cmpRes;

    while(*pl && (cmpRes = cmp(elem, (*pl)->elem)) > 0)
        pl = &(*pl)->siguiente;

    if(cmpRes == 0)
    {
        Nodo* nodoAEliminar = *pl;

        *pl = nodoAEliminar->siguiente;

        destruirNodoSinGuardar(nodoAEliminar);

        return VERDADERO;
    }

    return FALSO;
}

booleano eliminarDeListaDesordPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    while(*pl && cmp(elem, (*pl)->elem) != 0)
        pl = &(*pl)->siguiente;

    if(!*pl)
        return FALSO;

    Nodo* nodoAEliminar = *pl;

    *pl = nodoAEliminar->siguiente;
    destruirNodoSinGuardar(nodoAEliminar);

    return VERDADERO;
}

int eliminarDeListaOrdPorCondicion(Lista* pl, Condicion condicion)
{
    while(*pl)
    {
        if(condicion((*pl)->elem))
        {
            Nodo* nodoAEliminar = *pl;

            *pl = nodoAEliminar->siguiente; // Avanza
            destruirNodoSinGuardar(nodoAEliminar);
        }
        else // Importante
            pl = &(*pl)->siguiente; // Avanza
    }

    return TODO_OK;
}

booleano eliminarDeListaPrimero(Lista* pl, void* elem, size_t tamElem)
{
    if(!*pl)
        return FALSO;

    Nodo* nodoAEliminar = *pl;

    *pl = nodoAEliminar->siguiente;
    destruirNodo(nodoAEliminar, elem, tamElem);

    return VERDADERO;
}

booleano eliminarDeListaUltimo(Lista* pl, void* elem, size_t tamElem)
{
    while(*pl && (*pl)-> siguiente)
        pl = &(*pl)->siguiente;

    if(!*pl)
        return FALSO;

    Nodo* nodoAEliminar = *pl;

    *pl = nodoAEliminar->siguiente;
    destruirNodo(nodoAEliminar, elem, tamElem);

    return VERDADERO;
}

int eliminarDeListaOrdDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar) // Por qué actualizar?
{
    while(*pl && (*pl)->siguiente)
    {
        if(cmp((*pl)->elem, (*pl)->siguiente->elem) == 0)
        {
            actualizar((*pl)->elem, (*pl)->siguiente->elem);

            Nodo* nodoAEliminar = (*pl)->siguiente;
            (*pl)->siguiente = nodoAEliminar->siguiente;

            destruirNodoSinGuardar(nodoAEliminar);
        }
        else
            pl = &(*pl)->siguiente;
    }

    return TODO_OK;
}

int eliminarDeListaDesordDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar) // Por qué actualizar?
{
    Lista* plCursor;

    while(*pl)
    {
        plCursor = &(*pl)->siguiente;

        while(*plCursor)
        {
            if(cmp((*pl)->elem, (*plCursor)->elem) == 0)
            {
                actualizar((*pl)->elem, (*plCursor)->elem);

                Nodo* nodoAEliminar = *plCursor;
                *plCursor = nodoAEliminar->siguiente;

                destruirNodoSinGuardar(nodoAEliminar);
            }
            else
                plCursor = &(*plCursor)->siguiente;
        }

        pl = &(*pl)->siguiente;
    }

    return TODO_OK;
}

int eliminarDeListaDesordDuplicadosV2(Lista* pl, void* elem, Cmp cmp, Actualizar actualizar) // Por qué actualizar?
{
    Lista* plCursor;

    while(*pl)
    {
        plCursor = &(*pl)->siguiente;

        while(*plCursor)
        {
            if(cmp((*pl)->elem, (*plCursor)->elem) == 0)
            {
                actualizar((*pl)->elem, (*plCursor)->elem);

                Nodo* nodoAEliminar = *plCursor;
                *plCursor = nodoAEliminar->siguiente;

                destruirNodoSinGuardar(nodoAEliminar);
            }
            else
                plCursor = &(*plCursor)->siguiente;
        }

        pl = &(*pl)->siguiente;
    }

    return TODO_OK;
}

booleano crearIterador(Iterador* it, const Lista* pl)
{
    it->primero = *pl;
    it->act = NULL;

    if(!pl)
        return FALSO;

    return VERDADERO;
}

void primeroDeLista(Iterador* it, void* elem, size_t tamElem) // Copia al elemento el primero y a la vez el it apunta al primero
{
    if(!it->primero) // La lista está vacia
        return;

    it->act = it->primero;

    memcpy(elem, it->act->elem, min(tamElem, it->act->tamElem));
}

booleano siguienteDeLista(Iterador* it, void* elem, size_t tamElem)
{
    if(!it->act)
        return FALSO;

    it->act = it->act->siguiente;

    if(!it->act)
        return FALSO;

    memcpy(elem, it->act->elem, min(tamElem, it->act->tamElem));

    return VERDADERO;
}

booleano haySiguienteDeLista(Iterador* it)
{
    if(!it->act)
        return FALSO;

    return it->act->siguiente != NULL;
}

booleano finLista(Iterador* it)
{
    return !it->act;
}

/*
    primero()
    while(!fin())
    {
        tratar()
        siguiente()
    }
*/

void recorrerLista(Lista* pl, Accion accion, void* datosAccion)
{
    while(*pl)
    {
        accion((*pl)->elem, datosAccion);
        pl = &(*pl)->siguiente;
    }
}

void ordenarLista(Lista* pl, Cmp cmp)
{
    Lista lord;
    Lista* plult = &lord;
    Lista* plmenor;

    while (*pl) // Va a seguir hasta que pl apunte a nada
    {
        plmenor = buscarMenorDeLista(pl, cmp);
        *plult = *plmenor;
        *plmenor = (*plmenor)->siguiente; // Desengancha de la lista principal
        plult = &(*plult)->siguiente;
    }
    *pl = lord;
}

Lista* buscarMenorDeLista(Lista* pl, Cmp cmp)
{
    Lista* plmenor = pl;
    Lista* plact = &(*plmenor)->siguiente;

    while (*plact)
    {
        if (cmp((*plact)->elem, (*plmenor)->elem) < 0)
        {
            plmenor = plact;
        }
        plact = &(*plact)->siguiente;
    }

    return plmenor;
}

void ordenarLista_ALU(Lista* pl, Cmp cmp)
{
    Lista lOrd;
    Lista* plUltOrd = &lOrd;
    Lista* plMenor;

    while(*pl) // Va a seguir hasta que pl apunte a nada
    {
        plMenor = buscarMenorDeLista(pl, cmp);
        *plUltOrd = *plMenor;
        *plMenor = (*plMenor)->siguiente;// Desengancha de la lista principal

        plUltOrd = &(*plUltOrd)->siguiente;
    }

    *pl = lOrd; // pl apunta a la nueva lista ordenada
}

Lista* buscarMenorDeLista_ALU(Lista* pl, Cmp cmp)
{
    Lista* plMenor = pl;
    Lista* plAct = &(*pl)->siguiente;

    while(*plAct)
    {
        if(cmp((*plMenor)->elem, (*plAct)->elem) < 0)
            plMenor = plAct;

        plAct = &(*pl)->siguiente;
    }

    return plMenor;
}
