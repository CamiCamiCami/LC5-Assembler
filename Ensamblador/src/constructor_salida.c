#include "constructor_salida.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

ConsSalida initConstructorSalida(char path[], addr orig){
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

    agregarConsSalida(cons, orig);

    return cons;
}

#define ALOCACION_PASO 20

void agregarConsSalida(ConsSalida cons, bin b) {
    if (cons->largo >= cons->alocado){
        int nuevo_alocado = cons->alocado + ALOCACION_PASO;
        cons->contenido = realloc(cons->contenido, sizeof(bin) * nuevo_alocado);
        cons->alocado = nuevo_alocado;
    }

    bin change_endian = (b << 8) + (b >> 8);

    cons->contenido[cons->largo++] = change_endian;
}

void construirSalida(ConsSalida cons){
    for (int i = 0; i < cons->largo; i++) {
        char bin[17];
        comoStr(cons->contenido[i], bin);
        debug_print("%s\n", bin);
    }
    int escrito = fwrite(cons->contenido, sizeof(bin), cons->largo, cons->file);
    if (escrito < cons->largo){
        // Manejo de Error
        fprintf(stderr, "No se pudo escribir la totalidad del output. Escrito %i/%i", escrito, cons->largo);
        exit(1);
    }
    fclose(cons->file);
    free(cons->contenido);
    free(cons);
}