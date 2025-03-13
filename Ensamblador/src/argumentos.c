#include "argumentos.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Argumento internalInitArgumento(int tipo, void* valor){
    if(tipo != TIPO_NUMERO && tipo != TIPO_REGISTRO && tipo != TIPO_ETIQUETA && tipo != TIPO_STRING){
        fprintf(stderr, "Mal tipo para Argumento, recibio %i\n", tipo);
        exit(1);
    }
    Argumento arg = malloc(sizeof(struct __argumento));
    arg->tipo = (unsigned char)tipo;
    arg->valor = valor;
    return arg;
}

Argumento initArgumentoString(char str[]){
    // Quita los "" del string
    str += 1;
    str[strlen(str)-1] = '\0';

    char* ptr = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ptr, str);

    return internalInitArgumento(TIPO_STRING, ptr);
}

Argumento initArgumentoNumero(int n){
    int* ptr = malloc(sizeof(int));
    *ptr = n;
    return internalInitArgumento(TIPO_NUMERO, ptr);
}

Argumento initArgumentoRegistro(int n_reg){
    if(n_reg < 0 || 7 < n_reg){
        fprintf(stderr, "Sintaxis invalidad, Numero de registro fuera de rango (0-7) (Recibio %i)", n_reg);
        exit(1);
    }

    Registro r = malloc(sizeof(struct __registro));
    r->NUMERO = n_reg;
    return internalInitArgumento(TIPO_REGISTRO, r);
}

Argumento initArgumentoEtiqueta(char etiqueta[]){
    char* ptr = malloc((sizeof(char) * strlen(etiqueta)) + 1);
    strcpy(ptr, etiqueta);
    return internalInitArgumento(TIPO_ETIQUETA, ptr);
}

Argumento initArgumento(char* token){
    if (token[0] == '\0'){
        // Manejo de Error
        fprintf(stderr, "No se puede parsear un token vacio.\n");
        exit(1);
    }
    char* end;
    int token_len = strlen(token);
    if(token[0] == 'r' || token[0] == 'R'){
        long r_num = strtol(token+1, &end, 10);
        if (end[0] == '\0' && token_len > 1){
            // El token es un argumento de registro
            return initArgumentoRegistro(r_num);
        }
    } else if (token[0] == 'b'){
        long value = (short)strtol(token+1, &end, 2);
        if (end[0] == '\0' && token_len > 1){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else if (token[0] == 'x'){
        long value = strtol(token+1, &end, 16);
        if (end[0] == '\0' && token_len > 1){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else if (token[0] == '#'){
        long value = strtol(token+1, &end, 10);
        if (end[0] == '\0' && token_len > 1){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    } else if (token[0] == '\"') {
        if (token[token_len - 1] != '\"') {
            // Manejo de Error
            fprintf (stderr, "Literal de string no cerro con \".\n");
            exit(1);
        }
        return initArgumentoString(token);
    } else {
        long value = strtol(token, &end, 10);
        if (end[0] == '\0'){
            // El token es un argumento numerico
            return initArgumentoNumero(value);
        }
    }

    return initArgumentoEtiqueta(token);
}

Argumento directInitArgumento(void* arg, ArgsTipo tipo) {
    switch (tipo) {
    case TIPO_REGISTRO:
        return initArgumentoRegistro(((Registro)arg)->NUMERO);
    case TIPO_NUMERO:
        return initArgumentoNumero(*((int*)arg));
    case TIPO_STRING:
        return initArgumentoString(arg);
    case TIPO_ETIQUETA:
        return initArgumentoEtiqueta(arg);
    default:
        fprintf(stderr, "Error de programacion, directInitArgumento");
        exit(0);
    }
}

/*Argumento* parsearArgumentos(char raw[], int* argc){
    debug_print("parsearArgumentos: Parseando %s\n", raw);
    const int MAX_TOKENS = 5;
    char* tokens[MAX_TOKENS];
    tokens[0] = strtok(raw, ",");
    int c_tokens = 0;

    for(int i = 1; tokens[i-1] != NULL && i<MAX_TOKENS; i++, c_tokens++) {
        if (i >= MAX_TOKENS){
            fprintf(stderr, "Sintaxis invalida, demasiados argumentos\n");
            exit(1);
        }
        tokens[i] = strtok(NULL, ",");
    }
    debug_print("parsearArgumentos: Encontro %i tokens\n", c_tokens);

    Argumento* args = malloc(sizeof(Argumento) * c_tokens);

    for(int i = 0; i < c_tokens; i++){
        args[i] = _parsearArgumento(tokens[i]);
    }

	*argc = c_tokens;
    debug_print("parsearArgumentos: Tokens parseados\n");
    return args;
}*/

void freeArgumento(Argumento arg){
    if (arg == NULL) {
        return;
    }
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
    case TIPO_NUMERO:
        printf("Nro %i\n", *((int*)arg->valor));
        break;
    case TIPO_REGISTRO:
        printf("Registro %i\n", ((Registro)arg->valor)->NUMERO);
        break;
    case TIPO_ETIQUETA:
        printf("Etiqueta %s\n", ((char*)arg->valor));
        break;
    case TIPO_STRING:
        printf("String %s\n", ((char*)arg->valor));
        break;
    default:
        fprintf(stderr, "Argumento con tipo ilegal %i. Rango esperado 1-3\n", arg->tipo);
        break;
    }
}

bool argCoincideTipo(ArgsTipo req_tipo, Argumento arg) {
    return (req_tipo & arg->tipo);
}

void toStringArgumento(Argumento arg, char* rtn){
    switch (arg->tipo) {
    case TIPO_NUMERO:
        sprintf(rtn, "Nro %i\n", *((int*)arg->valor));
        break;
    case TIPO_REGISTRO:
        sprintf(rtn, "Registro %i\n", ((Registro)arg->valor)->NUMERO);
        break;
    case TIPO_ETIQUETA:
        sprintf(rtn, "Etiqueta %s\n", ((char*)arg->valor));
        break;
    case TIPO_STRING:
        sprintf(rtn, "String %s\n", ((char*)arg->valor));
        break;
    default:
        fprintf(stderr, "Argumento con tipo ilegal %i. Rango esperado 1-3\n", arg->tipo);
        break;
    }
}
