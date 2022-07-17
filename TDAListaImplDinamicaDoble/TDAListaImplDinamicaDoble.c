#define TDA_LISTA_IMPL_DINAMICA_DOBLE
#include "../TDALista/TDALista.h"
#include <string.h>
#include <stdlib.h>

void crearLista(Lista* pl)
{
    *pl = NULL;
}

booleano verPrimeroDeLista(const Lista* pl, void* elem, size_t tamElem)
{
    NodoD* act = *pl;

    if(!act)
        return FALSO;

    while(act->ant)
        act = act->ant;

    memcpy(elem, act->elem, min(act->tamElem, tamElem));

    return VERDADERO;
}

int insertarEnListaOrdAscSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;

    if(act)
    {
        while(act->ant && cmp(elem, act->elem) < 0)
            act = act->ant;

        while(act->sig && cmp(elem, act->elem) > 0)
          act = act->sig;

        int comp = cmp(elem, act->elem);

        if(comp == 0) // Puedo hacer la version de actualizar
            return DUPLICADO;

        if(comp < 0)
        {
            sig = act;
            ant = act->ant;
        }
        else
        {
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nue = crearNodoD(elem, tamElem);

    if(!nue) // Teng que destruir a memoria?
        return SIN_MEM;

    nue->ant = ant; // 1
    nue->sig = sig; // 2

    if(ant) // 3
        ant->sig = nue;

    if(sig) // 4
        sig->ant = nue;

    *pl = nue;

    return TODO_OK;
}

int insertarEnListaOrdDescSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaOrdAscConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;

    if(act)
    {
        while(act->ant && cmp(elem, act->elem) < 0) // Si es menor que actual me muevo para la izquiera
            act = act->ant;

        while(act->sig && cmp(elem, act->elem) > 0) // Si es mayor que actual me muevo para la derecha
            act = act->sig;

        int comp = cmp(elem, act->elem);

        if(comp < 0) // Si quiero que el duplciado este a la izquierda, pongo <=
        {
            sig = act;
            ant = act->ant;
        }
        else // Incluye el duplicado si es que quiero que esté a la derecha
        {
            ant = act;
            sig = act->sig;
        }

        /* Los nodos contiguos lo asignamos una vez creado el nodo nuevo */
    }

    NodoD* nae = crearNodoD(elem, tamElem);

    if(!nae)
        return SIN_MEM;

    nae->ant = ant;
    nae->sig = sig;

    if(ant)
        ant->sig = nae;

    if(sig)
        sig->ant = nae;

    *pl = nae;

    return TODO_OK;
}

int insertarEnListaOrdDescConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaDesord(Lista* pl, const void* elem, size_t tamElem);
int insertarOActualizarEnListaOrdAsc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarOActualizarEnListaOrdDesc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);

int insertarEnListaAlInicio(Lista* pl, const void* elem, size_t tamElem)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;

    if(act)
    {
        while(act->ant)
            act = act->ant;

        ant = act->ant; // Siempre va a ser NULL
        sig = act;
    }

    NodoD* nue = crearNodoD(elem, tamElem);

    if(!nue)
    {
        destruirNodoSinGuardarD(nue);

        return SIN_MEM;
    }

    nue->ant = ant; // Siempre va a ser NULL
    nue->sig = sig; // -> engancho

    if(sig) // <- engancho
        sig->ant = nue;

    *pl = nue;

    return TODO_OK;
}

int insertarEnListaAlFinal(Lista* pl, const void* elem, size_t tamElem)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;

    if(act)
    {
        while(act->sig)
            act = act->sig;

        ant = act;
        sig = act->sig;
    }

    NodoD* nue = crearNodoD(elem, tamElem);

    if(!nue)
    {
        destruirNodoSinGuardarD(nue);
        return SIN_MEM;
    }

    nue->ant = ant;
    nue->sig = sig;

    if(ant)
        ant->sig = nue;

    *pl = nue;

    return TODO_OK;
}

int insertarEnListaEnPosicion(Lista* pl, const void* elem, size_t tamElem, unsigned pos)
{
    NodoD* act = *pl;
    NodoD* ant = NULL, * sig = NULL;
    int posAct = 1;

    if(act)
    {
        while(act->ant) // Llevamos a act al principio de la lista
            act = act->ant;

        while(act->sig && posAct < pos) // Nos movemos hasta la posicion de insercion
        {
            act = act->sig;
            posAct++;
        }

        if(posAct == pos || pos == 0)
        {
            /* Enganchamos uno antes asi queda en la posicion elegida o estamos en posicion 0 */
            ant = act->ant;
            sig = act;
        }
        else
        {
            /* Si no llegamos a la posicion elegida porque nos pasamos, insertamo al final */
            ant = act;
            sig = act->sig;
        }
    }

    NodoD* nue = crearNodoD(elem, tamElem);

    if(!nue)
        return SIN_MEM;

    nue->ant = ant;
    nue->sig = sig;

    if(ant)
        ant->sig = nue;

    if(sig)
        sig->ant = nue;

    *pl = nue;

    return TODO_OK;
}

booleano eliminarDeListaOrdPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return FALSO;

    NodoD* nae = *pl;

    while(nae->ant && cmp(elem, nae->elem) < 0)
        nae = nae->ant;

    while(nae->sig && cmp(elem, nae->elem) > 0)
        nae = nae->sig;

    if(cmp(elem, nae->elem) != 0)
        return FALSO;

    if(nae->ant)
        nae->ant->sig = nae->sig;

    if(nae->sig)
        nae->sig->ant = nae->ant;

    if(nae == *pl)
    {
        if(nae->sig)
            *pl = nae->sig;
        else
            *pl = nae->ant;
    }

    destruirNodoD(nae, elem, tamElem); // Guarda el elemento eliminado en la variable de parametro

    return VERDADERO;
}

booleano eliminarDeListaDesordPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    NodoD* nae = *pl;

    if(!nae)
        return FALSO;

    NodoD* ini = nae; // Inicio de la lista

    while(nae->ant && cmp(elem, nae->elem) != 0) // Recorro la primera mitad
        nae = nae->ant;

    if(cmp(elem, nae->elem) != 0) // Verifico sino lo encontre en la primera mitad
        nae = ini->sig; // Sino lo encontre arranco en la segunda mitad despues del inicio, al inicio ya lo comprobe

    while(nae->sig && cmp(elem, nae->elem) != 0) // Recorro la segunda mitad
        nae = nae->sig;

    if(cmp(elem, nae->elem) != 0) // Sino lo encontre en la segunda mitad, no está el elemento
        return FALSO;

    /* Lo encontre, entonces desengancho */
    if(nae->ant)
        nae->ant->sig = nae->sig;

    if(nae->sig)
        nae->sig->ant = nae->ant;

    /* Verifico que no sea el puntero a lista el que voy a eliminar, sino lo cambio */
    if(nae == *pl)
    {
        if(nae->sig)
            *pl = nae->sig;
        else
            *pl = nae->ant;
    }

    /* Guardamos y eliminamos */
    destruirNodoD(nae, elem, tamElem);

    return TODO_OK;
}

void recorrerLista(Lista* pl, Accion accion, void* datosAccion)
{
    if(!*pl)
        return;

    NodoD* act = *pl;

    while(act->ant)
        act = act->ant;

    while(act)
    {
        accion(act->elem, datosAccion);
        act = act->sig;
    }
}

booleano eliminarDeListaPrimero(Lista *pl, void* elem, size_t tamElem)
{
    if(!*pl) // Me fijo si es que no es lista vacia
        return FALSO;

    NodoD* nae = *pl;

    while(nae->ant) // Voy hasta el principio de la lista
        nae = nae->ant;

    if(nae->sig)
        nae->sig->ant = nae->ant;

    if(nae == *pl)
    {
        if(nae->sig)
            *pl = nae->sig;
        else
            *pl = nae->ant;
        /* Si es que sig y ant son NULL, entonces ya no hay mas elementos en la lista */
    }

    destruirNodoD(nae, elem, tamElem);

    return VERDADERO;
}

int eliminarDeListaOrdDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar)
{
    if(!*pl)
        return FALSO;

    NodoD* naeAct = *pl, * naeDup;

    while(naeAct->ant)
        naeAct = naeAct->ant;

    naeDup = naeAct->sig;

    while(naeAct && naeDup)
    {
        while(naeDup && cmp(naeAct->elem, naeDup->elem) == 0)
        {
            if(actualizar)
                actualizar(naeAct->elem, naeDup->elem);

            if(naeDup->sig)
                naeDup->sig->ant = naeDup->ant;

            if(naeDup->ant)
                naeDup->ant->sig = naeDup->sig;

            if(*pl == naeDup)
            {
                if(naeDup->sig)
                    *pl = naeDup->sig;
                else
                    *pl = naeDup->ant;
            }

            free(naeDup->elem);
            free(naeDup);

            naeDup = naeAct->sig;
        }

        naeAct = naeDup;
        naeDup = naeDup->sig;
    }

    return VERDADERO;
//    if(!*pl) // No hay nodos
//        return FALSO;
//
//    NodoD* nae = *pl, * dup = NULL;
//
//    while(nae->ant) // Llevo al principio nae
//        nae = nae->ant;
//
//    if(!nae->sig) // Un solo nodo
//        return FALSO;
//
//    dup = nae->sig;
//
//    while(nae)
//    {
//        while(dup && cmp(dup->elem, nae->elem) == 0)
//        {
//            if(actualizar)
//                actualizar(nae->elem, dup->elem);
//
//            if(dup->sig)
//                dup->sig->ant = dup->ant;
//
//            if(dup->ant)
//                dup->ant->sig = dup->sig;
//
//            destruirNodoSinGuardarD(dup);
//
//            dup = nae->sig;
//        }
//
//        nae = nae->sig;
//    }
//
//    return VERDADERO;
}

booleano buscarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return FALSO;

    NodoD* act = *pl;

    while(act->ant && cmp(elem, act->elem) != 0)
        act = act->ant;

    while(act->sig && cmp(elem, act->elem) != 0)
        act = act->sig;

    if(cmp(elem, act->elem) != 0)
        return FALSO;

    memcpy(elem, act->elem, min(tamElem, act->tamElem));
    *pl = act;

    return VERDADERO;
}

booleano buscarEnListaDesord(const Lista* pl, void* elem, size_t tamElem, Cmp cmp)
{
    if(!*pl)
        return FALSO;

    NodoD* act = *pl;

    while(act->ant)
        act = act->ant;

    while(act->sig && cmp(elem, act->elem) != 0)
        act = act->sig;

    if(cmp(elem, act->elem) != 0)
        return FALSO;

    memcpy(elem, act->elem, min(tamElem, act->tamElem));
    *(Lista*)pl = act;

    return VERDADERO;
}

booleano listaVacia(Lista* pl)
{
    return !*pl;
}
