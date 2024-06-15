#ifndef TIPOS
#define TIPOS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDR (1 << 16)

enum __instruccion{
    IAND = 0,
    IOR,
	IADD,
    INOR,
    IANN,
    IXOR,
    ISUB,
    ISLT,
    IADDI,
    ILUI,
    ILORI,         
    ILD,                                          
    IST,
    ILDR,
    ISTR,
    IBRn,
    IBRz,
    IBRp,
    IBRnz,
    IBRnp,
    IBRzp,
    IJUMP,
    IJR,
    IJAL,
    IJALR,
    ITRAP,
    IRTI
};

enum __pseudoins{
    ORIG = 0,
    FILL,
    BLKW,
    STRINGZ,
    END
};

enum __tipo_args {
    TIPO_NUMERO = 0b00000011,
    TIPO_REGISTRO = 0b00001100,
    TIPO_ETIQUETA = 0b00110000,
    TIPO_STRING = 0b11000000
};

enum __seccion {
    TEXT,
    DATA
};

enum __tipo_token {
    INSTRUCCION = 0,
    PSEUDOOP,
    ETIQUETA,
    ARGUMENTOS
};

struct __registro{
     unsigned char NUMERO:3, __unused:5;
};

struct __argumento {
    enum __tipo_args tipo;
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
    int largo;
};

struct __symbol_table{
    struct __symbol_list** array;
    int largo;
};

struct __full_address {
    enum __seccion seccion;
    unsigned int offset;
};

struct __constructor_salida {
    FILE* file;
    int largo;
    int alocado;
    unsigned short* contenido;
};

struct __constructor_programa {
    struct __cola* text;
    struct __cola* data;
    struct __symbol_table* symtable;
    unsigned short orig;
    bool reached_end;
};

struct __operacion{
    enum __instruccion ins;
    struct __argumento** args;
    int argc;
};


typedef char* Token;
typedef enum __instruccion Instruccion;
typedef enum __seccion Seccion;
typedef enum __pseudoins PseudoIns;
typedef enum __tipo_args ArgsTipo;
typedef enum __tipo_token TipoToken;
typedef FILE* Escaner;
typedef struct __cola_nodo* ColaNodo;
typedef struct __cola* Cola;
typedef struct __operacion *Operacion;
typedef struct __argumento* Argumento;
typedef struct __registro *Registro;
typedef struct __symbol_table* SymTable;
typedef struct __full_address* FullAddr;
typedef struct __operacion* Operacion;
typedef struct __constructor_salida* ConsSalida;
typedef struct __constructor_programa* ConsPrograma;
typedef unsigned short bin;
typedef unsigned short addr;
typedef bin (*Traductor)(Operacion, SymTable, addr);

void comoStr(bin bin, char str[17]);
void intComoStr(int word, char repr[33]);
void argTipoComoStr(ArgsTipo tipo, char repr[50]);
TipoToken encontrarTipoPrimerToken(Token tkn);

#endif 
