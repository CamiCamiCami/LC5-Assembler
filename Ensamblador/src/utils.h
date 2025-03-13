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

enum __seccion {
    TEXT,
    DATA
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
    struct __instruction* ins;
    struct __argumento** args;
};

struct __pseudo_operacion {
    struct __pseudo_instruction* psi;
    struct __argumento* arg;
};

struct __alias_operacion {
    struct __alias* alias;
    struct __argumento** args;
};

union __instance_type {
    struct __instruction* ins;
    struct __pseudo_instruction* psi;
    struct __alias* alias;
};

enum __statement_type {
    OPERATION = 0,
    PSEUDOOP,
    ALIAS
};

struct __statement {
    void* ins;
    Argumento* args;
    enum __statement_type statement_type;
};

struct __statement_builder {
    StatementType type;
    void* insruction;
    Argumento* args;
    int arg_idx;
    char* label;
};

typedef struct __statement_builder* StatementBuilder;
typedef struct __statement* Statement;
typedef void* InstanceType;
typedef enum __seccion Seccion;
typedef enum __tipo_args ArgsTipo;
typedef enum __statement_type StatementType;
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
typedef struct __instruction* Instruction;
typedef struct __pseudo_instruction* PseudoIns;
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
Instruction deStringInstruccion(char token[], bool* error);
PseudoIns deStringPseudoIns(char token[], bool* error);
Alias deStringAlias(char token[], bool* error);

struct __instruction {
    char name[10];
    enum __tipo_args args_tipos[3];
    int argc;
    unsigned short base;
    Traductor traductor;
};


Instruction AND;
Instruction OR;
Instruction IADD;
Instruction NOR;
Instruction ANN;
Instruction XOR;
Instruction SUB;
Instruction SLT;
Instruction IADDI;
Instruction LUI;
Instruction LORI;
Instruction LD;
Instruction ST;
Instruction LDR;
Instruction STR;
Instruction BRn;
Instruction BRz;
Instruction BRp;
Instruction BRnz;
Instruction BRnp;
Instruction BRzp;
Instruction JUMP;
Instruction JR;
Instruction JALR;
Instruction JAL;
Instruction TRAP;
Instruction RTI;

struct __pseudo_instruction {
    char name[10];
    int argc;
    enum __tipo_args arg_tipo;
    Efecto efecto;
};

extern PseudoIns ORIG;
extern PseudoIns FILL;
extern PseudoIns BLKW;
extern PseudoIns STRINGZ;
extern PseudoIns END;

struct __alias {
    char name[10];
    enum __tipo_args arg_tipo[3];
    int argc;
    Expandir expandir;
};

extern Alias ADD;
extern Alias MOV;

#endif