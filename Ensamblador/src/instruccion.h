#include "argumentos.h"

struct __instruccion{
    unsigned char OPCODE;
    Argumento* args;
    int argc;
};
typedef struct __instruccion *Instruccion;

Instruccion initInstruccion(int opcode, Argumento* args);
