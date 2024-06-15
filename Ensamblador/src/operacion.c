#include "operacion.h"
#include "instruccion.h"
#include "argumentos.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Operacion initOperacion(Token tkns[], int c_tkns){
	Operacion op = malloc(sizeof(struct __operacion));
    bool err;
    op->ins = deStringInstruccion(tkns[0], &err);
    if (err){
        fprintf(stderr, "Codigo de operación invalido: %s\n", tkns[0]);
        exit(1);
    }
    
    if (c_tkns >= 2) {
        op->args = parsearArgumentos(tkns[1], &(op->argc));
    } else {
        op->args = NULL;
        op->argc = 0;
    }
    
    return op;
}

bin traducirOperacion(Operacion op, SymTable tabla, addr pos){
    return (conseguirTraductorInstruccion(op->ins))(op, tabla, pos);
}

void freeOperacion(Operacion op) {
    for (int i = 0; i < op->argc; i++)
        freeArgumento(op->args[i]);
    free(op->args);
    free(op);
}



