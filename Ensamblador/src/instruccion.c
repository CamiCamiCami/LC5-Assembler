#include "instruccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

char* limpiarLinea(char linea[]){
    while (linea[0] == ' ' || linea[0] == '\t'){
        linea++;
    }
    return linea;
}

char* avanzarToken(char linea[]){
    while(linea[0] != ' ' && linea[0] != ';' && linea[0] != '\0' && linea[0] != '\t'){
        linea++;
    }
    return linea;
}

char* extraerToken(char linea[]){
    //Asume que el token empieza en linea[0]
    const int buff_paso = 10;
    int buff_largo = buff_paso;
    char* buffer = malloc(sizeof(char) * buff_largo);
    int i = 0;
    for(; linea[i] != ' ' && linea[i] != ';' && linea[i] != '\0' && linea[i] != '\t'; i++){
        if(buff_largo <= i){
            buff_largo += buff_paso;
            buffer = realloc(buffer, buff_largo);
        }
        buffer[i] = linea[i];
    }

    buffer = realloc(buffer, i+1);
    buffer[i] = '\0';
    return buffer;
}

// Devuelve el opcode, 0 si el token no es un codigo de instruccion
int comoOpcode(char token[]){
    if(strlen(token) == 0){
        return 0;
    }
    for(int i = 0; i < CANT_CODIGOS_INS; i++){
        if(!strcmp(token, CODIGOS_INSTRUCCION[i])){
            return i+1;
        }
    }
    return 0;
}

// Devuelve Null si no encontro ningun token
char** parsearTokens(char linea[]){
    char** tokens = malloc(sizeof(char*) * 3);

    linea = limpiarLinea(linea);
    tokens[0] = extraerToken(linea);
    linea = avanzarToken(linea);

    if(tokens[0][0] == '\0'){
        return NULL;
    }

    for(int i = 1; linea[0] != '\0' && i < 3; i++){
        linea = limpiarLinea(linea);
        tokens[i] = extraerToken(linea);
        linea = avanzarToken(linea);
    }
    


    return tokens;
}

Argumento* parsearArgs(char token[]){
    return NULL;
}

Instruccion initInstruccion(char linea[]){
    Instruccion ins = malloc(sizeof(struct __instruccion));

    char** tokens = parsearTokens(linea);

    if(tokens == NULL){
        free(ins);
        return NULL;
    }

    int opcode;
    if(opcode = comoOpcode(tokens[0])){
        ins->etiqueta = NULL;
        ins->OPCODE = (unsigned char) opcode;
        ins->args = parsearArgumentos(tokens[1]);
    } else {
        ins->etiqueta = tokens[0];
        if (!(opcode = comoOpcode(tokens[1]))){
            fprintf(stderr, "Sinstaxis invalida en linea \"%s\"\n", linea);
            exit(1);
        }
        ins->OPCODE = (unsigned char) opcode;
        ins->args = parsearArgumentos(tokens[2]);
    }

    return ins;
}