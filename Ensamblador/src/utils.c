#include "utils.h"

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

void argTipoComoStr(unsigned char tipo, char repr[10]){
	switch (tipo) {
	case 1:
		strcpy(repr, "Numero");
		break;
	case 2:
		strcpy(repr, "Registro");
		break;
	case 3:
		strcpy(repr, "Etiqueta");
		break;
	default:
		// Manejo de Error
		fprintf(stderr, "Esperaba un tipo en el rango 1-3 pero recibio %u\n", tipo);
		exit(1);
		break;
	}
}