#include "utils.h"
#include "pseudoIns.h"
#include "argumentos.h"
#include "helpers_traduccion.h"
#include <ctype.h>


Instruccion initInstruccion(char name[10], int argc, int argstipos[3], bin base, Traductor traductor){
    Instruccion new = malloc(sizeof(struct __instruccion));
    strcpy(new->name, name);
    new->argc = argc;
    for (int i = 0; i < argc; i++) {
        new->args_tipos[i] = argstipos[i];
    }
    new->base = base;
    new->traductor = traductor;
    return new;
}


#define getInstrucciones() {AND, OR, ADD, NOR, ANN, XOR, SUB, SLT, ADDI, LUI, LORI, LD, ST, LDR, STR, BRn, BRz, BRp, BRnz, BRnp, BRzp, JUMP, JR, JAL, JALR, TRAP, RTI, NULL};

Instruccion deStringInstruccion(char token[], bool* error){
	Instruccion instrucciones[] = getInstrucciones();
	char cpy[strlen(token)];

	strcpy(cpy, token);
	for (char* p = cpy ; *p; ++p) *p = tolower(*p);
	
    for(int i = 0; instrucciones[i]; i++){
        if(!strcmp(cpy, instrucciones[i]->name)){
            *error = false;
            return instrucciones[i];
        }
    }
    *error = true;
    return NULL;
}

void initInstrucciones() {
	int tresRegistros[] = {TIPO_REGISTRO, TIPO_REGISTRO, TIPO_REGISTRO};
	int unicaEtiqueta[] = {TIPO_ETIQUETA};

	AND = initInstruccion(	"and",	  3, tresRegistros, 									   0b0001000000000000, traducirArimetica);
	OR = initInstruccion(	"or", 	  3, tresRegistros, 									   0b0001000000000001, traducirArimetica);
	ADD = initInstruccion(	"i.add",  3, tresRegistros, 									   0b0001000000000010, traducirArimetica);
	NOR = initInstruccion(	"nor", 	  3, tresRegistros, 									   0b0001000000000011, traducirArimetica);
	ANN = initInstruccion(	"ann", 	  3, tresRegistros,									 	   0b0001000000000100, traducirArimetica);
 	XOR = initInstruccion(	"xor", 	  3, tresRegistros, 									   0b0001000000000101, traducirArimetica);
 	SUB = initInstruccion(	"sub", 	  3, tresRegistros, 									   0b0001000000000110, traducirArimetica);
 	SLT = initInstruccion(	"slt", 	  3, tresRegistros, 									   0b0001000000000111, traducirArimetica);
 	ADDI = initInstruccion(	"i.addi", 3, (int[]){TIPO_REGISTRO, TIPO_REGISTRO, TIPO_NUMERO},   0b0101000000000000, traducirADDI);
 	LUI = initInstruccion(	"lui", 	  2, (int[]){TIPO_REGISTRO, TIPO_NUMERO}, 				   0b0100000000000000, traducirLUI);
 	LORI = initInstruccion(	"lori",   2, (int[]){TIPO_REGISTRO, TIPO_NUMERO}, 				   0b0100000100000000, traducirLORI);
 	LD = initInstruccion(	"ld", 	  2, (int[]){TIPO_REGISTRO, TIPO_ETIQUETA}, 			   0b0010000000000000, traducirLD);
 	ST = initInstruccion(	"st", 	  2, (int[]){TIPO_REGISTRO, TIPO_ETIQUETA}, 			   0b0011000000000000, traducirST);
 	LDR = initInstruccion(	"ldr", 	  3, (int[]){TIPO_REGISTRO, TIPO_REGISTRO, TIPO_NUMERO},   0b0110000000000000, traducirLDR);
 	STR = initInstruccion(	"str", 	  3, (int[]){TIPO_REGISTRO, TIPO_REGISTRO, TIPO_NUMERO},   0b0111000000000000, traducirSTR);
 	BRn = initInstruccion(	"brn", 	  1, unicaEtiqueta, 									   0b0000001000000000, traducirBranch);
 	BRz = initInstruccion(	"brz", 	  1, unicaEtiqueta, 									   0b0000010000000000, traducirBranch);
 	BRp = initInstruccion(	"brp", 	  1, unicaEtiqueta, 									   0b0000100000000000, traducirBranch);
 	BRnz = initInstruccion(	"brnz",   1, unicaEtiqueta, 									   0b0000110000000000, traducirBranch);
 	BRnp = initInstruccion(	"brnp",   1, unicaEtiqueta, 									   0b0000101000000000, traducirBranch);
 	BRzp = initInstruccion(	"brzp",   1, unicaEtiqueta, 									   0b0000011000000000, traducirBranch);
 	JUMP = initInstruccion(	"jump",   1, unicaEtiqueta, 									   0b1000100000000000, traducirJUMP);
 	JR = initInstruccion(	"jr",  	  1, (int[]){TIPO_REGISTRO}, 							   0b1000000000000000, traducirJR);
	JAL = initInstruccion(	"jal", 	  1, (int[]){TIPO_REGISTRO},							   0b1001100000000000, traducirJR);
 	JALR = initInstruccion(	"jalr",   1, unicaEtiqueta, 									   0b1001000000000000, traducirJALR);
 	TRAP = initInstruccion(	"trap",   1, (int[]){TIPO_NUMERO}, 								   0b1010000000000000, traducirTRAP);
 	RTI = initInstruccion(	"rti", 	  0, NULL, 												   0b1011000000000000, traducirRTI);
}


void comoStr(bin word, char repr[17]){
	bin k;
	for(int c = 15; c >= 0; c--){
		k = word >> c;

		if(k & 1){
			repr[15-c] = '1';
		} else {
			repr[15-c] = '0';
		}
	}
	repr[16] = '\0';
}


void intComoStr(int word, char repr[33]){
    bin k;
	for(int c = 31; c >= 0; c--){
		k = word >> c;

		if(k & 1){
			repr[31-c] = '1';
		} else {
			repr[31-c] = '0';
		}
	}
	repr[32] = '\0';
}


void argTipoComoStr(ArgsTipo tipo, char repr[50]){
	const char num_str[] = "Numero";
	const char reg_str[] = "Registro";
	const char etq_str[] = "Etiqueta";
	const char str_str[] = "String";

	if (TIPO_NUMERO & tipo) {
		strcpy(repr, num_str);
		tipo -= TIPO_NUMERO;
		argTipoComoStr(tipo, repr+strlen(num_str)+1);
		repr[strlen(num_str)] = repr[strlen(num_str) + 1] == '\0' ? '\0' : '/';
	} else if (TIPO_REGISTRO & tipo) {
		strcpy(repr, reg_str);
		tipo -= TIPO_REGISTRO;
		argTipoComoStr(tipo, repr+strlen(reg_str)+1);
		repr[strlen(reg_str)] = repr[strlen(reg_str) + 1] == '\0' ? '\0' : '/';
	} else if (TIPO_ETIQUETA & tipo) {
		strcpy(repr, etq_str);
		tipo -= TIPO_ETIQUETA;
		argTipoComoStr(tipo, repr+strlen(etq_str)+1);
		repr[strlen(etq_str)] = repr[strlen(etq_str) + 1] == '\0' ? '\0' : '/';
	} else if (TIPO_STRING & tipo) {
		strcpy(repr, "String");
		tipo -= TIPO_STRING;
		argTipoComoStr(tipo, repr+strlen(str_str)+1);
		repr[strlen(str_str)] = repr[strlen(str_str) + 1] == '\0' ? '\0' : '/';
	} else if (tipo == 0) {
		repr[0] = '\0';
	} else {
		// Manejo de Error
		fprintf(stderr, "Esperaba un tipo en el rango 1-3 pero recibio %u\n", tipo);
		exit(1);
	}
}


TipoToken encontrarTipoPrimerToken(Token tkn){
	bool err_parse_ins;
	bool err_parse_psi;
	deStringInstruccion(tkn, &err_parse_ins);
	deStringPseudoIns(tkn, &err_parse_psi);
	if (!err_parse_ins){
		return INSTRUCCION;
	} else if (!err_parse_psi){
		return PSEUDOOP;
	} else {
		return ETIQUETA;
	}
}