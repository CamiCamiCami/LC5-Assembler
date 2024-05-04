


struct __cola_nodo {
    void* valor;
    struct __cola_nodo *sig;
    struct __cola_nodo *ant;
};

typedef struct __cola_nodo* ColaNodo;

struct __cola
{
    ColaNodo cabeza;
    ColaNodo fin;
};

typedef struct __cola* Cola;


Cola initCola();

void pushCola(Cola cola, void* valor);

void* popCola(Cola cola);

int lengthCola(Cola cola);

void freeCola(Cola cola);