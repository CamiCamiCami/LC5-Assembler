#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct __cola_nodo { 
    void* valor;
    struct __cola_nodo *sig;
    struct __cola_nodo *ant;
};


struct __cola {
	struct __cola_nodo* cabeza;
    struct __cola_nodo* fin;
    int largo;
};

typedef struct __cola_nodo* ColaNodo;
typedef struct __cola* Cola;

Cola initCola(void);

void pushCola(Cola cola, void* valor);

void* popCola(Cola cola);

int lengthCola(Cola cola);

bool emptyCola(Cola cola);

void freeCola(Cola cola);
