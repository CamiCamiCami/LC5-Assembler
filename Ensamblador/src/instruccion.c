#include "instruccion.h"
#include <ctype.h>
#include "helpers_traduccion.h"

#define PRIMERA_INS IAND
#define ULTIMA_INS IRTI
#define CANT_CODIGOS_INS 24


void comoStringInstruccion(Instruccion ins, char str[10]){
    char name[5];
    switch (ins) {
    case IAND:;
        static const char code_and[10] = "i.and";
        strcpy(str, code_and);
        break;
    case IOR:;
        static const char code_or[10] = "i.or";
        strcpy(str, code_or);
        break;
    case IADD:;
        static const char code_add[10] = "i.add";
        strcpy(str, code_add);
        break;
    case INOR:;
        static const char code_nor[10] = "nor";
        strcpy(str, code_nor);
        break;
    case IANN:;
        static const char code_ann[10] = "ann";
        strcpy(str, code_ann);
        break;
    case IXOR:;
        static const char code_xor[10] = "xor";
        strcpy(str, code_xor);
        break;
    case ISUB:;
        static const char code_sub[10] = "i.sub";
        strcpy(str, code_sub);
        break;
    case ISLT:;
        static const char code_slt[10] = "slt";
        strcpy(str, code_slt);
        break;
    case IADDI:;
        static const char code_addi[10] = "i.addi";
        strcpy(str, code_addi);
        break;
    case ILUI:;
        static const char code_lui[10] = "lui";
        strcpy(str, code_lui);
        break;
    case ILORI:;
        static const char code_lori[10] = "lori";
        strcpy(str, code_lori);
        break;
    case ILD:;
        static const char code_ld[10] = "ld";
        strcpy(str, code_ld);
        break;
    case IST:;
        static const char code_st[10] = "st";
        strcpy(str, code_st);
        break;
    case ILDR:;
        static const char code_ldr[10] = "ldr";
        strcpy(str, code_ldr);
        break;
    case ISTR:;
        static const char code_str[10] = "str";
        strcpy(str, code_str);
        break;
    case IBRz:;
        static const char code_brz[10] = "brz";
        strcpy(str, code_brz);
        break;
    case IBRp:;
        static const char code_brp[10] = "brp";
        strcpy(str, code_brp);
        break;
    case IBRn:;
        static const char code_brn[10] = "brn";
        strcpy(str, code_brn);
        break;
    case IBRnz:;
        static const char code_brnz[10] = "brnz";
        strcpy(str, code_brnz);
        break;
    case IBRnp:;
        static const char code_brnp[10] = "brnp";
        strcpy(str, code_brnp);
        break;
    case IBRzp:;
        static const char code_brzp[10] = "brzp";
        strcpy(str, code_brzp);
        break;
    case IJUMP:;
        static const char code_jump[10] = "jump";
        strcpy(str, code_jump);
        break;
    case IJAL:;
        static const char code_jal[10] = "jal";
        strcpy(str, code_jal);
        break;
    case IJR:;
        static const char code_jr[10] = "jr";
        strcpy(str, code_jr);
        break;
    case IJALR:;
        static const char code_jalr[10] = "jalr";
        strcpy(str, code_jalr);
        break;
    case ITRAP:;
        static const char code_trap[10] = "trap";
        strcpy(str, code_trap);
        break;
    case IRTI:;
        static const char code_reti[10] = "rti";
        strcpy(str, code_reti);
        break;  
    default:
        fprintf(stderr, "Instruccion inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, ins);
        exit(1);
        break;
    }
}

Instruccion deStringInstruccion(char token[], bool* error){
	char cpy[strlen(token)];
    char repr[10];

	strcpy(cpy, token);
	for (char* p = cpy ; *p; ++p) *p = tolower(*p);
	
    for(int i = PRIMERA_INS; i <= ULTIMA_INS; i++){
        comoStringInstruccion((Instruccion) i, repr);
        if(!strcmp(cpy, repr)){
            *error = false;
            return i;
        }
    }
    *error = true;
    return 0;
}

int conseguirArgsTipoInstruccion(Instruccion INS, int args[5]){
    switch (INS)
    {
    case IAND:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case IOR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case IADD:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case INOR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case IANN:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case IXOR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case ISUB:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case ISLT:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_REGISTRO;
        return 3;
    case IADDI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        return 3;
    case ILUI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_NUMERO;
        return 2;
    case ILORI:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_NUMERO;
        return 2;
    case ILD:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_ETIQUETA;
        return 2;
    case IST:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_ETIQUETA;
        return 2;
    case ILDR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        return 3;
    case ISTR:
        args[0] = TIPO_REGISTRO;
        args[1] = TIPO_REGISTRO;
        args[2] = TIPO_NUMERO;
        return 3;
    case IBRp:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IBRz:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IBRn:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IBRnz:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IBRnp:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IBRzp:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IJUMP:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IJAL:
        args[0] = TIPO_ETIQUETA;
        return 1;
    case IJR:
        args[0] = TIPO_REGISTRO;
        return 1;
    case IJALR:
        args[0] = TIPO_REGISTRO;
        return 1;
    case ITRAP:
        args[0] = TIPO_REGISTRO;
        return 1;
    case IRTI:
        return 0;
    default:
        fprintf(stderr, "Instruccion inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, INS);
        exit(1);
        break;
    }
}

bin conseguirBaseInstruccion(Instruccion INS){
    switch (INS) {
    case IAND:
        return 0b0001000000000000;
    case IOR:
        return 0b0001000000000001;
    case IADD:
        return 0b0001000000000010;
    case INOR:
        return 0b0001000000000011;
    case IANN:
        return 0b0001000000000100;
    case IXOR:
        return 0b0001000000000101;
    case ISUB:
        return 0b0001000000000110;
    case ISLT:
        return 0b0001000000000111;
    case IADDI:
        return 0b0101000000000000;
    case ILUI:
        return 0b0100000000000000;
    case ILORI:
        return 0b0100000100000000;
    case ILD:
        return 0b0010000000000000;
    case IST:
        return 0b0011000000000000;
    case ILDR:
        return 0b0110000000000000;
    case ISTR:
        return 0b0111000000000000;
    case IBRp:
        return 0b0000001000000000;
    case IBRz:
        return 0b0000010000000000;
    case IBRn:
        return 0b0000100000000000;
    case IBRnz:
        return 0b0000110000000000;
    case IBRnp:
        return 0b0000101000000000;
    case IBRzp:
        return 0b0000011000000000;
    case IJUMP:
        return 0b1000100000000000;
    case IJR:
        return 0b1000000000000000;
    case IJAL:
        return 0b1001100000000000;
    case IJALR:
        return 0b1001000000000000;
    case ITRAP:
        return 0b1010000000000000;
    case IRTI:
        return 0b1011000000000000;
    default:
        fprintf(stderr, "Instruccion base INS inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, INS);
        exit(1);
        break;
    }
}


Traductor conseguirTraductorInstruccion(Instruccion INS){
	switch (INS) {
        case IAND:
	        return traducirArimetica;
	    case IOR:
	        return traducirArimetica;
		case IADD:
        	return traducirArimetica;
        case INOR:
	        return traducirArimetica;
        case IANN:
            return traducirArimetica;
        case IXOR:
            return traducirArimetica;
	    case ISUB:
	        return traducirArimetica;
        case ISLT:
            return traducirArimetica;
	    case IADDI:
	        return traducirADDI;
        case ILUI:
	        return traducirLUI;
	    case ILORI:
	        return traducirLORI;
        case ILD:
	        return traducirLD;
	    case IST:
	        return traducirST;
	    case ILDR:
	        return traducirLDR;
	    case ISTR:
	        return traducirSTR;
	    case IBRp:
	        return traducirBranch;
	    case IBRz:
	        return traducirBranch;
	    case IBRn:
	        return traducirBranch;
        case IBRnz:
	        return traducirBranch;
	    case IBRnp:
	        return traducirBranch;
	    case IBRzp:
	        return traducirBranch;
        case IJUMP:
            return traducirJUMP;
	    case IJR:
	        return traducirJR;
        case IJAL:
	        return traducirJAL;
	    case IJALR:
	        return traducirJALR;
	    case ITRAP:
	        return traducirTRAP;
	    case IRTI:
	        return traducirRTI;
	    default:
	        fprintf(stderr, "Instruccion base INS inexistente. Esperaba un codigo 1-%i, recibio %i\n", CANT_CODIGOS_INS, INS);
			exit(1);
	}
}
