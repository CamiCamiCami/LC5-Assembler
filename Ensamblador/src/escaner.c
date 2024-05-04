#include "escaner.h"
#include <errno.h>
#include "cola.h"


Escaner initEscaner(char path[]){
    Escaner escaner = fopen(path, "r");

    if (escaner == NULL){
        fprintf(stderr, "No se pudo abrir el archivo \"%s\", error Nro %i\n", path, errno);
        exit(1);
    }

    return escaner;
}

char* nextEscaner(Escaner Escaner){
    Cola cola = initCola();

    for(char c = fgetc(Escaner); c != '\n' && c != '\0' && !feof(Escaner); c = fgetc(Escaner)){
        if (ferror(Escaner)){
            // Si falla la lectura
            fprintf(stderr, "Error leyendo linea, error Nro %i\n", errno);
            exit(1);
        }
        // Pone el caracter en la cola
        char* pchr = malloc(sizeof(char));
        *pchr = c;
        pushCola(cola, pchr);
    }

    int largo_linea = lengthCola(cola);
    // el mas uno cuenta por el terminador a agregar
    char* linea = malloc((sizeof(char) * largo_linea) + 1);

    for(int i = 0; i < largo_linea; i++){
        char* pchr = (char*) popCola(cola);
        linea[i] = *pchr;
        free(pchr);
    }
    linea[largo_linea] = '\0';
    return linea;
}

void resetEscaner(Escaner escaner){
    rewind(escaner);
}