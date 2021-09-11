#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define VECTOR_VOLUMEN_TAMANIO 10000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_vacia(){

    printf("\nINICIO DE PRUEBAS CON PILA VACIA:\n");

    // Se puede crear correctamente la estructura.
    pila_t* pila_test = pila_crear();
    print_test("Se creo una pila", pila_test != NULL);

    // Condición de borde: la acción de esta_vacía en una pila recién creada es verdadero.
    print_test("Pila esta vacia", pila_esta_vacia(pila_test));

    // Condición de borde: la accion de desapilar en una pila recién creada es inválida.
    print_test("Desapilar pila vacia", pila_desapilar(pila_test) == NULL);

    // Condición de borde: la accion de ver_tope en una pila recién creada es inválida.
    print_test("Tope de pila recien creada es nulo", pila_ver_tope(pila_test) == NULL);

    // Se puede destruir correctamente la estructura.
    pila_destruir(pila_test);
    print_test("Se destruyo la pila", true);

}

void pruebas_pila_algunos_elementos(){

    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS:\n");

    // Creo una estructura pila para las pruebas.
    pila_t* pila_test = pila_crear();

    // Apilo del elemento NULL es valido.
    print_test("Apilo NULL", pila_apilar(pila_test, NULL));
    print_test("Pila no esta vacia", !pila_esta_vacia(pila_test));

    // Desapilo el elemento NULL para proseguir con las pruebas posteriores.
    print_test("Desapilo y obtengo NULL", pila_desapilar(pila_test) == NULL);
    print_test("Pila esta vacia", pila_esta_vacia(pila_test));

    // Al apilar y desapilar una pila hasta que este vacia esta se comporta como recien creada, es decir, desapilar, ver_tope y esta_vacia dan los valores adecuados.
    int ejemplo1 = 1;
    char ejemplo2 = 'b';
    print_test("Apilo...", pila_apilar(pila_test, &ejemplo1));
    print_test("Apilo...", pila_apilar(pila_test, &ejemplo2));
    print_test("Desapilo...", pila_desapilar(pila_test) == &ejemplo2);
    print_test("Desapilo...", pila_desapilar(pila_test) == &ejemplo1);
    print_test("Chequeo si la pila esta vacia", pila_esta_vacia(pila_test));
    print_test("Intentar desapilar una pila vacia es invalido", pila_desapilar(pila_test) == NULL);
    print_test("Intentar ver tope de una pila vacia es invalido", pila_ver_tope(pila_test) == NULL);

    // Compruebo que al apilar y desapilar el variante de la pila se mantenga.
    char a = 'A';
    char b = 'B';
    char c = 'C';
    print_test("Apilo...", pila_apilar(pila_test, &a));
    print_test("Apilo...", pila_apilar(pila_test, &b));
    print_test("Apilo...", pila_apilar(pila_test, &c));
    print_test("Pila no esta vacia", !pila_esta_vacia(pila_test));
    print_test("Al desapilar se mantiene el invariante y me devuelve 'c'", pila_desapilar(pila_test) == &c);
    print_test("Al desapilar se mantiene el invariante y me devuelve 'b'", pila_desapilar(pila_test) == &b);
    print_test("Al desapilar se mantiene el invariante y me devuelve 'a'", pila_desapilar(pila_test) == &a);

    // Destruyo la pila luego de terminar las pruebas en este bloque.
    pila_destruir(pila_test);

}

void pruebas_pila_volumen(int tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN:\n");

    /* Prueba de volumen: Se pueden apilar muchos elementos (10000 elementos) y hacer crecer la pila hasta un valor sabido mucho mayor 
    que el tamaño inicial, y desapilar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. */

    pila_t* pila_test = pila_crear();
    int vector[tamanio];
    bool apilar = true;
    bool apilar_invariante = true;
    bool desapilar_invariante = true;
    bool desapilar = true;
    void* tope_actual;
    void* tope_desapilar;

    for(int i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(int i = 0; i < tamanio; i++){
        apilar = pila_apilar(pila_test, &vector[i]);
        if(!apilar){
            apilar_invariante = false;
            break;
        }
        if(pila_ver_tope(pila_test) != &vector[i]){
            apilar_invariante = false;
            break;
        }
    }

    print_test("Los 10000 elementos se apilaron con exito", apilar);
    print_test("La invariante al apilar se conserva", apilar_invariante);

    for(int i = 0; i < tamanio; i++){
        if(pila_ver_tope(pila_test) != &vector[tamanio-1-i]){
            desapilar_invariante = false;
            desapilar = false;
            break;
        }
        tope_actual = pila_ver_tope(pila_test);
        tope_desapilar = pila_desapilar(pila_test);
        if(tope_actual != tope_desapilar){
            desapilar = false;
            desapilar_invariante = false;
            break;
        }
    }

    print_test("El desapilado de los 10000 elementos fue realizado con exito", desapilar);
    print_test("La invariante al desapilar se conserva", desapilar_invariante);

    // Destruyo la pila luego de terminar las pruebas en este bloque.
    pila_destruir(pila_test);

}

void pruebas_pila_alumno(){

    pruebas_pila_vacia();
    pruebas_pila_algunos_elementos();
    pruebas_pila_volumen(VECTOR_VOLUMEN_TAMANIO);

}