#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "debug.h"

Cola initCola(){
    Cola nueva = malloc(sizeof(struct __cola));
    nueva->cabeza = NULL;
    nueva->fin = NULL;
    return nueva;
}

void pushCola(Cola cola, void* valor){
    // Crea Nodo
    ColaNodo nodo = malloc(sizeof(struct __cola_nodo));
    nodo->sig = cola->cabeza;
    nodo->ant = NULL;
    nodo->valor = valor;
    
    // Lo pone en la cabeza
    if (cola->cabeza != NULL){
        cola->cabeza->ant = nodo;
        cola->cabeza = nodo;
    } else {
        cola->cabeza = nodo;
    }
    // Setea el fin si es necesario
    if (cola->fin == NULL){
        cola->fin = nodo;
    }
}

void freeColaNodo(ColaNodo nodo){
    free(nodo);
}

void* popCola(Cola cola){
    if (cola->fin == NULL){
        fprintf(stderr, "No puede hacer popCola en una cola de largo 0\n");
        exit(1);
    }
    // Tomamos lo que se necesita del nodo final
    void* valor = cola->fin->valor;
    ColaNodo ant = cola->fin->ant;
    // Liberamos el ultimo nodo
    freeColaNodo(cola->fin);
    if(ant != NULL){
        // Si la cola no está vacia
        // Actualizamos el nuevo ultimo acorde
        ant->sig = NULL;
        cola->fin = ant;
    } else {
        // Si la cola está vacia
        cola->cabeza = NULL;
        cola->fin == NULL;
    }
    return valor;
}

int lengthCola(Cola cola){
    int largo = 0;
    ColaNodo nodo = cola->cabeza;
    for(; nodo != NULL; largo++){
        nodo = nodo->sig;
    }
    return largo;
}

void freeCola(Cola cola){
    ColaNodo nodo = cola->cabeza;
    ColaNodo sig;
    while(nodo != NULL){
        sig = nodo->sig;
        freeColaNodo(nodo);
        nodo = sig;
    }

    free(cola);
}