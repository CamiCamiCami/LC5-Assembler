#include "instruccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "tokens.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

// Devuelve el opcode, 0 si el token no es un codigo de instruccion
int comoOpcode(Token _token){
    char token[lengthToken(_token)];
    comoStringToken(_token, token);

    for(int i = 0; i < CANT_CODIGOS_INS; i++){
        if(!strcmp(token, CODIGOS_INSTRUCCION[i])){
            return i+1;
        }
    }
    return 0;
}

Instruccion initInstruccion(Token tokens[], int c_tokens){
    if(c_tokens < 2 || 4 < c_tokens){
        // Manejo de Error
        fprintf(stderr, "Cantidad de tokens fuera de rango. Esperaba 2-3, recibio %i", c_tokens);
        exit(1);
    }

    Instruccion ins = malloc(sizeof(struct __instruccion));

    int opcode;
    if(c_tokens == 2){
        if ((opcode = comoOpcode(tokens[0])) == 0){
            // Manejo de Error
            free(ins);
            fprintf(stderr, "Instruccion invalida \"%s\"\n", tokens[0]);
            exit(1);
        }
        ins->etiqueta = NULL;
        ins->OPCODE = (unsigned char) comoOpcode(tokens[0]);
        ins->args = parsearArgumentos(tokens[1]);
    } else {
        if ((opcode = comoOpcode(tokens[1])) == 0){
            // Manejo de Error
            free(ins);
            fprintf(stderr, "Instruccion invalida \"%s\"\n", tokens[1]);
            exit(1);
        }
        ins->etiqueta = tokens[0];
        ins->OPCODE = (unsigned char) opcode;
        ins->args = parsearArgumentos(tokens[2]);
    }

    return ins;
}