#ifndef TDALISTA_H
#define TDALISTA_H

#include "../Comun/Comun.h"

#ifdef TDA_LISTA_IMPL_ESTATICA
    #include "../TDAListaImplEstatica/TDAListaImplEstatica.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA
    #include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#endif

#ifdef  TDA_LISTA_IMPL_DINAMICA_DOBLE
    #include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#endif


void crearLista(Lista* pl);

booleano verPrimeroDeLista(const Lista* pl, void* elem, size_t tamElem);

int insertarEnListaOrdAscSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaOrdDescSinDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaOrdAscConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaOrdDescConDupl(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int insertarEnListaDesord(Lista* pl, const void* elem, size_t tamElem);
int insertarOActualizarEnListaOrdAsc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarOActualizarEnListaOrdDesc(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int insertarEnListaAlInicio(Lista* pl, const void* elem, size_t tamElem);
int insertarEnListaAlFinal(Lista* pl, const void* elem, size_t tamElem);
int insertarEnListaEnPosicion(Lista* pl, const void* elem, size_t tamElem, unsigned pos);

booleano eliminarDeListaOrdAsc(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeListaOrdDesc(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeListaDesord(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
int eliminarDuplicadosDeListaOrd(Lista* pl, Cmp cmp);
int eliminarDuplicadosDeListaDesord(Lista* pl, Cmp cmp);
//Hacer:
booleano eliminarDeListaOrdPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano eliminarDeListaDesordPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
int eliminarDeListaOrdPorCondicion(Lista* pl, Condicion condicion);
booleano eliminarDeListaPrimero(Lista* pl, void* elem, size_t tamElem);
booleano eliminarDeListaUltimo(Lista* pl, void* elem, size_t tamElem);
int eliminarDeListaOrdDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar); // Por qu� actualizar?
int eliminarDeListaDesordDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar); // Por qu� actualizar?

//Hacer
booleano buscarEnListaOrd(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
booleano buscarEnListaDesord(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);

//Hacer
void ordenarLista(Lista* pl, Cmp cmp);

//Hacer
booleano listaVacia(Lista* pl);
booleano listaLlena(Lista* pl, size_t tamElem);

//Hacer
void vaciarLista(Lista* pl);

//Hacer
void recorrerLista(Lista* pl, Accion accion, void* datosAccion);

// Iterador
booleano crearIterador(Iterador* it, const Lista* pl);
void primeroDeLista(Iterador* it, void* elem, size_t tamElem);
booleano siguienteDeLista(Iterador* it, void* elem, size_t tamElem);
booleano haySiguienteDeLista(Iterador* it);
booleano finLista(Iterador* it);


#endif// TDALISTA_H
