#ifndef TIPOS
#define TIPOS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TIPO_NUMERO 1
#define TIPO_REGISTRO 2
#define TIPO_ETIQUETA 3


enum __instruccion{
	ADD = 1,
    SUB,
    AND,
    OR,
    ADDI,
    ANDI,
    ORI,
    BRp,
    BRz,
    BRn,
    JR,
    JALR,
    TRAP,
    RETI,
    NOT,
    JAL,         
    LD,                                          
    ST,
    LDR,
    STR,
    LUI,
    LORI,
    LJMP,
    NULL_INS
};

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

struct __symbol_table{
    struct __symbol_list** array;
    int largo;
};

struct __constructor_salida {
    FILE* file;
    int largo;
    int alocado;
    bin* contenido;
};


typedef char* Token;
typedef enum __instruccion Instruccion;
typedef FILE* Escaner;
typedef struct __cola_nodo* ColaNodo;
typedef struct __cola* Cola;
typedef struct __argumento* Argumento;
typedef struct __registro *Registro;
typedef struct __symbol_table* SymTable;
typedef struct __operacion* Operacion;
typedef struct __constructor_salida* ConsSalida;
typedef unsigned short bin;
typedef unsigned short addr;
typedef bin (*Traductor)(Operacion, SymTable, addr, addr);

void comoStr(bin bin, char str[17]);
void intComoStr(int word, char repr[33]);
void argTipoComoStr(unsigned char tipo, char repr[10]);

#endif 
