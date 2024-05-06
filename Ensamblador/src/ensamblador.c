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
    addr dir_act = 0;
    while(tieneProximoEscaner(lector)){
		char* linea = nextEscaner(lector);
		debug_print("parseando linea \"%s\"\n", linea);
		Token tokens[3];
		int c_tokens = parsearTokens(linea, tokens);
		debug_print("encontro %i tokens\n", c_tokens);
		if (c_tokens == 0){
			continue;
		}
		
		InstruccionProcesador opcode = deString(tokens[0]);
		Argumento* args = NULL;
		
		if(opcode == NULL){
			if (!(c_tokens == 2 || c_tokens == 3)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 2-3 pero encontro %i\n", linea, c_tokens);
				exit(1);
			}
			
			debug_print("etiqueta %s en direccion %i\n", tokens[0], dir_act);
			insertSymTable(tabla, tokens[0], dir_act);
			lista[cont++] = tokens[0];
			opcode = deString(tokens[1]);
			if (opcode == NULL){
				// Manejo de Error
				fprintf(stderr, "Sintaxis invalida, esperaba una instruccion pero encontro %s", tokens[1]);
				exit(1);
			}
			if(c_tokens == 3) {
				args = parsearArgumentos(tokens[2]);
			}		
		} else {
			if (!(c_tokens == 1 || c_tokens == 2)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 1-2 pero encontro %i\n", linea, c_tokens);
				exit(1);
			}
			if (c_tokens == 2){
				args = parsearArgumentos(tokens[1]);	
			}
		}
		
        Instruccion ins = initInstruccion(opcode, args);
        pushCola(cola, ins);
        free(linea);
        dir_act++;
    }

	for(int i = 0; i < cont; i++){
		debug_print("%s: %i\n", lista[i], searchSymTable(tabla, lista[i]));
	}
    debug_print("Se pushearon %i instrucciones\n", lengthCola(cola));




}
