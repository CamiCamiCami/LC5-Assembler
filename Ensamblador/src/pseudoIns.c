#include "pseudoIns.h"
#include "helpers_traduccion.h"
#include "argumentos.h"
#include <ctype.h>

#define C_CODIGOS_PSEUDOOP 4
static const char CODIGOS_PSEUDOOP[C_CODIGOS_PSEUDOOP][10] = {".orig", ".fill", ".blkw", ".end"};

void checkArgs(PseudoIns psi, Argumento args[], unsigned int argc){
    ArgsTipo esperado[5];
    unsigned int c_esperado = conseguirArgsTipoPseudoOp(psi, esperado);

    if(argc != c_esperado){
        // Manejo de Error
        char str[15];
        comoStringPseudoOp(psi, str);
        fprintf(stderr, "Argumentos invalidos para pseudo operacion %s. Esperaba %i argumento/s pero recibio %i\n", str, c_esperado, argc);
        exit(1);
    }

    for (int i = 0; i < argc; i++){
        if (esperado[i] != args[i]->tipo){
            // Manejo de Error
            char str_pso[5], str_esperado[10], str_recibido[10];
            comoStringPseudoIns(psi, str_pso);
            argTipoComoStr(esperado[i], str_esperado);
            argTipoComoStr(args[i]->tipo, str_recibido);
            fprintf(stderr, "Argumentos invalidos para operacion %s. en la posicion %i, esperaba tipo %s pero recibio tipo %s\n", str_pso, i+1, str_esperado, str_recibido);
            exit(1);
        }
    }
}


void efectuarPseudoOp (ConsPrograma prog, Token tkns[], unsigned int c_tkns, char label[]){
    PseudoIns psi = deStringPseudoIns(tkns[0]);
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
        return efectoFILL;
    case BLKW:
        return efectoBLKW;
    case END:
        if (label != NULL) {
            // Manejo de error
            fprintf(stderr, "No se admiten etiqutas que apunten a .end\n");
            exit(1);
        }
        prog->reached_end = true;
        break;
    
    default:
        return NULL_PSO;
    }

    for(int i = 0; i < argc; i++){
        freeArgumento(args[i]);
    }
}


PseudoIns deStringPseudoIns(char codigo[]){
	char cpy[strlen(codigo)];
	strcpy(cpy, codigo);
	for (char* p = cpy ; *p; ++p) *p = tolower(*p);
	
    for(int i = 0; i < C_CODIGOS_PSEUDOOP; i++){
        if(!strcmp(cpy, CODIGOS_PSEUDOOP[i])){
            return i+1;
        }
    }
    return NULL_INS;
}

void comoStringPseudoIns(PseudoIns psi, char repr[]) {
    const char* codigo = CODIGOS_PSEUDOOP[psi-1];
    int i = 0;
    for (; codigo[i]; i++){
        repr[i] = codigo[i];
    }
    repr[i] = '\0';
}


AfectarPrograma efectoPseudoIns(PseudoIns psi, ConsPrograma prog) {
    
}


unsigned int conseguirArgsTipoPseudoIns(PseudoIns psi, ArgsTipo args[5]) {
    switch (pso) {
    case ORIG:
        args[0] = TIPO_NUMERO;
        return 1U;
    case FILL:
        args[0] = TIPO_NUMERO;
        return 1U;
    case BLKW:
        args[0] = TIPO_NUMERO;
        return 1U;
    case END:
        return 0U;
    default:
        // Manejo de error
        fprintf(stderr, "pseudo operacion inexistente. Esperaba un codigo 1-%i, recibio %i\n", C_CODIGOS_PSEUDOOP, pso);
        exit(1);
        break;
    }
}