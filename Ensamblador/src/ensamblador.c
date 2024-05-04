#include "ensamblador.h"

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
    char path[] = interpreta_args(argc, argv);
    
}