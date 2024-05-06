#include "argumentos.h"
#include "enum_instrucciones.h"

struct __instruccion{
    InstruccionProcesador INS;
    Argumento* args;
    int argc;
};
typedef struct __instruccion *Instruccion;

Instruccion initInstruccion(InstruccionProcesador ins, Argumento* args);
