#include "seccion.h"

static addr TEXT_addr = 0;
static addr DATA_addr = 0;

static bool TEXT_has_addr = false;
static bool DATA_has_addr = false;


void setStartSeccion(Seccion s, addr starts) {
    switch (s)
    {
    case TEXT:
        TEXT_has_addr = true;
        TEXT_addr = starts;
        break;
    case DATA:
        DATA_has_addr = false;
        DATA_addr = starts;
        break;
    default:
        // Manejo de Error
        fprintf(stderr, "Codigo de seccion invalido %i\n", (int)s);
        exit(1);
    }
}

void asStringSeccion(Seccion s, char str[]) {
    switch (s) {
    case TEXT:
        strcpy(str, ".text");
        break;
    case DATA:
        strcpy(str, ".data");
        break;
    default:
        // Manejo de Error
        fprintf(stderr, "Codigo de seccion invalido %i\n", (int)s);
        exit(1);
    }
}

addr getStartSeccion(Seccion s) {
    switch (s) {
    case TEXT:
        if (TEXT_has_addr) {
            return TEXT_addr;
        }
        break;
    case DATA:
        if (DATA_has_addr) {
            return DATA_addr;
        }
        break;
    default:
        // Manejo de Error
        fprintf(stderr, "Codigo de seccion invalido %i\n", (int)s);
        exit(1);
    }

    // Manejo de Error
    char str[20];
    asStringSeccion(s, str);
    fprintf (stderr, "No se puede resolver %s porque todavia no se le asigno un inicio\n", str);
    exit(1);
}