#include "pseudoop.h"
#include "helpers_traduccion.h"
#include <ctype.h>

#define C_CODIGOS_PSEUDOOP 4
static const char CODIGOS_PSEUDOOP[C_CODIGOS_PSEUDOOP][10] = {".orig", ".fill", ".blkw", ".end"};

PseudoOp deStringPseudoOp(char codigo[]){
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

void comoStringPseudoOp(PseudoOp pso, char repr[15]) {
    const char* codigo = CODIGOS_PSEUDOOP[pso-1];
    int i = 0;
    for (; codigo[i]; i++){
        repr[i] = codigo[i];
    }
    repr[i] = '\0';
}


AfectarPrograma efectoPseudoOp(PseudoOp pso) {
    switch (pso) {
    case ORIG:
        return efectoORIG;
    case FILL:
        return efectoFILL;
    case BLKW:
        return efectoBLKW;
    case END:
        return efectoEND;
    default:
        // Manejo de error
        fprintf(stderr, "pseudo operacion inexistente. Esperaba un codigo 1-%i, recibio %i\n", C_CODIGOS_PSEUDOOP, pso);
        exit(1);
        break;
    }
}


unsigned int conseguirArgsTipoPseudoOp(PseudoOp pso, ArgsTipo args[5]){
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