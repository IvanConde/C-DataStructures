#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */

struct pila {
    void** datos;
    size_t tope;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

bool redimensionar_pila(pila_t* pila, size_t nueva_capacidad){

    void** datos_nuevo = realloc(pila->datos, (nueva_capacidad * sizeof(void*)));
    if((nueva_capacidad > 0) && (datos_nuevo == NULL)){
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = nueva_capacidad;

    return true;

}

pila_t* pila_crear(void){

    pila_t* pila = malloc(sizeof(pila_t));
    if(pila == NULL){
        return NULL;
    }

    pila->datos = malloc(sizeof(void*)*2);
    if(pila->datos == NULL){
        free(pila);
        return NULL;
    }

    pila->capacidad = 2;
    pila->tope = 0;

    return pila;

}

void pila_destruir(pila_t *pila){

    free(pila->datos);
    free(pila);

}

bool pila_esta_vacia(const pila_t *pila){

    return (pila->tope == 0);

}

bool pila_apilar(pila_t *pila, void* valor){

    if(pila->capacidad == pila->tope){
        if(!redimensionar_pila(pila, pila->capacidad*2)){
            return false;
        }
    }

    pila->datos[pila->tope] = valor;
    pila->tope++;

    return true;

}

void* pila_ver_tope(const pila_t *pila){

    if(pila_esta_vacia(pila)){
        return NULL;
    }

    return pila->datos[pila->tope-1];

}

void* pila_desapilar(pila_t *pila){

    if(pila_esta_vacia(pila)){
        return NULL;
    }

    void* valor_tope_anterior = pila_ver_tope(pila);
    pila->tope--;

    if(((pila->capacidad/4) >= pila->tope) && (pila->capacidad > 2)){
        redimensionar_pila(pila, (pila->capacidad/2));
    }

    return valor_tope_anterior;

}

// ...