#include "tokens.h"


#define DEBUG 0
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

bool esEspacio(char c){
    return (c == ' ' || c == '\t' || c == ',' || c <= (char)31);
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

char decode_escape(char escaped){
    switch (escaped) {
    case 'a':
        return (char)0x07;
    case 'b':
        return (char)0x08;
    case 'e':
        return (char)0x1B;
    case 'f':
        return (char)0x0C;
    case 'n':
        return (char)0x0A;
    case 'r':
        return (char)0x0D;
    case 't':
        return (char)0x09;
    case 'v':
        return (char)0x0B;
    case '\\':
        return (char)0x5C;
    case '\'':
        return (char)0x27;
    case '\"':
        return (char)0x22;
    case '?':
        return (char)0x3F;
    default:
        // Manejo de Error
        fprintf(stderr, "Secuencia escapada ilegal \\%c.\n", escaped);
        exit(1);
    }
}

// Mayor cantidad de tokens que espera encontrar en una linea
#define MAX_TOKENS 5

// Devuelve la cantidad de tokens encontrados, devuelve los tokens


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
