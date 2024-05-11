#ifndef TIPOS
#define TIPOS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADDR (1 << 16)

enum __instruccion{
    NULL_INS = 0,
	ADD,
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
};

enum __pseudoins{
    NULL_PSO = 0,
    ORIG,
    FILL,
    BLKW,
    END
};

enum __tipo_args {
    TIPO_NUMERO = 0b00000011,
    TIPO_REGISTRO = 0b00001100,
    TIPO_ETIQUETA = 0b00110000
};

enum __seccion {
    TEXT,
    DATA
};

enum __tipo_token {
    INSTRUCCION,
    PSEUDOOP,
    ETIQUETA
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
void argTipoComoStr(unsigned char tipo, char repr[10]);
TipoToken encontrarTipoToken(Token tkn);

#endif 
