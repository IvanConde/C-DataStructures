#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define PRUEBA_VOLUMEN_TAMANIO 10000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_primitivas_lista_vacia(){

    printf("\nINICIO DE PRUEBAS CON UNA LISTA VACIA:\n");

    // Se puede crear correctamente la estructura.
    lista_t* lista_test = lista_crear();

    // Lista esta vacia en una lista recien creada es verdadero.
    print_test("Lista esta vacia", lista_esta_vacia(lista_test));

    // Borrar primero en una lista vacia devuelve NULL i/o es invalido.
    print_test("Borrar primero es invalido", lista_borrar_primero(lista_test) == NULL);

    // Ver primer elemento de la lista vacia es invalido.
    print_test("Ver primer elemento es invalido", lista_ver_primero(lista_test) == NULL);

    // Ver ultimo elemento de la lista vacia es invalido.
    print_test("Ver ultimo elemento es invalido", lista_ver_ultimo(lista_test) == NULL);

    // Se puede destruir correctamente la estructura.
    lista_destruir(lista_test, NULL);
    print_test("Se destruyo la lista", true);

}

void pruebas_primitivas_lista_algunos_elementos(){

    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS:\n");

    // Se puede crear correctamente la estructura.
    lista_t* lista_test = lista_crear();

    // Listar el elemento NULL es valido.
    print_test("Insertar NULL a la lista es valido", lista_insertar_primero(lista_test, NULL));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));

    // Quito el elemento NULL para proseguir con las pruebas posteriores.
    print_test("Obtengo NULL al quitarlo de la lista", lista_borrar_primero(lista_test) == NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista_test));

    // Compruebo que al añadir elementos con insertar_ultimo y borrar_primero el invariante de la lista es el correcto.
    char a = 'A';
    char b = 'B';
    char c = 'C';
    print_test("Añado...", lista_insertar_ultimo(lista_test, &a));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &b));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &c));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));
    print_test("Al borrar se mantiene el invariante y me devuelve 'a'", lista_borrar_primero(lista_test) == &a);
    print_test("Al borrar se mantiene el invariante y me devuelve 'b'", lista_borrar_primero(lista_test) == &b);
    print_test("Al borrar se mantiene el invariante y me devuelve 'c'", lista_borrar_primero(lista_test) == &c);

    // Compruebo que al añadir elementos con insertar_primero y borrar_primero el invariante de la lista es el correcto.
    char d = 'D';
    char e = 'E';
    char f = 'F';
    print_test("Añado...", lista_insertar_primero(lista_test, &d));
    print_test("Añado...", lista_insertar_primero(lista_test, &e));
    print_test("Añado...", lista_insertar_primero(lista_test, &f));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));
    print_test("Al borrar se mantiene el invariante y me devuelve 'f'", lista_borrar_primero(lista_test) == &f);
    print_test("Al borrar se mantiene el invariante y me devuelve 'e'", lista_borrar_primero(lista_test) == &e);
    print_test("Al borrar se mantiene el invariante y me devuelve 'd'", lista_borrar_primero(lista_test) == &d);

    // Al añadir y quitar elementos a una lista hasta que este vacia esta se comporta como recien creada, es decir, borrar, ver_primero, ver_ultimo y esta_vacia dan los valores adecuados.
    int ejemplo1 = 1;
    char ejemplo2 = 'b';
    print_test("Añado...", lista_insertar_ultimo(lista_test, &ejemplo1));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &ejemplo2));
    print_test("Borro...", lista_borrar_primero(lista_test) == &ejemplo1);
    print_test("Borro...", lista_borrar_primero(lista_test) == &ejemplo2);
    print_test("Chequeo si la lista esta vacia", lista_esta_vacia(lista_test));
    print_test("Intentar borrar en una lista vacia es invalido", lista_borrar_primero(lista_test) == NULL);
    print_test("Intentar ver primero en lista vacia es invalido", lista_ver_primero(lista_test) == NULL);
    print_test("Intentar ver ultimo en lista vacia es invalido", lista_ver_ultimo(lista_test) == NULL);

    // Destruyo la lista luego de terminar las pruebas en este bloque.
    lista_destruir(lista_test, NULL);

}

void pruebas_primitivas_lista_volumen(int tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN:\n");

    /* Prueba de volumen: Se pueden insertar muchos elementos y hacer crecer la lista hasta un valor sabido mucho mayor 
    que el tamaño inicial, y borrar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. */

    lista_t* lista_test = lista_crear();
    int vector[tamanio];
    bool check_insertar = true;
    bool check_borrar = true;

    for(int i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(int i = 0; i < tamanio; i++){
        if((!lista_insertar_ultimo(lista_test, &vector[i])) && (lista_ver_ultimo(lista_test) != &vector[i])){
            check_insertar = false;
            break;
        }
    }

    print_test("Se insertaron con exito los elementos", check_insertar);

    for(int i = 0; i < tamanio; i++){
        if(lista_borrar_primero(lista_test) != &vector[i]){
            check_borrar = false;
            break;
        }
    }

    print_test("Se borraron con exito los elementos y se mantuvo correctamente su invariante", check_borrar);

    // Destruyo la lista luego de terminar las pruebas en este bloque.
    lista_destruir(lista_test, NULL);

}

void pila_destruir_wrapper(void* pila){
    pila_destruir((pila_t*) pila);
}

void pruebas_lista_destruccion(){

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION:\n");

    // Creo la estructura para la prueba estatica.
    lista_t* lista_test_estatica = lista_crear();

    // Prueba de destruccion con valor estatico.
    int valor_estatico = 69;
    print_test("Añado...", lista_insertar_ultimo(lista_test_estatica, &valor_estatico));
    lista_destruir(lista_test_estatica, NULL);
    print_test("Se destruyo el valor estatico", true);

    // Creo la estructura para la prueba dinamica.
    lista_t* lista_test_dinamica = lista_crear();

    // Prueba de destruccion con valor dinamico.
    void* valor_dinamico = malloc(sizeof(void*));
    print_test("Creo el valor dinamico para la prueba...", valor_dinamico);
    print_test("Añado...", lista_insertar_ultimo(lista_test_dinamica, valor_dinamico));
    lista_destruir(lista_test_dinamica, free);
    print_test("Se destruyo el valor dinamico", true);

    // Creo las estructuras para la prueba con estructura.
    lista_t* lista_test_estructura = lista_crear();
    pila_t* pila_test = pila_crear();

    // Prueba de destruccion con estructura.
    int elemento_pila = 5;
    print_test("Apilo un elemento", pila_apilar(pila_test, &elemento_pila));
    print_test("Añado la pila", lista_insertar_ultimo(lista_test_estructura, pila_test));
    lista_destruir(lista_test_estructura, pila_destruir_wrapper);
    print_test("Se destruyo la estructura pila en la cola", true);

}

void pruebas_iterador_externo_lista_vacia(){

    printf("\nINICIO DE PRUEBAS ITERADOR EXTERNO CON UNA LISTA VACIA:\n");

    // Se puede crear correctamente la estructura.
    lista_t* lista_test = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista_test);

    // Avanzar el iterador en una lista vacia es falso.
    print_test("Avanzar iterador es invalido", !lista_iter_avanzar(iterador));

    // Borrar primero en una lista vacia devuelve NULL i/o es invalido.
    print_test("Ver primero es invalido", lista_iter_ver_actual(iterador) == NULL);

    // Borrar lista vacia es NULO.
    print_test("Borrar es invalido", lista_iter_borrar(iterador) == NULL);

    // Lista esta al final devuelve NULO..
    print_test("Ver final es invalido", lista_iter_al_final(iterador));

    // Se puede destruir correctamente la estructura.
    lista_iter_destruir(iterador);
    lista_destruir(lista_test, NULL);
    print_test("Se destruyo la lista y el iterador", true);

}

void pruebas_iterador_externo_lista_algunos_elementos(){

    printf("\nINICIO DE PRUEBAS ITERADOR EXTERNO CON ALGUNOS ELEMENTOS:\n");

    // Se puede crear correctamente la estructura.
    lista_t* lista_test = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista_test);

    // Insertar el elemento NULL es valido.
    print_test("Insertar NULL a la lista es valido", lista_iter_insertar(iterador, NULL));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));

    // Borro el elemento NULL para proseguir con las pruebas posteriores.
    print_test("Obtengo NULL al quitarlo de la lista", lista_iter_borrar(iterador) == NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista_test));

    // Compruebo que al añadir elementos con insertar y borrar el invariante de la lista es el correcto.
    char a = 'A';
    char b = 'B';
    char c = 'C';
    print_test("Añado...", lista_iter_insertar(iterador, &a));
    print_test("Añado...", lista_iter_insertar(iterador, &b));
    print_test("Añado...", lista_iter_insertar(iterador, &c));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));
    print_test("Al borrar se mantiene el invariante y me devuelve 'a'", lista_iter_borrar(iterador) == &c);
    print_test("Al borrar se mantiene el invariante y me devuelve 'b'", lista_iter_borrar(iterador) == &b);
    print_test("Al borrar se mantiene el invariante y me devuelve 'c'", lista_iter_borrar(iterador) == &a);

    // Al añadir y quitar elementos a una lista hasta que este vacia esta se comporta como recien creada.
    int ejemplo1 = 1;
    char ejemplo2 = 'b';
    print_test("Añado...", lista_iter_insertar(iterador, &ejemplo1));
    print_test("Añado...", lista_iter_insertar(iterador, &ejemplo2));
    print_test("Borro...", lista_iter_borrar(iterador) == &ejemplo2);
    print_test("Borro...", lista_iter_borrar(iterador) == &ejemplo1);
    print_test("Chequeo si la lista esta vacia", !lista_iter_avanzar(iterador));
    print_test("Intentar borrar en una lista vacia es invalido", lista_iter_ver_actual(iterador) == NULL);
    print_test("Intentar ver primero en lista vacia es invalido", lista_iter_al_final(iterador));
    print_test("Intentar ver ultimo en lista vacia es invalido", lista_iter_borrar(iterador) == NULL);

    // Destruyo la lista y el iterador luego de terminar las pruebas en este bloque.
    lista_iter_destruir(iterador);
    lista_destruir(lista_test, NULL);

}

void pruebas_iterador_externo_lista_casos_borde(){

    printf("\nINICIO DE PRUEBAS ITERADOR EXTERNO CASOS BORDE:\n");

    // Se puede crear correctamente la estructura.
    lista_t* lista_test = lista_crear();

    char a = 'A';
    char b = 'B';
    char c = 'C';
    print_test("Añado...", lista_insertar_ultimo(lista_test, &a));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &b));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &c));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));

    // Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.
    // Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.
    // Insertar un elemento en el medio se hace en la posición correcta
    // Verificar que al remover un elemento del medio, este no está.
    // Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.
    // Remover el último elemento con el iterador cambia el último de la lista.

    lista_iter_t* iterador = lista_iter_crear(lista_test);
    char d = 'D';

    print_test("Se crea iterador", iterador);
    print_test("Inserto elemento en la posicion del iterador", lista_iter_insertar(iterador, &d));
    print_test("Elemento esta al principio", lista_ver_primero(lista_test) == &d);

    print_test("Borro elemento", lista_iter_borrar(iterador));
    print_test("Primero cambia correctamente al remover en la posicion inicial del iterador", lista_ver_primero(lista_test) == &a);

    print_test("Avanzo iterador al medio", lista_iter_avanzar(iterador));
    print_test("Estoy en el medio", lista_iter_ver_actual(iterador) == &b);
    print_test("Inserto en el medio", lista_iter_insertar(iterador, &d));
    print_test("Cursor esta en la posicion correcta", lista_iter_ver_actual(iterador) == &d);
    print_test("Avanzo iterador y verifico siguiente", lista_iter_avanzar(iterador));
    print_test("El elemento siguiente es el correcto", lista_iter_ver_actual(iterador) == &b);

    print_test("Borro en el medio", lista_iter_borrar(iterador) == &b);
    print_test("El cursor cambio al valor correcto", lista_iter_ver_actual(iterador) == &c);
    print_test("La cantidad de elementos es la correcta, es decir el elemento eliminado ya no esta", lista_largo(lista_test) == 3);

    print_test("Avanzo iterador al final de la lista", lista_iter_avanzar(iterador));
    print_test("Inserto al final", lista_iter_insertar(iterador, &d));
    print_test("Elemento se inserto al final", lista_ver_ultimo(lista_test) == &d);
    print_test("La cantidad de elementos es la correcta", lista_largo(lista_test) == 4);

    print_test("Borro el ultimo elemento", lista_iter_borrar(iterador) == &d);
    print_test("El nuevo ultimo es el correcto", lista_ver_ultimo(lista_test) == &c);

    // Destruyo la lista y el iterador luego de terminar las pruebas en este bloque.
    lista_iter_destruir(iterador);
    lista_destruir(lista_test, NULL);

}

void pruebas_iterador_externo_lista_volumen(int tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN ITERADOR EXTERNO:\n");

    /* Prueba de volumen: Se pueden insertar muchos elementos y hacer crecer la lista hasta un valor sabido mucho mayor 
    que el tamaño inicial, y borrar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. */

    lista_t* lista_test = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista_test);
    int vector[tamanio];
    bool check_insertar = true;
    bool check_borrar = true;

    for(int i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(int i = 0; i < tamanio; i++){
        if(!lista_iter_insertar(iterador, &vector[i])){
            check_insertar = false;
            break;
        }
    }

    print_test("Se insertaron con exito los elementos", check_insertar);

    for(int i = 0; i < tamanio; i++){
        if(lista_iter_borrar(iterador) != &vector[PRUEBA_VOLUMEN_TAMANIO-1-i]){
            check_borrar = false;
            break;
        }
    }

    print_test("Se borraron con exito los elementos y se mantuvo correctamente su invariante", check_borrar);

    // Destruyo la lista y el iterador luego de terminar las pruebas en este bloque.
    lista_iter_destruir(iterador);
    lista_destruir(lista_test, NULL);

}

bool cantidad_elementos(void* dato, void* extra){

    *(size_t*) extra += 1;
    return true;

}

bool primeros_dos(void* dato, void* extra){

    if (*(size_t*) extra >= 2) return false;
    *(size_t*) extra += 1;
    return true;

}

void pruebas_iterador_interno(){

    printf("\nINICIO DE PRUEBAS ITERADOR INTERNO:\n");

    lista_t* lista_test = lista_crear();
    char a = 'A';
    char b = 'B';
    char c = 'C';
    size_t contador = 0;
    
    print_test("Añado...", lista_insertar_ultimo(lista_test, &a));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &b));
    print_test("Añado...", lista_insertar_ultimo(lista_test, &c));
    print_test("Lista no esta vacia", !lista_esta_vacia(lista_test));
    lista_iterar(lista_test, cantidad_elementos, &contador);
    print_test("Con extra, Sin corte, Se contaron 3 elementos", contador == 3);
    contador = 0;
    lista_iterar(lista_test, primeros_dos, &contador);    
    print_test("Con extra, con corte, Se contaron 2 elementos", contador == 2);

    // Destruyo la lista luego de terminar las pruebas en este bloque.
    lista_destruir(lista_test, NULL);

}

void pruebas_iterador_interno_volumen(int tamanio){

    printf("\nINICIO DE PRUEBAS ITERADOR INTERNO VOLUMEN:\n");

    lista_t* lista_test = lista_crear();
    int vector[tamanio];
    bool check_insertar = true;
    size_t contador = 0;

    for(int i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(int i = 0; i < tamanio; i++){
        if((!lista_insertar_ultimo(lista_test, &vector[i])) && (lista_ver_ultimo(lista_test) != &vector[i])){
            check_insertar = false;
            break;
        }
    }

    print_test("Se insertaron con exito los elementos para la prueba...", check_insertar);

    lista_iterar(lista_test, cantidad_elementos, &contador);

    print_test("La funcion iterar termino normalmente y la cantidad de elementos es la correcta", contador == tamanio);

    // Destruyo la lista luego de terminar las pruebas en este bloque.
    lista_destruir(lista_test, NULL);

}

void pruebas_lista_alumno(void){

    pruebas_primitivas_lista_vacia();
    pruebas_primitivas_lista_algunos_elementos();
    pruebas_primitivas_lista_volumen(PRUEBA_VOLUMEN_TAMANIO);
    pruebas_lista_destruccion();
    pruebas_iterador_externo_lista_vacia();
    pruebas_iterador_externo_lista_algunos_elementos();
    pruebas_iterador_externo_lista_casos_borde();
    pruebas_iterador_externo_lista_volumen(PRUEBA_VOLUMEN_TAMANIO);
    pruebas_iterador_interno();
    pruebas_iterador_interno_volumen(PRUEBA_VOLUMEN_TAMANIO);

}