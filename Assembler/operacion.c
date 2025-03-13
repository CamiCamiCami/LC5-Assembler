#include "operacion.h"


#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Operacion initOperacion(Instruction ins, Argumento* args){
	Operacion op = malloc(sizeof(struct __operacion));
    op->ins = ins;
    op->args = malloc(sizeof(Argumento) * ins->argc);
    for (int i = 0; i < ins->argc; i++)
        op->args[i] = args[i];
    return op;
}

bin traducirOperacion(Operacion op, SymTable tabla, addr pos){
    return op->ins->traductor(op, tabla, pos);
}

void freeOperacion(Operacion op) {
    for (int i = 0; i < op->ins->argc; i++)
        freeArgumento(op->args[i]);
    free(op->args);
    free(op);
}



