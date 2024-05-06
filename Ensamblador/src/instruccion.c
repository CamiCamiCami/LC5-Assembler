#include "instruccion.h"
#include "utils.h"
#include <stdio.h>

#define CANT_CODIGOS_INS 23
static const char CODIGOS_INSTRUCCION[CANT_CODIGOS_INS][5] = {"add", "sub", "and", "or", "addi", "andi", "ori", "brp", "brz", "brn", "jr", "jalr", "trap", "reti", "not", "jal", "ld", "st", "str", "ldr", "lui", "lori", "ljmp"};

Instruccion deString(char token[]){
	char cpy[lengthToken(token)];
	comoStringToken(token, cpy);
	for (char* p = cpy ; *p; ++p) *p = tolower(*p);
	
    for(int i = 0; i < CANT_CODIGOS_INS; i++){
        if(!strcmp(cpy, CODIGOS_INSTRUCCION[i])){
            return i+1;
        }
    }
    return 0;
}

int conseguirArgsTipo(Instruccion INS, int args[5]){
    switch (INS)
    {
    case ADD:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case SUB:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case AND:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case OR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case ADDI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        return 3;
    case ANDI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        args[3] = TIPO_NUMERO;
        return 4;
    case ORI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        args[3] = TIPO_NUMERO;
        return 4;
    case BRp:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case BRz:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case BRn:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case JR:
        args[0] = TIPO_REGISTRO;
        return 1;
    case JALR:
        args[0] = TIPO_REGISTRO;
        return 1;
    case TRAP:
        args[0] = TIPO_REGISTRO;
        return 1;
    case RETI:
        return 0;
    case NOT:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        return 2;
    case JAL:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case LD:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_ETIQUETA;
        return 2;
    case ST:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_ETIQUETA;
        return 2;
    case LDR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case STR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case LUI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_NUMERO;
        return 2;
    case LORI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_NUMERO;
        return 2;
    case LJMP:
        args[0] = TIPO_ETIQUETA;
        return 1;
    default:
        fprintf(stderr, "Instruccion base INS inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, INS);
        exit(1);
        break;
    }
}

bin conseguirBase(Instruccion INS){
    switch (INS) {
    case ADD:
        return 0b0001000000000000;
    case SUB:
        return 0b0001000000001000;
    case AND:
        return 0b0001000000010000;
    case OR:
        return 0b0001000000011000;
    case ADDI:
        return 0b0101000000000000;
    case ANDI:
        return 0b0100000000000000;
    case ORI:
        return 0b1001000000000000;
    case BRp:
        return 0b0000010000000000;
    case BRz:
        return 0b0000000000000000;
    case BRn:
        return 0b0000100000000000;
    case JR:
        return 0b1010000000000000;
    case JALR:
        return 0b1010010000000000;
    case TRAP:
        return 0b1010100000000000;
    case RETI:
        return 0b1010110000000000;
    case NOT:
        return 0b1010000000100000;
    case JAL:
        return 0b1000000000000000;
    case LD:
        return 0b0010000000000000;
    case ST:
        return 0b0011000000000000;
    case LDR:
        return 0b0110000000000000;
    case STR:
        return 0b0110000000100000;
    case LUI:
        return 0b0111000000000000;
    case LORI:
        return 0b0111000100000000;
    case LJMP:
        return 101100000000000000;
    default:
        fprintf(stderr, "Instruccion base INS inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, INS);
        exit(1);
        break;
    }
}