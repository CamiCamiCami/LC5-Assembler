#include "ensamblador.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

char *interpreta_args(int argc, char **argv){
    if(argc < 2){
        printf("Falta el archivo a ensamblar\n");
        exit(1);
    } 
    if(argc > 2){
        printf("Demasiados archivos\n");
        exit(1);
    }
    
    return argv[1];
}

void agregarOperacion(ConsPrograma prog, char label[], Token tkns[], int c_tokens){
	if (c_tokens > 2){
		// Manejo de Error
		fprintf(stderr, "Mala cantidad de tokens. Esperaba 1-2 pero encontro %i\n", c_tokens);
		exit(1);
	}

	Operacion op = initOperacion(tkns, c_tokens);
	addOperacionPrograma(prog, op, label);
}

void agregarPseudoOp(ConsPrograma prog, char label[], Token tkns[], int c_tokens){
	if (c_tokens > 2){
		// Manejo de Error
		fprintf(stderr, "Mala cantidad de tokens. Esperaba 1-2 pero encontro %i\n", c_tokens);
		exit(1);
	}

	PseudoOp pso = deStringPseudoOp(tkns[0]);
	int argc = 0;
	Argumento* args = NULL;
	if (c_tokens == 2) {
		args = parsearArgumentos(tkns[1], &argc);
	}
	(efectoPseudoOp(pso))(prog, pso, label, args, argc);
}

#define ARCHIVO_SALIDA "../../../SimuladorCoba/miniPC/codigo.bin"

int main(int argc, char **argv){
    debug_print("main: Empieza el programa\n");
    char* path = interpreta_args(argc, argv);
    debug_print("main: Tenemos el path, %s\n", path);
    Escaner lector = initEscaner(path);
    debug_print("main: Tenemos el lector, %p\n", lector);
    

	char* lista[30];
	int cont = 0;
	ConsPrograma builder = initConstructorPrograma();
    for(unsigned int n_linea = 0; tieneProximoEscaner(lector);){
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
		
		switch (encontrarTipoToken(tkns[0])) {
		case INSTRUCCION:
			agregarOperacion(builder, NULL, tkns, c_tkns);
			break;
		case PSEUDOOP:
			agregarPseudoOp(builder, NULL, tkns, c_tkns);
			break;
		case ETIQUETA:
			switch (encontrarTipoToken(tkns[1])) {
			case INSTRUCCION:
				agregarOperacion(builder, tkns[0], tkns+1, c_tkns-1);
				break;
			case PSEUDOOP:
				agregarPseudoOp(builder, tkns[0], tkns+1, c_tkns-1);
				break;
			default:
				// Manejo de error
				fprintf(stderr, "Tipo de token desconocido\n");
				exit(1);
			}
			break;
		default:
			// Manejo de error
			fprintf(stderr, "Tipo de token desconocido\n");
			exit(1);
		}
	
        
        free(linea);
		for (int i = 0; i < c_tkns; i++)
			free(tkns[i]);
		free(tkns);
		n_linea++;
    }

	closeEscaner(lector);
	
	buildPrograma(builder, ARCHIVO_SALIDA);

	return 0;
}
