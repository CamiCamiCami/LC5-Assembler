#include "ensamblador.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

void interpreta_args(int argc, char **argv, char* from, char* to){
    if(argc < 2){
        printf("Falta el archivo a ensamblar\n");
        exit(1);
    } 
	if(argc < 3){
        printf("Falta el destino del ensamblado\n");
        exit(1);
    } 
    
	strcpy(from, argv[1]);
	strcpy(to, argv[2]);
}

void agregarOperacion(ConsPrograma prog, char label[], Token tkns[], int c_tokens) {
	bool err;
	Instruccion ins = deStringInstruccion(tkns[0], &err);
	if (err) {
		fprintf(stderr, "Instruccion desconocida, %s", tkns[0]);
		exit(1);
	}

	Operacion op;
	if (c_tokens > 1) {
		Argumento args[c_tokens-1];
		for (int i = 1; i < c_tokens; i++)
			args[i-1] = initArgumento(tkns[i]);
		op = initOperacion(ins, args, c_tokens-1);
	} else {
		op = initOperacion(ins, NULL, 0);
	}

	addOperacionPrograma(prog, op, label);
}

void agregarPseudoOp(ConsPrograma prog, char label[], Token tkns[], int c_tokens) {
	bool err;
	PseudoIns psi = deStringPseudoIns(tkns[0], &err);
	if (err) {
		fprintf(stderr, "Pseudo instruccion desconocida, %s", tkns[0]);
		exit(1);
	}

	if (c_tokens > 1) {
		Argumento args[c_tokens-1];
		for (int i = 1; i < c_tokens; i++)
			args[i-1] = initArgumento(tkns[i]);
		efectuarPseudoOp(prog, psi, args, c_tokens-1, label);
		for (int i = 0; i < c_tokens-1; i++)
			freeArgumento(args[i]);
	} else {
		efectuarPseudoOp(prog, psi, NULL, 0, label);
	}
	
	
}

bool esTokenInstruccion(Token tkn){
	bool err;
	deStringInstruccion(tkn, &err);
	return !err;
}

bool esTokenPseudoInstruccion(Token tkn) {
	bool err;
	deStringPseudoIns(tkn, &err);
	return !err;
}

int main(int argc, char **argv){
	initInstrucciones();
    debug_print("main: Empieza el programa\n");
	char from[50], to[50];
    interpreta_args(argc, argv, from, to);
    debug_print("main: Tenemos el path, %s\n", from);
	debug_print("main: Tenemos el destino, %s\n", to);
    Escaner lector = initEscaner(from);
    debug_print("main: Tenemos el lector, %p\n", lector);
    

	ConsPrograma builder = initConstructorPrograma();
    while(tieneProximoEscaner(lector)){
		char* linea = nextEscaner(lector);
		debug_print("main: Parseando linea -%s-\n", linea);

		int c_tkns;
		Token* tkns = parsearTokens(linea, &c_tkns);
		debug_print("main: Encontro %i tokens\n", c_tkns);
	    for (int i = 0; i < c_tkns; i++)
        	debug_print("main: Tokens[%i] = %s\n", i, tkns[i]);
		
		if (c_tkns == 0){
			debug_print("main: linea vacia, saltada\n");
			free(linea);
			free(tkns);
			continue;
		}
		

		if (esTokenInstruccion(tkns[0])){
			agregarOperacion(builder, NULL, tkns, c_tkns);
		} else if (esTokenPseudoInstruccion(tkns[0])) {
			agregarPseudoOp(builder, NULL, tkns, c_tkns);
		} else {
			if (esTokenInstruccion(tkns[1])){
				agregarOperacion(builder, tkns[0], tkns+1, c_tkns-1);
			} else if (esTokenPseudoInstruccion(tkns[1])) {
				agregarPseudoOp(builder, tkns[0], tkns+1, c_tkns-1);
			} else {
				fprintf(stderr, "Sintaxis invalida\n");
				exit(1);
			}
		}
	
        
        free(linea);
		for (int i = 0; i < c_tkns; i++)
			free(tkns[i]);
		free(tkns);
    }

	closeEscaner(lector);
	
	buildPrograma(builder, to);

	return 0;
}
