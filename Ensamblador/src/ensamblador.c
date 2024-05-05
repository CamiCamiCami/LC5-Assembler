#include "ensamblador.h"
#include "utils.h"

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


int main(int argc, char **argv){
    debug_print("main: Empieza el programa\n");
    char* path = interpreta_args(argc, argv);
    debug_print("main: Tenemos el path, %s\n", path);
    Escaner lector = initEscaner(path);
    debug_print("main: Tenemos el lector, %p\n", lector);
    
    char* linea = nextEscaner(lector);
    for(; *linea != '\0'; linea = nextEscaner(lector)){
        Instruccion ins = initInstruccion(linea);
        if(ins == NULL){
            continue;
        }
        if (ins->etiqueta){
            debug_print("main: instruccion con %s, %i, %p\n", ins->etiqueta, (int)ins->OPCODE, ins->args);
        } else {
            debug_print("main: instruccion con %p, %i, %p\n", ins->etiqueta, (int)ins->OPCODE, ins->args);
        }
        free(ins);
        free(linea);
    }
    free(linea);
}