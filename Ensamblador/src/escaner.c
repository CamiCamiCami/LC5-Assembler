#include <errno.h>
#include "escaner.h"
#include "cola.h"

#define DEBUG 0
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

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
    debug_print("nextEscaner: Tenemos Cola, %p\n", cola);

    for(char c = fgetc(Escaner); c != '\n' && c != '\0' && !feof(Escaner); c = fgetc(Escaner)){
        if (ferror(Escaner)){
            // Si falla la lectura
            fprintf(stderr, "Error leyendo linea, error Nro %i\n", errno);
            exit(1);
        }
        // Pone el caracter en la cola
        char* pchr = malloc(sizeof(char));
        *pchr = c;
        debug_print("nextEscaner: Tenemos pchr, %p, %c\n", pchr, c);
        pushCola(cola, pchr);
        debug_print("nextEscaner: pchr pusheado\n");
    }

    int largo_linea = lengthCola(cola);
    debug_print("nextEscaner: Tenemos largo_linea, %i\n", largo_linea);
    // el mas uno cuenta por el terminador a agregar
    char* linea = malloc((sizeof(char) * largo_linea) + 1);
    debug_print("nextEscaner: Tenemos linea, %p\n", linea);

    for(int i = 0; i < largo_linea; i++){
        char* pchr = (char*) popCola(cola);
        debug_print("nextEscaner, i=%i: Tenemos pchr, %p\n", i, pchr);
        linea[i] = *pchr;
        debug_print("nextEscaner, i=%i: Tenemos c, %c\n", i, *pchr);
        free(pchr);
        debug_print("nextEscaner, i=%i: pchr liberado\n", i);
    }
    linea[largo_linea] = '\0';
    freeCola(cola);
    return linea;
}

void resetEscaner(Escaner escaner){
    rewind(escaner);
}


bool tieneProximoEscaner(Escaner escaner){
	return !feof(escaner);
}

void closeEscaner(Escaner escaner){
	fclose(escaner);
}


