#include "tokens.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool esEspacio(char c){
    return (c == ' ' || c == '\t');
}

Token initToken(char token[]){
    Token tkn = malloc(sizeof(char) * strlen(token));
    strcpy(tkn, token);
    return tkn;
}

void freeToken(Token token){
    free(token);
}

void comoStringToken(Token token, char copia[]){
    strcpy(copia, token);
}

int lengthToken(Token token){
    return strlen(token);
}

// Mayor cantidad de tokens que espera encontrar en una linea
#define MAX_TOKENS 3

// Devuelve la cantidad de tokens encontrados, devuelve los tokens
int parsearTokens(char linea[], Token tokens[MAX_TOKENS]){
    const int buff_size = 100;
    int c_tokens = 0;
    char buffer[buff_size];
    int idx_buff = 0;

    for(int i = 0; linea[i] && linea[i] != ';'; i++){
        if(!esEspacio(linea[i])){
            if (idx_buff >= buff_size){
                // Manejo de Error
                buffer[buff_size-1] = '\0';
                fprintf(stderr, "Token demasiado largo \"%s\"\n", buffer);
                exit(1);
            }
            buffer[idx_buff++] = linea[i];
        } else if (idx_buff > 0){
            if (c_tokens >= MAX_TOKENS){
                // Manejo de Error
                fprintf(stderr, "Demasiados tokens en linea \"%s\"\n", linea);
                exit(1);
            }
            // Fin del token
            buffer[idx_buff++] = '\0';
            idx_buff = 0;
            tokens[c_tokens++] = initToken(buffer);
        }
    }

    return c_tokens;

    if (idx_buff > 0){
        if (c_tokens >= MAX_TOKENS){
            fprintf(stderr, "Demasiados tokens en linea \"%s\"\n", linea);
            exit(1);
        }
        buffer[idx_buff++] = '\0';
        idx_buff = 0;
        tokens[c_tokens++] = initToken(buffer);
    }

    return c_tokens;
}
