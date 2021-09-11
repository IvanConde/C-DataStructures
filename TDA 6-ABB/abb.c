#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>

#define DOS_HIJOS 2
#define UN_HIJO 1
#define SIN_HIJOS 0

typedef struct nodo{
    struct nodo* izq;
    struct nodo* der;
    char* clave;
    void* dato;
}nodo_t;

struct abb{
    size_t cantidad;
    nodo_t* raiz;
    abb_comparar_clave_t funcion_comparar;
    abb_destruir_dato_t funcion_destruir;
};

struct abb_iter{
    const abb_t* abb;
    pila_t* pila;
};

/* ******************************************************************
 *                    PRIMITIVAS PRIVADAS
 * *****************************************************************/

char *strdup(const char *clave){
    char* copia = malloc(strlen(clave)+1);
    if(!copia) return NULL;
    strcpy(copia, clave);
    return copia;
}

nodo_t* crear_nodo(const char* clave, void* dato){

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if(!nodo_nuevo) return NULL;

    nodo_nuevo->izq = NULL;
    nodo_nuevo->der = NULL;
    nodo_nuevo->clave = strdup(clave);
    nodo_nuevo->dato = dato;

    return nodo_nuevo;

}

nodo_t** buscar_espacio(nodo_t** p_nodo, const char* clave, abb_comparar_clave_t funcion_comparar){

    nodo_t* nodo = *p_nodo;

    if(!nodo || funcion_comparar(nodo->clave, clave) == 0){
        return p_nodo;
    }
    else if(funcion_comparar(nodo->clave, clave) > 0){
        return buscar_espacio(&(nodo->izq), clave, funcion_comparar);
    }
    else{
        return buscar_espacio(&(nodo->der), clave, funcion_comparar);
    }

}

size_t cant_hijos(nodo_t* nodo){

    if(nodo->der && nodo->izq){
        return DOS_HIJOS;
    }
    else if((!nodo->der && nodo->izq) || (nodo->der && !nodo->izq)){
        return UN_HIJO;
    }
    else{
        return SIN_HIJOS;
    }

}

void destruir_nodo(abb_destruir_dato_t funcion_destruir, nodo_t* nodo){
    if(funcion_destruir != NULL)
        funcion_destruir(nodo->dato);
    free(nodo->clave);
    free(nodo);
}

void* borrar_hoja(nodo_t** p_nodo, abb_destruir_dato_t funcion_destruir){

    nodo_t* nodo = *p_nodo;
    void* dato = nodo->dato;
    destruir_nodo(funcion_destruir, nodo);
    *p_nodo = NULL;
    return dato;

}

void* borrar_un_hijo(nodo_t** p_nodo, abb_destruir_dato_t funcion_destruir){

    nodo_t* nodo = *p_nodo;
    void* dato = nodo->dato;
    nodo_t* nuevo_hijo = NULL;

    if(!nodo->izq && nodo->der){
        nuevo_hijo = nodo->der;
    }
    else{
        nuevo_hijo = nodo->izq;
    }

    destruir_nodo(funcion_destruir, nodo);
    *p_nodo = nuevo_hijo;
    return dato;

}

void* borrar_dos_hijos(nodo_t** p_nodo, abb_t* arbol){

    nodo_t* nodo_a_borrar = *p_nodo;
    void* dato = nodo_a_borrar->dato;
    nodo_t* reemplazante;

    reemplazante = nodo_a_borrar->der;

    while(reemplazante->izq != NULL){
        reemplazante = reemplazante->izq;
    }
    char* clave_reemplazante = strdup(reemplazante->clave);
    void* dato_reemplazante = abb_borrar(arbol, reemplazante->clave);
    arbol->cantidad++;

    if(arbol->funcion_destruir != NULL){
        arbol->funcion_destruir(nodo_a_borrar->dato);
    }
    nodo_a_borrar->dato = dato_reemplazante;
    free(nodo_a_borrar->clave);
    nodo_a_borrar->clave = clave_reemplazante;

    return dato;

}

void destruir_post_order(nodo_t* nodo, abb_destruir_dato_t funcion_destruir){

    if(!nodo) return;
    destruir_post_order(nodo->izq, funcion_destruir);
    destruir_post_order(nodo->der, funcion_destruir);
    destruir_nodo(funcion_destruir, nodo);

}

bool apilar_rama_izquierda(pila_t* pila, nodo_t* nodo){

    while(nodo){
        if(!pila_apilar(pila, nodo)) return false;
        nodo = nodo->izq;
    }

    return true;

}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;
    abb->cantidad = 0;
    abb->raiz = NULL;
    abb->funcion_comparar = cmp;
    abb->funcion_destruir = destruir_dato;
    return abb;

}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato){

    nodo_t** p_nodo = buscar_espacio(&(arbol->raiz), clave, arbol->funcion_comparar);
    nodo_t* nodo = *p_nodo;

    if(nodo){
        if(arbol->funcion_destruir != NULL){
            arbol->funcion_destruir(nodo->dato);
        }
        nodo->dato = dato;
        return true;
    }

    nodo = crear_nodo(clave, dato);
    if(!nodo) return false;

    *p_nodo = nodo;
    arbol->cantidad++;
    return true;

}

void* abb_borrar(abb_t* arbol, const char* clave){

    nodo_t** p_nodo = buscar_espacio(&(arbol->raiz), clave, arbol->funcion_comparar);
    nodo_t* nodo = *p_nodo;
    if (!nodo) return NULL;
    void* dato = NULL;

    size_t hijos = cant_hijos(nodo);

    switch(hijos){
        case SIN_HIJOS:
            dato = borrar_hoja(p_nodo, arbol->funcion_destruir);
            break;
        case UN_HIJO:
            dato = borrar_un_hijo(p_nodo, arbol->funcion_destruir);
            break;
        case DOS_HIJOS:
            dato = borrar_dos_hijos(p_nodo, arbol);
            break;
    }

    arbol->cantidad--;
    return dato;

}

void* abb_obtener(const abb_t* arbol, const char* clave){
    nodo_t* raiz = arbol->raiz;
    nodo_t* nodo = *(buscar_espacio(&raiz, clave, arbol->funcion_comparar));
    if(!nodo) return NULL;
    return nodo->dato;
}

bool abb_pertenece(const abb_t* arbol, const char* clave){
    nodo_t* raiz = arbol->raiz;
    return *(buscar_espacio(&raiz, clave, arbol->funcion_comparar)) != NULL;
}

size_t abb_cantidad(abb_t* arbol){
    return arbol->cantidad;
}

void abb_destruir(abb_t* arbol){
    destruir_post_order(arbol->raiz, arbol->funcion_destruir);
    free(arbol);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t* abb_iter_in_crear(const abb_t* arbol){

    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;

    pila_t* pila = pila_crear();
    if(!pila){
        free(iter);
        return NULL;
    }
    
    if(!apilar_rama_izquierda(pila, arbol->raiz)){
        pila_destruir(pila);
        free(iter);
        return NULL;
    }

    iter->pila = pila;
    iter->abb = arbol;
    return iter;

}

bool abb_iter_in_avanzar(abb_iter_t* iter){
    if(abb_iter_in_al_final(iter)) return false;
    nodo_t* aux = pila_desapilar(iter->pila);
    return apilar_rama_izquierda(iter->pila, aux->der);
}

const char* abb_iter_in_ver_actual(const abb_iter_t* iter){
    if(abb_iter_in_al_final(iter)) return NULL;
    nodo_t* aux = pila_ver_tope(iter->pila);
    return aux->clave;
}

bool abb_iter_in_al_final(const abb_iter_t* iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

bool abb_in_order_(nodo_t* nodo, bool visitar(const char*, void*, void*), void* extra){

    if(!nodo) return true;
    if(!abb_in_order_(nodo->izq, visitar, extra)){
        return false;
    }
    if(!visitar(nodo->clave, nodo->dato, extra)){
        return false;
    }
    return abb_in_order_(nodo->der, visitar, extra);

}

void abb_in_order(abb_t* arbol, bool visitar(const char*, void*, void*), void* extra){
    abb_in_order_(arbol->raiz, visitar, extra);
}