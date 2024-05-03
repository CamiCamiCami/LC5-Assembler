#include <stdlib.h>

struct __cola_nodo {
    void* valor;
    __cola_nodo* sig;
    __cola_nodo* ant;
};


typedef __cola_nodo* NodoCola;

struct __cola
{
    NodoCola cabeza;
    NodoCola fin;
};

typedef __cola* Cola;


Cola initCola();