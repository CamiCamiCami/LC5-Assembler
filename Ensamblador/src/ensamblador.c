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

#define TABLE_SIZE 11
#define ORIG 3000

void comoStr(bin word, char repr[17]){
	bin k;
	for(int c = 15; c >= 0; c--){
		k = word >> c;

		if(k & 1){
			repr[c] = '1';
		} else {
			repr[c] = '0';
		}
	}
	repr[16] = '\0';
}

int main(int argc, char **argv){
    debug_print("main: Empieza el programa\n");
    char* path = interpreta_args(argc, argv);
    debug_print("main: Tenemos el path, %s\n", path);
    Escaner lector = initEscaner(path);
    debug_print("main: Tenemos el lector, %p\n", lector);
    

	SymTable tabla = initSymTable(TABLE_SIZE);
	char* lista[10];
	int cont = 0;
    Cola cola = initCola();
    addr dir_act = ORIG;
    while(tieneProximoEscaner(lector)){
		char* linea = nextEscaner(lector);
		debug_print("parseando linea \"%s\"\n", linea);
		Token tokens[3];
		int c_tokens = parsearTokens(linea, tokens);
		debug_print("encontro %i tokens\n", c_tokens);
		if (c_tokens == 0){
			free(linea);
			continue;
		}
		
		Instruccion opcode = deString(tokens[0]);
		Argumento* args = NULL;
		int argc = 0;
		
		if(opcode == NULL_INS){
			if (!(c_tokens == 2 || c_tokens == 3)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 2-3 pero encontro %i\n", linea, c_tokens);
				exit(1);
			}
			
			debug_print("etiqueta %s en direccion %i\n", tokens[0], dir_act);
			insertSymTable(tabla, tokens[0], dir_act);
			lista[cont++] = tokens[0];
			opcode = deString(tokens[1]);
			if (opcode == NULL_INS){
				// Manejo de Error
				fprintf(stderr, "Sintaxis invalida, esperaba una instruccion pero encontro %s", tokens[1]);
				exit(1);
			}
			if(c_tokens == 3) {
				args = parsearArgumentos(tokens[2], &argc);
			}		
		} else {
			if (!(c_tokens == 1 || c_tokens == 2)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 1-2 pero encontro %i\n", linea, c_tokens);
				exit(1);
			}
			if (c_tokens == 2){
				args = parsearArgumentos(tokens[1], &argc);	
			}
		}
		
        Operacion op = initOperacion(opcode, args, argc);
        pushCola(cola, op);
        free(linea);
        dir_act++;
    }

	char str[17];
	for(int pos = ORIG; pos < cont+ORIG; pos++){
		debug_print("%s: %i\n", lista[pos], searchSymTable(tabla, lista[pos]));
		Operacion op = popCola(cola);
		bin traduccion = traducirOperacion(op, tabla, ORIG, pos);
		comoStr(traduccion, str);
		debug_print("%s\n", str);
	}
    debug_print("Se pushearon %i instrucciones\n", lengthCola(cola));

}
