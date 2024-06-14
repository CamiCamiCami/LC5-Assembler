#include "utils.h"
#include "instruccion.h"
#include "pseudoins.h"
#include "argumentos.h"

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