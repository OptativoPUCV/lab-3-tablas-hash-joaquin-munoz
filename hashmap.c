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
HashMap * createMap(long capacity) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (Pair**)calloc(capacity,sizeof(Pair*));
    
    map->capacity = capacity;
    map->current = -1;
    map->size = 0;
    return map;
}
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
    long posicion = hash(key,map->capacity);
    while(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){
        posicion = (posicion + 1) % map->capacity;
    }
    Pair * par = createPair(strdup(key),value);
    map->size++;
    map->buckets[posicion] = par;
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
void eraseMap(HashMap * map,  char * key){
    long pos = hash(key,map->capacity);
    while(map->buckets[pos] != NULL){
        if(is_equal(map->buckets[pos]->key,key)){
            map->buckets[pos]->key = NULL;
            map->size--;
        }
        pos = (pos + 1) % map->capacity;
    }
}
void enlarge(HashMap * map) {
    enlarge_called = 1;  //no borrar (testing purposes)
    // gurdar datos antes de cambiarlos
    Pair **bucket_old = map->buckets;
    long capacidadAntigua = map->capacity;
    
    // duplicar capacidad de map nuevo 
    map->capacity *= 2;
    
    //asignamos nueva memoria para el nuevo mapa 
    map->buckets = (Pair **) malloc(sizeof(Pair *) * map->capacity);
    for (long i = 0; i < map->capacity; i++) {
        map->buckets[i] = NULL;
    }
    
    // reiniciamos tamaño de datos ingresados 
    map->size = 0;
    
    // reordenamos datos anteriores 
    for (long i = 0; i < capacidadAntigua; i++) {
        if (bucket_old[i] != NULL && bucket_old[i]->key != NULL) {
            insertMap(map, bucket_old[i]->key, bucket_old[i]->value);
        }
    }
    
    // Liberamos el arreglo antiguo
    free(bucket_old);
}

Pair * firstMap(HashMap * map) {
    // recorremos el mapa para allar el primer pair valido y lo entrgamos , en otro caso retotnamos null.
    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;

}

Pair * nextMap(HashMap * map) {
    for (long i = map->current + 1; i < map->capacity; i++) { // recorremos desde el current + 1 (el siguiente dato)
        if (map->buckets[i] != NULL) { //preguntamos si es valido
            map->current = i;
            return map->buckets[i]; // lo retornamos
        }
    }
    return NULL;
}
