#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define PRUEBA_VOLUMEN_TAMANIO 10000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_cola_vacia(){

    printf("\nINICIO DE PRUEBAS CON UNA COLA VACIA:\n");

    // Se puede crear correctamente la estructura.
    cola_t* cola_test = cola_crear();
    print_test("Se creo una estructura de tipo cola", cola_test != NULL);

    // La acción de esta_vacía en una cola recién creada es verdadero.
    print_test("Cola esta vacia", cola_esta_vacia(cola_test));

    // La accion de desencolar en una cola recién creada es inválida.
    print_test("Desencolar retorna NULL", cola_desencolar(cola_test) == NULL);

    // La accion de ver_primero en una cola recién creada es inválida.
    print_test("Cola ver primero retorna NULL", cola_ver_primero(cola_test) == NULL);

    // Se puede destruir correctamente la estructura.
    cola_destruir(cola_test, NULL);
    print_test("Se destruyo la cola", true);

}

void pruebas_cola_algunos_elementos(){

    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS:\n");

    // Creo la estructura para las pruebas.
    cola_t* cola_test = cola_crear();

    // Encolamiento del elemento NULL es valido.
    print_test("Encolo NULL", cola_encolar(cola_test, NULL));
    print_test("Cola no esta vacia", !cola_esta_vacia(cola_test));

    // Desencolo el elemento NULL para proseguir con las pruebas posteriores.
    print_test("Desencolo y obtengo NULL", cola_desencolar(cola_test) == NULL);
    print_test("Cola esta vacia", cola_esta_vacia(cola_test));

    // Compruebo que al encolar y desencolar el variante de la cola se mantenga.
    char a = 'A';
    char b = 'B';
    char c = 'C';
    print_test("Encolo...", cola_encolar(cola_test, &a));
    print_test("Encolo...", cola_encolar(cola_test, &b));
    print_test("Encolo...", cola_encolar(cola_test, &c));
    print_test("Cola no esta vacia", !cola_esta_vacia(cola_test));
    print_test("Al desencolar se mantiene el invariante y me devuelve 'a'", cola_desencolar(cola_test) == &a);
    print_test("Al desencolar se mantiene el invariante y me devuelve 'b'", cola_desencolar(cola_test) == &b);
    print_test("Al desencolar se mantiene el invariante y me devuelve 'c'", cola_desencolar(cola_test) == &c);

    // Al encolar y desencolar una cola hasta que este vacia esta se comporta como recien creada, es decir, desencolar, ver_primero y esta_vacia dan los valores adecuados.
    int ejemplo1 = 1;
    char ejemplo2 = 'b';
    print_test("Encolo...", cola_encolar(cola_test, &ejemplo1));
    print_test("Encolo...", cola_encolar(cola_test, &ejemplo2));
    print_test("Desencolo...", cola_desencolar(cola_test) == &ejemplo1);
    print_test("Desencolo...", cola_desencolar(cola_test) == &ejemplo2);
    print_test("Chequeo si la cola esta vacia", cola_esta_vacia(cola_test));
    print_test("Intentar desencolar una cola vacia es invalido", cola_desencolar(cola_test) == NULL);
    print_test("Intentar ver primero de una cola vacia es invalido", cola_ver_primero(cola_test) == NULL);

    // Destruyo la cola luego de terminar las pruebas en este bloque.
    cola_destruir(cola_test, NULL);

}

void pruebas_cola_volumen(int tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN:\n");

    /* Prueba de volumen: Se pueden encolar muchos elementos y hacer crecer la cola hasta un valor sabido mucho mayor 
    que el tamaño inicial, y desencolar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. */

    cola_t* cola_test = cola_crear();
    int vector[tamanio];
    bool check_encolar = true;
    bool check_desencolar = true;

    for(int i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(int i = 0; i < tamanio; i++){
        if(!cola_encolar(cola_test, &vector[i])){
            check_encolar = false;
            break;
        }
    }

    print_test("Se encolaron con exito los elementos", check_encolar);

    for(int i = 0; i < tamanio; i++){
        if(cola_desencolar(cola_test) != &vector[i]){
            check_desencolar = false;
            break;
        }
    }

    print_test("Se desencolaron con exito los elementos y se mantuvo correctamente su invariante", check_desencolar);

    // Destruyo la cola luego de terminar las pruebas en este bloque.
    cola_destruir(cola_test, NULL);

}

void pila_destruir_wrapper(void* pila){
    pila_destruir((pila_t*) pila);
}

void pruebas_cola_destruccion(){

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION:\n");

    // Creo la estructura para la prueba estatica.
    cola_t* cola_test_estatica = cola_crear();

    // Prueba de destruccion con valor estatico.
    int valor_estatico = 69;
    print_test("Encolo...", cola_encolar(cola_test_estatica, &valor_estatico));
    cola_destruir(cola_test_estatica, NULL);
    print_test("Se destruyo el valor estatico", true);

    // Creo la estructura para la prueba dinamica.
    cola_t* cola_test_dinamica = cola_crear();

    // Prueba de destruccion con valor dinamico.
    void* valor_dinamico = malloc(sizeof(void*));
    print_test("Encolo...", cola_encolar(cola_test_dinamica, valor_dinamico));
    cola_destruir(cola_test_dinamica, free);
    print_test("Se destruyo el valor dinamico", true);

    // Creo las estructuras para la prueba con estructura.
    cola_t* cola_test_estructura = cola_crear();
    pila_t* pila_test = pila_crear();

    // Prueba de destruccion con estructura.
    int elemento_pila = 5;
    print_test("Apilo un elemento", pila_apilar(pila_test, &elemento_pila));
    print_test("Encolo la pila", cola_encolar(cola_test_estructura, pila_test));
    cola_destruir(cola_test_estructura, pila_destruir_wrapper);
    print_test("Se destruyo la estructura pila en la cola", true);

}

void pruebas_cola_alumno(void){

    pruebas_cola_vacia();
    pruebas_cola_algunos_elementos();
    pruebas_cola_volumen(PRUEBA_VOLUMEN_TAMANIO);
    pruebas_cola_destruccion();

}