#include "cola.h"

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

void* popCola(Cola cola){
    // Tomamos lo que se necesita del nodo final
    void* valor = cola->fin->valor;
    ColaNodo ant = cola->fin->ant;
    // Liberamos el ultimo nodo
    freeColaNodo(cola->fin);
    // Actualizamos el nuevo ultimo acorde
    ant->sig = NULL;
    // Seteamos el nuevo ultimo
    cola->fin = ant;
    return valor;
}

void freeColaNodo(ColaNodo nodo){
    free(nodo);
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