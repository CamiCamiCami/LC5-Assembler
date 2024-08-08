#ifndef UTILS_COMPILADOR
#define UTILS_COMPILADOR

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAX_ADDR (1 << 16)

enum __tipo_args {
    TIPO_NUMERO = 0b00000011,
    TIPO_REGISTRO = 0b00001100,
    TIPO_ETIQUETA = 0b00110000,
    TIPO_STRING = 0b11000000
};

enum __tipo_comando {
    OPERACION = 0,
    PSEUDOOP,
    ALIAS
};

enum __seccion {
    TEXT,
    DATA
};

enum __tipo_token {
    INSTRUCCION = 0,
    PSEUDOINS,
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
    struct __instruccion* ins;
    struct __argumento** args;
    int argc;
};

struct __pseudo_operacion {
    struct __pseudo_instruccion* psi;
    struct __argumento* arg;
};

struct __alias_operacion {
    struct __alias* alias;
    struct __argumento** args;
    int argc;
};



typedef char* Token;
typedef enum __seccion Seccion;
typedef enum __tipo_args ArgsTipo;
typedef enum __tipo_token TipoToken;
typedef enum __tipo_comando TipoComando;
typedef FILE* TokenScanner;
typedef struct __cola_nodo* ColaNodo;
typedef struct __cola* Cola;
typedef struct __operacion *Operacion;
typedef struct __pseudo_operacion *PseudoOp;
typedef struct __alias_operacion *AliasOp;
typedef struct __argumento* Argumento;
typedef struct __registro *Registro;
typedef struct __symbol_table* SymTable;
typedef struct __full_address* FullAddr;
typedef struct __instruccion* Instruccion;
typedef struct __pseudo_instruccion* PseudoIns;
typedef struct __alias* Alias;
typedef struct __constructor_salida* ConsSalida;
typedef struct __constructor_programa* ConsPrograma;
typedef unsigned short bin;
typedef unsigned short addr;
typedef bin (*Traductor)(Operacion, SymTable, addr);
typedef void (*Efecto)(ConsPrograma, PseudoOp, char*);
typedef Operacion* (*Expandir)(AliasOp, int*);

void initConstantesGlobales();
void comoStr(bin bin, char str[17]);
void intComoStr(int word, char repr[]);
void argTipoComoStr(ArgsTipo tipo, char repr[]);
Instruccion deStringInstruccion(char token[], bool* error);
TipoToken encontrarTipoPrimerToken(Token tkn);
PseudoIns deStringPseudoIns(char token[], bool* error);
Alias deStringAlias(char token[], bool* error);

struct __instruccion {
    char name[10];
    enum __tipo_args args_tipos[3];
    int argc;
    unsigned short base;
    Traductor traductor;
};


Instruccion AND;
Instruccion OR;
Instruccion IADD;
Instruccion NOR;
Instruccion ANN;
Instruccion XOR;
Instruccion SUB;
Instruccion SLT;
Instruccion IADDI;
Instruccion LUI;
Instruccion LORI;
Instruccion LD;
Instruccion ST;
Instruccion LDR;
Instruccion STR;
Instruccion BRn;
Instruccion BRz;
Instruccion BRp;
Instruccion BRnz;
Instruccion BRnp;
Instruccion BRzp;
Instruccion JUMP;
Instruccion JR;
Instruccion JALR;
Instruccion JAL;
Instruccion TRAP;
Instruccion RTI;

struct __pseudo_instruccion {
    char name[10];
    bool necesita_arg;
    enum __tipo_args arg_tipo;
    Efecto efecto;
};

PseudoIns ORIG;
PseudoIns FILL;
PseudoIns BLKW;
PseudoIns STRINGZ;
PseudoIns END;

struct __alias {
    char name[10];
    enum __tipo_args arg_tipo[3];
    int argc;
    Expandir expandir;
};

Alias ADD;
Alias MOV;

#endif