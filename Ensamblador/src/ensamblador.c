#include "ensamblador.h"
#include "debug.h"

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
    for(char* linea = nextEscaner(lector); *linea != '\0'; linea = nextEscaner(lector)){
        printf("%s\n", linea);
        free(linea);
    }
}