#include "argumentos.h"
#include "instruccion.h"

struct __operacion{
    Instruccion ins;
    Argumento* args;
    int argc;
};
typedef struct __operacion *Operacion;

Operacion initOperacion(Instruccion ins, Argumento* args, int argc);

bin traducirOperacion(Operacion op, SymTable tabla, addr orig, addr pos);
