#ifndef TIPOS
#define TIPOS

#include <stdio.h>
#include <stdbool.h>

#define TIPO_NUMERO 1
#define TIPO_REGISTRO 2
#define TIPO_ETIQUETA 3

struct __registro{
     unsigned char NUMERO:3, __unused:5;
};

struct __argumento {
	// tipo = 1 -> int*     (Numero constante)
    // tipo = 2 -> Registro (Registro 0-7)
    // tipo = 3 -> char*    (Etiqueta)
    unsigned char tipo;
    void* valor;
};

struct __cola_nodo { 
    void* valor;
    struct __cola_nodo *sig;
    struct __cola_nodo *ant;
};


struct __cola {
	struct __cola_nodo* cabeza;
    struct __cola_nodo* fin;
};

typedef FILE* Escaner;
typedef struct __cola_nodo* ColaNodo;
typedef struct __cola* Cola;
typedef struct __argumento* Argumento;
typedef struct __registro *Registro;
typedef struct __symbol_table* SymTable;
typedef struct __symbol_list* SymList;
typedef struct __symbol* Symbol;
typedef struct __operacion* Operacion;
typedef unsigned short bin;
typedef unsigned short addr;
typedef bin (*Traductor)(Operacion, SymTable, addr, addr);



#endif 
