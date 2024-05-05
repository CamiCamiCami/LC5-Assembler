#include "argumentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Argumento initArgumento(int tipo, void* valor){
    if(tipo < 1 || 3 < tipo){
        fprintf(stderr, "Mal tipo para Argumento, espera valores entre 1 y 3 pero recibio %i\n", tipo);
        exit(1);
    }
    Argumento arg = malloc(sizeof(struct __argumento));
    arg->tipo = (unsigned char)tipo;
    arg->valor = valor;
    return arg;
}

Argumento _parsearArgumento(char token[]){
    long as_num = strtol(token, NULL, 10);
    if (as_num != 0 || errno != EINVAL){
        // El token es un argumento numerico
        int* n = malloc(sizeof(int));
        *n = as_num;
        return initArgumento(TIPO_NUMERO, n);
    }

    bool empiezaR = token[0] == 'r' || token[0] == 'R';
    
}

Argumento* parsearArgumentos(char raw[]){
    const int MAX_TOKENS = 5;
    char* tokens[MAX_TOKENS];
    tokens[0] = strtok(raw, ",");
    int c_tokens = 0;
    for(int i = 1; tokens[i-1] != NULL && i<MAX_TOKENS; i++, c_tokens++) {
        if (i >= MAX_TOKENS){
            fprintf(stderr, "Sintaxis invalida, demasiados argumentos\n");
        }
        tokens[i] = strtok(NULL, ",");
    }



    return NULL;
}