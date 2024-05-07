#include "operacion.h"
#include "instruccion.h"


#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Operacion initOperacion(Instruccion ins, Argumento* args, int argc){
	Operacion op = malloc(sizeof(struct __operacion));
    op->ins = ins;
    op->args = args;
    op->argc = argc;
    return op;
}

bin traducirOperacion(Operacion op, SymTable tabla, addr orig, addr pos){
    return (conseguirTraductor(op->ins))(op, tabla, orig, pos);
}




