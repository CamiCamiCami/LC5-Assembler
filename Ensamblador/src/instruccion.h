#include "argumentos.h"

struct __instruccion{
    char* etiqueta;
    unsigned char OPCODE;
    Argumento* args;
};
typedef struct __instruccion *Instruccion;

Instruccion initInstruccion(char linea[]);