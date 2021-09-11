#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PRUEBA_VOLUMEN_TAMANIO 5000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void prueba_crear_abb_vacio(){

    printf("\nINICIO DE PRUEBAS CON UN ABB VACIO:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);

}

void prueba_iterar_abb_vacio(){

    printf("\nINICIO DE PRUEBAS ITERAR UN ABB VACIO:\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);

}

void prueba_abb_insertar(){

    printf("\nINICIO DE PRUEBAS ABB INSERTAR:\n");
    
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);

}

void prueba_abb_reemplazar(){

    printf("\nINICIO DE PRUEBAS ABB REEMPLAZAR:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);

}

void prueba_abb_reemplazar_con_destruir(){

    printf("\nINICIO DE PRUEBAS ABB REEMPLAZAR DESTRUIR:\n");

    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);

}

void prueba_abb_borrar(){

    printf("\nINICIO DE PRUEBAS ABB BORRAR:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

void prueba_abb_clave_vacia(){

    printf("\nINICIO DE PRUEBAS ABB CLAVE VACIA:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

void prueba_abb_valor_null(){

    printf("\nINICIO DE PRUEBAS ABB VALOR NULL:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

const char alfabeto[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int intN(int n){ 
    return rand() % n;
}

char *string_aleatorio(int longitud) {

    char* rstr = malloc((longitud + 1) * sizeof(char));

    for(int i = 0; i < longitud; i++){
        rstr[i] = alfabeto[intN(strlen(alfabeto))];
    }

    rstr[longitud] = '\0';
    return rstr;

}

void prueba_abb_volumen(size_t tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN:\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(tamanio * largo_clave);
    unsigned int* valores[tamanio];
    bool ok = true;

    /* Inserta 'tamanio' parejas en el abb */
    unsigned int i = 0;
    while(i < tamanio){
        char *aux = string_aleatorio(9);
        if(!abb_pertenece(abb, aux)){
            valores[i] = malloc(sizeof(int));
            strcpy(claves[i], aux);
            *valores[i] = i;
            ok = abb_guardar(abb, claves[i], valores[i]);
            i++;
        }
        if(!ok) break;
        free(aux);
    }

    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == tamanio);

    /* Verifica que devuelva los valores correctos */
    for(i = 0; i < tamanio; i++){
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == tamanio);

    /* Verifica que borre y devuelva los valores correctos */
    for(i = 0; i < tamanio; i++){
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'tamanio' parejas en el abb */
    ok = true;
    for(i = 0; i < tamanio; i++){
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);

}

void prueba_abb_iterador_externo(){

    printf("\nINICIO DE PRUEBAS ITERADOR EXTERNO:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    print_test("Prueba abb iterador ver actual, itera en orden...", strcmp(abb_iter_in_ver_actual(iter), claves[1]) == 0);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    print_test("Prueba abb iterador ver actual, itera en orden...", strcmp(abb_iter_in_ver_actual(iter), claves[0]) == 0);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    print_test("Prueba abb iterador ver actual, itera en orden...", strcmp(abb_iter_in_ver_actual(iter), claves[2]) == 0);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);

}

void prueba_abb_iterador_externo_volumen(size_t tamanio){

    printf("\nINICIO DE PRUEBAS DE VOLUMEN ITERADOR EXTERNO:\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(tamanio * largo_clave);
    size_t valores[tamanio];
    bool ok = true;

    /* Inserta 'tamanio' parejas en el abb */
    unsigned int i = 0;
    while(i < tamanio){
        char *aux = string_aleatorio(9);
        if(!abb_pertenece(abb, aux)){
            strcpy(claves[i], aux);
            valores[i] = i;
            ok = abb_guardar(abb, claves[i], &valores[i]);
            i++;
        }
        if(!ok) break;
        free(aux);
    }

    print_test("Se almaceno tamanio elementos correctamente", ok);
    
    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    const char *clave;
    size_t *valor;

    for(i = 0; i < tamanio; i++){
        if(abb_iter_in_al_final(iter)){
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if(clave == NULL){
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if(valor == NULL){
            ok = false;
            break;
        }
        *valor = tamanio;
        abb_iter_in_avanzar(iter);
    }
    
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el tamanio", i == tamanio);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for(i = 0; i < tamanio; i++){
        if(valores[i] != tamanio){
            ok = false;
            break;
        }
    }
    
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);

}

bool cantidad_elementos(const char* clave, void* dato, void* extra){

    *(size_t*) extra += 1;
    return true;

}

bool primeros_dos(const char* clave, void* dato, void* extra){

    if (*(size_t*) extra >= 2) return false;
    *(size_t*) extra += 1;
    return true;

}

void prueba_abb_iterador_interno(){

    printf("\nINICIO DE PRUEBAS ITERADOR INTERNO:\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));
    print_test("Se insertaron todas las claves correctamente", abb_cantidad(abb) == 3);

    size_t contador = 0;
    abb_in_order(abb, cantidad_elementos, &contador);
    print_test("Con extra, Sin corte, Se contaron 3 elementos", contador == 3);
    contador = 0;
    abb_in_order(abb, primeros_dos, &contador);    
    print_test("Con extra, con corte, Se contaron 2 elementos", contador == 2);

    abb_destruir(abb);

}

void prueba_abb_iterador_interno_volumen(size_t tamanio){

    printf("\nINICIO DE PRUEBAS ITERADOR INTERNO VOLUMEN:\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(tamanio * largo_clave);
    size_t valores[tamanio];
    bool ok = true;
    size_t contador = 0;

    /* Inserta 'tamanio' parejas en el abb */
    unsigned int i = 0;
    while(i < tamanio){
        char *aux = string_aleatorio(9);
        if(!abb_pertenece(abb, aux)){
            strcpy(claves[i], aux);
            valores[i] = i;
            ok = abb_guardar(abb, claves[i], &valores[i]);
            i++;
        }
        if(!ok) break;
        free(aux);
    }

    print_test("Se almaceno tamanio elementos correctamente", ok);

    abb_in_order(abb, cantidad_elementos, &contador);

    print_test("La funcion iterar termino normalmente y la cantidad de elementos es la correcta", contador == tamanio);

    free(claves);
    abb_destruir(abb);

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_alumno(){
    
    srand((unsigned int)time(NULL));
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(PRUEBA_VOLUMEN_TAMANIO);
    prueba_abb_iterador_externo();
    prueba_abb_iterador_externo_volumen(PRUEBA_VOLUMEN_TAMANIO);
    prueba_abb_iterador_interno();
    prueba_abb_iterador_interno_volumen(PRUEBA_VOLUMEN_TAMANIO);

}