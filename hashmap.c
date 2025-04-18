#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    /*long posicion = hash(key,map->capacity);
    while(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){
        posicion = (posicion + 1) % map->capacity;
    }
    Pair * par = createPair(strdup(key),value);
    map->size++;
    map->buckets[posicion] = par;
    */
}
void enlarge(HashMap * map) {
    enlarge_called = 1; // no borrar (testing purposes)
    /*// gurdar datos antes de cambiarlos
    Pair **bucketold = map->buckets;
    long capacidadAntigua = map->capacity;
    
    // duplicar capacidad
    map->capacity *= 2;
    
    //nuevo arreglo de buckets 
    map->buckets = (Pair **) malloc(sizeof(Pair *) * map->capacity);
    for (long i = 0; i < map->capacity; i++) {
        map->buckets[i] = NULL;
    }
    
// reiniciamos tamaño
    map->size = 0;
    
// reordenamos datos anteriores 
    for (long i = 0; i < capacidadAntigua; i++) {
        if (bucketold[i] != NULL && bucketold[i]->key != NULL) {
            insertMap(map, bucketold[i]->key, bucketold[i]->value);
        }
    }
    
    // Liberamos el arreglo antiguo
    free(bucketold);*/
}

Pair * searchMap(HashMap * map,  char * key) {   
    long pos = hash(key,map->capacity);
    while(map->buckets[pos] != NULL){
        if(is_equal(map->buckets[pos]->key,key)) {
            map->current = pos;
            return map->buckets[pos];
        }
        pos = (pos + 1) % map->capacity;
    }
    return NULL;
}
/*Implemente las funciones para recorrer la estructura: Pair * firstMap(HashMap * map) retorna el primer **Pair** válido del arreglo buckets. 
Pair * nextMap(HashMap * map) retorna el siguiente **Pair** del arreglo buckets a partir índice current. Recuerde actualizar el índice.

    Pair * firstMap(HashMap * map) {
        

        return NULL;
    }

    Pair * nextMap(HashMap * map)  {
       

        return NULL;
    }*/
Pair * firstMap(HashMap * map) {
    
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
