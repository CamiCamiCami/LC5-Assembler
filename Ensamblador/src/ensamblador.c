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

	addProgama(prog, op, OPERACION, label);
}

void agregarAlias(ConsPrograma prog, char label[], Token tkns[], int c_tokens) {
	bool err;
	Alias alias = deStringAlias(tkns[0], &err);
	if (err) {
		fprintf(stderr, "Alias desconocido, %s", tkns[0]);
		exit(1);
	}

	AliasOp aop;
	if (c_tokens > 1) {
		Argumento args[c_tokens-1];
		for (int i = 1; i < c_tokens; i++)
			args[i-1] = initArgumento(tkns[i]);
		aop = initAliasOperacion(alias, args, c_tokens-1);
	} else {
		aop = initAliasOperacion(alias, NULL, 0);
	}

	addProgama(prog, aop, ALIAS, label);
}

void agregarPseudoOp(ConsPrograma prog, char label[], Token tkns[], int c_tokens) {
	bool err;
	PseudoIns psi = deStringPseudoIns(tkns[0], &err);
	if (err) {
		fprintf(stderr, "Pseudo instruccion desconocida, %s", tkns[0]);
		exit(1);
	}
	if (c_tokens > 2) {
		fprintf(stderr, "Demasiados argumentos para %s. Esperaba 0-1 pero recibio %i", psi->name, c_tokens);
		exit(1);
	}

	Argumento arg = NULL;
	if (c_tokens == 2) {
		arg = initArgumento(tkns[1]);
	}

	PseudoOp pso = initPseudoOp(psi, arg);
	addProgama(prog, pso, PSEUDOINS, label);
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

bool esTokenAlias(Token tkn) {
	bool err;
	deStringAlias(tkn, &err);
	return !err;
}

int main(int argc, char **argv){
	initConstantesGlobales();
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
		} else if (esTokenAlias(tkns[0])) {
			agregarAlias(builder, NULL, tkns, c_tkns);
		} else {
			Token label = tkns[0];
			Token* comando = tkns+1;
			if (esTokenInstruccion(comando[0])) {
				agregarOperacion(builder, label, comando, c_tkns-1);
			} else if (esTokenPseudoInstruccion(comando[0])) {
				agregarPseudoOp(builder, label, comando, c_tkns-1);
			} else if (esTokenAlias(comando[0])) {
				agregarAlias(builder, label, comando, c_tkns-1);
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
