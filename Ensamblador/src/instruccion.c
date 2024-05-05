#include "instruccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

bool esOpcodeValido(int opcode){
	return (0 < opcode && opcode <= CANT_CODIGOS_INS);
}

Instruccion initInstruccion(int opcode, Argumento* args){
    if (!esOpcodeValido(opcode)){
        // Manejo de Error
        fprintf(stderr, "Opcode invalido %i\n", opcode);
        exit(1);
	}
	Instruccion ins = malloc(sizeof(struct __instruccion));
    ins->OPCODE = (unsigned char) opcode;
    ins->args = args;
    return ins;
}


