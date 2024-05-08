#include "constructor_salida.h"

ConsSalida initConstructorSalida(char path[]){
    FILE* f = fopen(path, "wb");
    if (f == NULL){
		// Manejo de error
		fprintf(stderr, "Se produjo un error al abrir el archivo, errno: %i\n", errno);
		exit(1);
	}

    ConsSalida cons = malloc(sizeof(struct __constructor_salida));
    cons->alocado = 0;
    cons->largo = 0;
    cons->contenido = NULL;
    cons->file = f;
    return cons;
}

#define ALOCACION_PASO 20

void agregarConsSalida(ConsSalida cons, bin b) {
    if (cons->largo >= cons->alocado){
        int nuevo_alocado = cons->alocado + ALOCACION_PASO;
        cons->contenido = realloc(cons->contenido, sizeof(bin) * ALOCACION_PASO);
        cons->alocado = nuevo_alocado;
    }

    cons->contenido[cons->largo++] = b;
}

void construirSalida(ConsSalida cons){
    int escrito = fwrite(cons->contenido, sizeof(bin), cons->largo, cons->file);
    if (escrito < cons->largo){
        // Manejo de Error
        fprintf(stderr, "No se pudo escribir la totalidad del output. Escrito %i/%i", escrito, cons->largo);
        exit(1);
    }
    fclose(cons->file);
    free(cons->alocado);
    free(cons);
}