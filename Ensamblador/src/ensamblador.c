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
#define ORIG (short) 3000
#define ARCHIVO_SALIDA "../obj/codigo.bin"

int main(int argc, char **argv){
    debug_print("main: Empieza el programa\n");
    char* path = interpreta_args(argc, argv);
    debug_print("main: Tenemos el path, %s\n", path);
    Escaner lector = initEscaner(path);
    debug_print("main: Tenemos el lector, %p\n", lector);
    

	SymTable tabla = initSymTable(TABLE_SIZE);
	char* lista[30];
	int cont = 0;
    Cola cola = initCola();
    for(unsigned int n_linea = 0; tieneProximoEscaner(lector);){
		char* linea = nextEscaner(lector);
		debug_print("main: Parseando linea -%s-\n", linea);
		int c_tkns;
		Token* tkns = parsearTokens(linea, &c_tkns);
	    for (int i = 0; i < c_tkns; i++){
        	debug_print("main: Tokens[%i] = %s\n", i, tkns[i]);
    	}
		debug_print("main: Encontro %i tokens\n", c_tkns);
		
		if (c_tkns == 0){
			debug_print("main: linea vacia, saltada\n");
			free(linea);
			for (int i = 0; i < c_tkns; i++)
				free(tkns[i]);
			free(tkns);
			continue;
		}
		
		Instruccion opcode = deString(tkns[0]);
		Argumento* args = NULL;
		int argc = 0;
		
		if(opcode == NULL_INS){
			if (!(c_tkns == 2 || c_tkns == 3)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 2-3 pero encontro %i\n", linea, c_tkns);
				exit(1);
			}
			
			debug_print("main: etiqueta %s en linea %i\n", tkns[0], n_linea);
			insertSymTable(tabla, tkns[0], n_linea);
			char* ptr = malloc(sizeof(char) * (strlen(tkns[0]) + 1));
			strcpy(ptr, tkns[0]);
			lista[cont++] = ptr;
			opcode = deString(tkns[1]);
			if (opcode == NULL_INS){
				// Manejo de Error
				fprintf(stderr, "Sintaxis invalida, esperaba una instruccion pero encontro %s\n", tkns[1]);
				exit(1);
			}
			if(c_tkns == 3) {
				args = parsearArgumentos(tkns[2], &argc);
			}		
		} else {
			if (!(c_tkns == 1 || c_tkns == 2)){
				// Manejo de Error
				fprintf(stderr, "Mala cantidad de tokens en linea \"%s\". Esperaba 1-2 pero encontro %i\n", linea, c_tkns);
				exit(1);
			}
			if (c_tkns == 2){
				args = parsearArgumentos(tkns[1], &argc);	
			}
		}
		
        Operacion op = initOperacion(opcode, args, argc);
        pushCola(cola, op);
        free(linea);
		for (int i = 0; i < c_tkns; i++)
			free(tkns[i]);
		free(tkns);
		n_linea++;
    }

    debug_print("main: Se pushearon %i instrucciones\n", lengthCola(cola));

	for(int i = 0; i < cont; i++){
		debug_print("main: %s: %i\n", lista[i], searchSymTable(tabla, lista[i]));
		free(lista[i]);
	}


	FILE* f = fopen(ARCHIVO_SALIDA, "wr");
	short pos = ORIG;
	fwrite(&pos, sizeof(short), 1, f);
	char str[17];
	for(; !emptyCola(cola); pos++){
		Operacion op = popCola(cola);
		bin traduccion = traducirOperacion(op, tabla, ORIG, pos);
		fwrite(&traduccion, sizeof(bin), 1, f);
		comoStr(traduccion, str);
		debug_print("main: %s\n", str);
		free(op);
	}
	fclose(f);

	return 0;
}
