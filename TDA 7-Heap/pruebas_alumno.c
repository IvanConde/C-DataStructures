#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"

#define PRUEBA_VOLUMEN_TAMANIO 5000
#define PRUEBA_ARR_TAMANIO 100

int intcmp(const void* a, const void* b){
    int* a_entero = (int*)a;
    int* b_entero = (int*)b;
    if(*a_entero > *b_entero) return 1;
    else if(*a_entero == *b_entero) return 0;
    else return (-1);
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_heap_vacio(){

    printf("\nINICIO DE PRUEBAS CON HEAP VACIO\n");

    // Creo la estructura para iniciar las pruebas.
    heap_t* heap = heap_crear(intcmp);

    // Diversas pruebas con un heap vacio.
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    print_test("Desencolar un heap vacio devuelve NULL", heap_desencolar(heap) == NULL);
    print_test("Ver maximo en un heap vacio devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Cantidad en un heap es 0", heap_cantidad(heap) == 0);

    // Destruyo la estructura para proseguir en las pruebas.
    heap_destruir(heap, NULL);

}

void pruebas_heap_null(){

    printf("\nINICIO DE PRUEBAS CON ELEMENTO NULL\n");

    // Creo la estructura para iniciar las pruebas.
    heap_t* heap = heap_crear(intcmp);

    // Diversas pruebas con un heap conteniendo un elemento NULL.
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    print_test("Encolo elemento NULL...", heap_encolar(heap, NULL));
    print_test("Heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Cantidad es 1", heap_cantidad(heap) == 1);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap) == NULL);
    print_test("Heap esta vacio", heap_esta_vacio(heap));

    // Destruyo la estructura para proseguir en las pruebas.
    heap_destruir(heap, NULL);

}

void pruebas_heap_algunos_elementos(){

    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    // Creo la estructura para iniciar las pruebas.
    heap_t* heap = heap_crear(intcmp);

    // Inicializo 3 elementos diferentes para los test.
    int a = 24;
    int b = 6;
    int c = 1024;

    // Diversas pruebas algunos elementos.
    print_test("Encolo 'a'...", heap_encolar(heap, &a));
    print_test("Encolo 'b'...", heap_encolar(heap, &b));
    print_test("Encolo 'c'...", heap_encolar(heap, &c));
    print_test("Heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Ver maximo devuelve 'c'", heap_ver_max(heap) == &c);
    print_test("Cantidad es 3", heap_cantidad(heap) == 3);
    print_test("Desencolar devuelve 'c'", heap_desencolar(heap) == &c);
    print_test("Cantidad es 2", heap_cantidad(heap) == 2);
    print_test("Ver maximo devuelve 'a'", heap_ver_max(heap) == &a);
    print_test("Desencolar devuelve 'a'", heap_desencolar(heap) == &a);
    print_test("Cantidad es 1", heap_cantidad(heap) == 1);
    print_test("Ver maximo devuelve 'b'", heap_ver_max(heap) == &b);
    print_test("Desencolar devuelve 'b'", heap_desencolar(heap) == &b);

    // El heap ahora se comporta como vacio.
    print_test("Cantidad es 0", heap_cantidad(heap) == 0);
    print_test("Heap esta vacio", heap_esta_vacio(heap));
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

    // Destruyo la estructura para proseguir en las pruebas.
    heap_destruir(heap, NULL);

}

void pruebas_heap_destruccion(){

    printf("\nINICIO DE PRUEBAS DE DESTRUCCION:\n");

    // Creo la estructura para la prueba estatica.
    heap_t* heap_estatico = heap_crear(intcmp);

    // Prueba de destruccion con valor estatico.
    int valor_estatico1 = 69;
    int valor_estatico2 = 2;
    int valor_estatico3 = 6;
    
    print_test("Añado...", heap_encolar(heap_estatico, &valor_estatico1));
    print_test("Añado...", heap_encolar(heap_estatico, &valor_estatico2));
    print_test("Añado...", heap_encolar(heap_estatico, &valor_estatico3));
    
    heap_destruir(heap_estatico, NULL);
    print_test("Se destruyeron los valores estaticos", true);

    // Creo la estructura para la prueba dinamica.
    heap_t* heap_dinamico = heap_crear(intcmp);

    // Prueba de destruccion con valor dinamico.
    int* valor_dinamico1 = malloc(sizeof(int*));
    int* valor_dinamico2 = malloc(sizeof(int*));
    int* valor_dinamico3 = malloc(sizeof(int*));
    *valor_dinamico1 = 14;
    *valor_dinamico2 = 1;
    *valor_dinamico3 = 15;
    
    print_test("Se creo un valor dinamico...", valor_dinamico1);
    print_test("Se creo un valor dinamico...", valor_dinamico2);
    print_test("Se creo un valor dinamico...", valor_dinamico3);
    print_test("Añado...", heap_encolar(heap_dinamico, valor_dinamico1));
    print_test("Añado...", heap_encolar(heap_dinamico, valor_dinamico2));
    print_test("Añado...", heap_encolar(heap_dinamico, valor_dinamico3));
    
    heap_destruir(heap_dinamico, free);
    print_test("Se destruyeron los valores dinamicos", true);

}

void shuffle(int* array[], size_t n){
    
    if(n > 1){
        size_t i;
        for(i = 0; i < n - 1; i++){
          size_t j = i + (size_t)rand() / (size_t)(RAND_MAX / (n - i) + 1);
          int* t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }

}

void pruebas_heap_volumen(size_t tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN:\n");

    heap_t* heap = heap_crear(intcmp);
    int vector[tamanio];
    bool ok = true;
    int i;

    for(i = 0; i < tamanio; i++){
        vector[i] = i;
    }

    for(i = 0; i < tamanio; i++){
        ok = heap_encolar(heap, &vector[i]);
        if(!ok) break;
    }

    print_test("Se encolo 'tamanio' elementos con exito.", ok);
    print_test("Cantidad es igual a 'tamanio'.", heap_cantidad(heap) == tamanio);
    print_test("El heap no esta vacio.", !heap_esta_vacio(heap));
    print_test("El valor maximo es el correcto.", heap_ver_max(heap) == &vector[tamanio-1]);

    for(i = 0; i < tamanio; i++){
        if(heap_desencolar(heap) != &vector[tamanio-1-i]){
            ok = false;
            break;
        }
        
    }

    print_test("Se desencolo 'tamanio' elementos con exito.", ok);
    print_test("Cantidad es 0", heap_cantidad(heap) == 0);
    print_test("El heap ahora esta vacio", heap_esta_vacio(heap));
    print_test("Ver maximo ahora devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar nuevamente devuelve NULL", heap_desencolar(heap) == NULL);

    // Destruyo el heap luego de terminar las pruebas en este bloque.
    heap_destruir(heap, NULL);

}

void pruebas_heap_crear_arr(size_t tamanio){

    printf("\nINICIO DE PRUEBAS HEAP CREAR ARRAY:\n");

    int** vector = malloc(tamanio * sizeof(int*));

    for(int i = 0; i < tamanio; i++){
        vector[i] = malloc(sizeof(int));
        *vector[i] = i;
    }

    heap_t* heap_creado = heap_crear_arr((void**)vector, tamanio, intcmp);

    print_test("Se creo el heap en base al array correctamente", heap_creado);
    print_test("El valor maximo es el correcto", heap_ver_max(heap_creado) == &(*vector[tamanio-1]));
    print_test("La cantidad es la correcta", heap_cantidad(heap_creado) == tamanio);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap_creado));

    // Destruyo el heap luego de terminar las pruebas en este bloque.
    heap_destruir(heap_creado, free);

    free(vector);

}

void pruebas_heapsort(){

    printf("\nINICIO DE PRUEBAS DE HEAPSORT:\n");

    size_t tamanio = 10;
    int vector_desordenado[10] = {-5,26,18,94,561,84,-156,51,96,18};
    int vector_ordenado[10] = {-156,-5,18,18,26,51,84,94,96,561};
    bool ok = true;
    
    int** vector = malloc(tamanio * sizeof(int*));
    printf("Vector desordenado:\n");
    for(int i = 0; i < tamanio; i++){
        vector[i] = malloc(sizeof(int));
        *vector[i] = vector_desordenado[i];
        printf("(%i)", *vector[i]);
    }

    heap_sort((void**)vector, tamanio, intcmp);

    printf("\nVector ordenado:\n");
    for(int i = 0; i < tamanio; i++){
        ok = (intcmp(vector[i], &vector_ordenado[i]) == 0);
        printf("(%i)", *vector[i]);
    }

    print_test("\nEl vector se ha ordenado correctamente", ok);

    for(int i = 0; i < tamanio; i++){
        free(vector[i]);
    }
    free(vector);

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_heap_alumno(){

    srand((unsigned int)time(NULL));
    pruebas_heap_vacio();
    pruebas_heap_null();
    pruebas_heap_algunos_elementos();
    pruebas_heap_destruccion();
    pruebas_heap_volumen(PRUEBA_VOLUMEN_TAMANIO);
    pruebas_heap_crear_arr(PRUEBA_ARR_TAMANIO);
    pruebas_heapsort();

}