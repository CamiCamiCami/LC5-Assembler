#include "pseudoIns.h"
#include "helpers_traduccion.h"
#include "argumentos.h"
#include "constructor_programa.h"
#include <ctype.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#define PRIMERA_PSI ORIG
#define ULTIMA_PSI END

void checkArgs(PseudoIns psi, Argumento args[], unsigned int argc){
    ArgsTipo esperado[5];
    unsigned int c_esperado = conseguirArgsTipoPseudoIns(psi, esperado);

    for (int i = 0; i < c_esperado; i++){
        char repr[50];
        argTipoComoStr(esperado[i], repr);
        debug_print("esperado[%i] = %s\n", i, repr);
    }
    for (int i = 0; i < argc; i++){
        char repr[50];
        argTipoComoStr(args[i]->tipo, repr);
        debug_print("args[%i]->tipo = %s\n", i, repr);
    }

    if(argc != c_esperado) {
        // Manejo de Error
        char str[15];
        comoStringPseudoIns(psi, str);
        fprintf(stderr, "Argumentos invalidos para pseudo operacion %s. Esperaba %i argumento/s pero recibio %i\n", str, c_esperado, argc);
        exit(1);
    }

    for (int i = 0; i < argc; i++){
        if (!argCoincideTipo(esperado[i], args[i])){
            // Manejo de Error
            char str_pso[10], str_esperado[50], str_recibido[50];
            comoStringPseudoIns(psi, str_pso);
            argTipoComoStr(esperado[i], str_esperado);
            argTipoComoStr(args[i]->tipo, str_recibido);
            fprintf(stderr, "Argumentos invalidos para operacion %s. en la posicion %i, esperaba tipo %s pero recibio tipo %s\n", str_pso, i+1, str_esperado, str_recibido);
            exit(1);
        }
    }
}


void efectuarPseudoOp (ConsPrograma prog, Token tkns[], unsigned int c_tkns, char label[]){
    bool err;
    PseudoIns psi = deStringPseudoIns(tkns[0], &err);
    if (err) {
        // Manejo de Error
        fprintf(stderr, "No pudo parsear token %s como pseudoinstruccion\n", tkns[0]);
        exit(1);
    }
    Argumento* args = NULL;
    unsigned int argc = 0;
    if (c_tkns == 2) {
        args = parsearArgumentos(tkns[1], &argc);
    }

    checkArgs(psi, args, argc);

    switch (psi) {
    case ORIG:
        if (label != NULL) {
            // Manejo de error
            fprintf(stderr, "No se admiten etiqutas que apunten a .orig\n");
            exit(1);
        }
        int addr_int = *((int*) args[0]->valor);
        if (addr_int < 0 || MAX_ADDR < addr_int){
            // Manejo de error
            fprintf(stderr, "Origen del programa no puede ser la direccion invalida %i. Fuera de rango 0-%i\n", addr_int, MAX_ADDR);
            exit(1);
        }
        setOrig(prog, (addr) addr_int);
        break;

    case FILL:
        if (args[0]->tipo & TIPO_ETIQUETA){
            addPointerPrograma(prog, args[0]->valor, label);
        } else {
            addLiteralPrograma(prog, (*((unsigned int*) args[0]->valor)), label);
        }
        break;

    case BLKW:  ; // <- El punto y como esta porque quiero declarar al inicio del case
        unsigned int c_blocks = *((unsigned int*)args[0]->valor);
        if (c_blocks < 1){
            // Manejo de error
            fprintf(stderr, ".blkw no puede reservar ua cantidad de %i\n", c_blocks);
            exit(1);
        }

        addLiteralPrograma(prog, (bin) 0, label);
        c_blocks--;
        for (; c_blocks > 0; c_blocks--){
            addLiteralPrograma(prog, (bin) 0, NULL);
        }
        break;
    case STRINGZ:   ; // <- El punto y como esta porque quiero declarar al inicio del case
        char* str = args[0]->valor;

        addLiteralPrograma(prog, (bin) str[0], label);
        for (int i = 1; str[i] != '\0'; i++) {
            addLiteralPrograma(prog, (bin) str[i], NULL);
        }
        addLiteralPrograma(prog, (bin) '\0', NULL);
        break;
    case END:
        if (label != NULL) {
            // Manejo de error
            fprintf(stderr, "No se admiten etiqutas que apunten a .end\n");
            exit(1);
        }
        programaLlegoAlFin(prog);
        break;
    
    default:
        // Manejo de Error
        fprintf(stderr, "Pseudo Instruccion invalida con codigo %i\n", psi);
        exit(1);
    }

    for (int i = 0; i < argc; i++) {
        freeArgumento(args[i]);
    }
    free(args);
}

PseudoIns deStringPseudoIns(char codigo[], bool* error){
	char cpy[strlen(codigo)];
    char repr[10];
	strcpy(cpy, codigo);
	for (char* p = cpy ; *p; ++p) *p = tolower(*p);
	
    for(int i = PRIMERA_PSI; i <= ULTIMA_PSI; i++){
        comoStringPseudoIns(i, repr);
        if(!strcmp(cpy, repr)){
            *error = false;
            return i;
        }
    }

    *error = true;
    return 0;
}

void comoStringPseudoIns(PseudoIns psi, char repr[]) {
    switch (psi) {
    case ORIG:;
        static const char code_orig[10] = ".orig";
        strcpy(repr, code_orig);
        break;
    case FILL:;
        static const char code_fill[10] = ".fill";
        strcpy(repr, code_fill);
        break;
    case BLKW:;
        static const char code_blwk[10] = ".blkw";
        strcpy(repr, code_blwk);
        break;
    case STRINGZ:;
        static const char code_stringz[10] = ".stringz";
        strcpy(repr, code_stringz);
        break;
    case END:;
        static const char code_end[10] = ".end";
        strcpy(repr, code_end);
        break;
    default:
        // Manejo de error
        fprintf(stderr, "pseudo operacion inexistente. Esperaba un codigo 0-%i, recibio %i\n", ULTIMA_PSI, psi);
        exit(1);
        break;
    }
}


unsigned int conseguirArgsTipoPseudoIns(PseudoIns psi, ArgsTipo args[5]) {
    switch (psi) {
    case ORIG:
        args[0] = TIPO_NUMERO;
        return 1U;
    case FILL:
        args[0] = TIPO_NUMERO | TIPO_ETIQUETA;
        return 1U;
    case BLKW:
        args[0] = TIPO_NUMERO;
        return 1U;
    case STRINGZ:
        args[0] = TIPO_STRING;
        return 1U;
    case END:
        return 0U;
    default:
        // Manejo de error
        fprintf(stderr, "pseudo operacion inexistente. Esperaba un codigo 1-%i, recibio %i\n", ULTIMA_PSI, psi);
        exit(1);
        break;
    }
}