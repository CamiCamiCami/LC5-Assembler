#include "tokens.h"
#include <ctype.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

bool esEspacio(char c){
    return (c == ' ' || c == '\t' || c <= (char)31);
}

Token initToken(char token[]){
    Token tkn = malloc(sizeof(char) * (strlen(token) + 1));
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
Token* parsearTokens(char linea[], int* c_tkn){
    Token* tokens = malloc(sizeof(Token) * MAX_TOKENS);
    const int buff_size = 100;
    int c_tokens = 0;
    char buffer[buff_size];
    int idx_buff = 0;

    for(int i = 0; linea[i] && linea[i] != ';'; i++){
        debug_print("parsearTokens: %c (ascii %i) -> ", linea[i], (int)linea[i]);
        if(!esEspacio(linea[i])){
            if (idx_buff >= buff_size){
                // Manejo de Error
                buffer[buff_size-1] = '\0';
                fprintf(stderr, "Token demasiado largo \"%s\"\n", buffer);
                exit(1);
            }
            debug_print("parte del %ier token\n", c_tokens);
            buffer[idx_buff++] = linea[i];
        } else if (idx_buff > 0){
            if (c_tokens >= MAX_TOKENS){
                // Manejo de Error
                fprintf(stderr, "Demasiados tokens en linea \"%s\"\n", linea);
                exit(1);
            }
            debug_print("espacio\n");
            // Fin del token
            buffer[idx_buff++] = '\0';
            idx_buff = 0;
            tokens[c_tokens++] = initToken(buffer);
            debug_print("parsearTokens: Encontro un token %s-%s\n", buffer, (char*)tokens[c_tokens-1]);
        } else debug_print("espacio\n");
    }

    if (idx_buff > 0){
        if (c_tokens >= MAX_TOKENS){
            // Manejo de Error
            fprintf(stderr, "Demasiados tokens en linea \"%s\"\n", linea);
            exit(1);
        }
        debug_print("espacio\n");
        // Fin del token
        buffer[idx_buff++] = '\0';
        idx_buff = 0;
        tokens[c_tokens++] = initToken(buffer);
        debug_print("parsearTokens: Encontro un token %s-%s\n", buffer, (char*)tokens[c_tokens-1]);
    }
    for (int i = 0; i < c_tokens; i++){
        debug_print("parseTokens: Tokens[%i] = %s\n", i, tokens[i]);
    }
    *c_tkn = c_tokens;
    return tokens;
}
