#include "ensamblador.h"

FILE* abrir_archivo(int argc, char **argv){
    if(argc < 2){
        printf("Falta el archivo a ensamblar\n");
        exit(1);
    } 
    if(argc > 2){
        printf("Demasiados archivos\n");
        exit(1);
    }
    
    FILE *f = fopen(argv[1], "r");
    
    if(f == NULL){
        printf("Error abriendo el archivo, %i\n", errno);
        exit(1);
    }

    return f;
}


int main(int argc, char **argv){
    FILE *f = abrir_archivo(argc, argv);
    
}