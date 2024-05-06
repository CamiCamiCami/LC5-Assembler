#include "instruccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Instruccion initInstruccion(InstruccionProcesador INS, Argumento* args){

	Instruccion ins = malloc(sizeof(struct __instruccion));
    ins->INS = INS;
    ins->args = args;
    return ins;
}

bin traducirInsTruccion(Instruccion ins){
    return 0;
}


