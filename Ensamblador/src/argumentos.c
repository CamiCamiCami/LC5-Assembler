#include "argumentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Argumento initArgumentoNumero(int n){
    int* ptr = malloc(sizeof(int));
    *ptr = n;
    return initArgumento(TIPO_NUMERO, ptr);
}

Argumento initArgumentoRegistro(int n_reg){
    if(n_reg < 0 || 7 < n_reg){
        fprintf(stderr, "Sintaxis invalidad, Numero de registro fuera de rango (0-7) (Recibio %i)", n_reg);
        exit(1);
    }

    Registro r = malloc(sizeof(struct __registro));
    r->NUMERO = n_reg;
    return initArgumento(TIPO_REGISTRO, r);
}

Argumento initArgumentoEtiqueta(char etiqueta[]){
    char* ptr = malloc((sizeof(char) * strlen(etiqueta)) + 1);
    strcpy(ptr, etiqueta);
    return initArgumento(TIPO_ETIQUETA, ptr);
}

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
    char* end;

    if(token[0] == 'r' || token[0] == 'R'){
        long r_num = strtol(token+1, &end, 10);
        if (r_num != 0 || end[0] == '\0'){
            // El token es un argumento de registro
            return initArgumentoRegistro(r_num);
        }
    } else if (token[0] == 'b'){
        long value = strtol(token+1, &end, 2);
        if (value != 0 || end[0] == '\0'){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else if (token[0] == 'x'){
        long value = strtol(token+1, &end, 16);
        if (value != 0 || end[0] == '\0'){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else if (token[0] == '#'){
        long value = strtol(token+1, &end, 10);
        if (value != 0 || end[0] == '\0'){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else {
        long value = strtol(token, &end, 10);
        if (value != 0 || end[0] == '\0'){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    }

    return initArgumentoEtiqueta(token);
}

Argumento* parsearArgumentos(char raw[]){
    debug_print("parsearArgumentos: Parseando %s\n", raw);
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
    debug_print("parsearArgumentos: Encontro %i tokens\n", c_tokens);

    Argumento* args = malloc(sizeof(Argumento) * c_tokens);

    for(int i = 0; i < c_tokens; i++){
        args[i] = _parsearArgumento(tokens[i]);
    }
    debug_print("parsearArgumentos: Tokens parseados\n");
    return args;
}

void freeArgumento(Argumento arg){
    free(arg->valor);
    free(arg);
}

int tipoArgumento(Argumento arg){
    return arg->tipo;
}

void* valorArgumento(Argumento arg){
    return arg->valor;
}

void printArgumento(Argumento arg){
    switch (arg->tipo) {
    case 1:
        printf("Nro %i\n", *((int*)arg->valor));
        break;
    case 2:
        printf("Registro %i\n", ((Registro)arg->valor)->NUMERO);
        break;
    case 3:
        printf("Etiqueta %s\n", ((char*)arg->valor));
        break;
    default:
        fprintf(stderr, "Argumento con tipo ilegal %i. Rango esperado 1-3\n", arg->tipo);
        break;
    }
}

void toStringArgumento(Argumento arg, char* rtn){
    switch (arg->tipo) {
    case 1:
        sprintf(rtn, "Nro %i\n", *((int*)arg->valor));
        break;
    case 2:
        sprintf(rtn, "Registro %i\n", ((Registro)arg->valor)->NUMERO);
        break;
    case 3:
        sprintf(rtn, "Etiqueta %s\n", ((char*)arg->valor));
        break;
    default:
        fprintf(stderr, "Argumento con tipo ilegal %i. Rango esperado 1-3\n", arg->tipo);
        break;
    }
}