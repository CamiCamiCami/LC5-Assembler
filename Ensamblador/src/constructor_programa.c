#include "constructor_programa.h"
#include "constructor_salida.h"
#include "cola.h"
#include "symtable.h"
#include "full_address.h"
#include "operacion.h"
#include "seccion.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#define DEFAULT_ORIG 3000

ConsPrograma initConstructorPrograma() {
    ConsPrograma prog = malloc(sizeof(struct __constructor_programa));

    prog->data = initCola();
    prog->text = initCola();
    prog->symtable = initSymTable(0);
    prog->orig = DEFAULT_ORIG;
    prog->reached_end = false;

    debug_print("initConstructorProgama: Constructor de Prgrama inicializado exitosamente\n");

    return prog;
}

void addOperacionPrograma(ConsPrograma prog, Operacion op, char label[]) {
    if (prog->reached_end) {
        debug_print("addOperacionPrograma: No se agrego la operacion, fin del programa alcanzado\n");
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->text);
        insertSymTable(prog->symtable, label, initFullAddr(TEXT, pos));
        debug_print("addOperacionPrograma: Encontro label %s sobre una operacion\n", label);
    }
    pushCola(prog->text, op);
    debug_print("addOperacionPrograma: Operacion agregada exitosamente\n");
}

void addDataPrograma(ConsPrograma prog, bin literal, char label[]) {
    if (prog->reached_end) {
        debug_print("addDataPrograma: No se agrego la operacion, fin del programa alcanzado\n");
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->data);
        insertSymTable(prog->symtable, label, initFullAddr(DATA, pos));
        debug_print("addDataPrograma: Encontro label %s sobre un literal\n", label);
    }

    bin* ptr = malloc(sizeof(bin));
    *ptr = literal;
    pushCola(prog->data, ptr);
    debug_print("addDataPrograma: Literal agregado exitosamente\n");
}

void setOrig(ConsPrograma prog, addr orig) {
    prog->orig = orig;
    debug_print("setOrig: origen seteado a %u\n", orig);
}

void freeConsPrograma(ConsPrograma prog) {
    freeSymTable(prog->symtable);
    freeCola(prog->text);
    freeCola(prog->data);
    free(prog);
    debug_print("freeConsPrograma: programa liberado exitosamente\n");
}

void buildPrograma(ConsPrograma prog, char path[]) {
    ConsSalida builder = initConstructorSalida(path, prog->orig);
    debug_print("buildPrograma: Constructor de salida inicializado correctamente\n");

    setStartSeccion(TEXT, prog->orig);
    debug_print("buildPrograma: Inicio de seccion .text seteada a %u\n", prog->orig);
    setStartSeccion(DATA, (getStartSeccion(TEXT) + lengthCola(prog->text)));
    debug_print("buildPrograma: Inicio de seccion .data seteada a %u\n", (getStartSeccion(TEXT) + lengthCola(prog->text)));

    agregarConsSalida(builder, (bin)prog->orig);

    
    addr pos = prog->orig;
    while (lengthCola(prog->text) > 0) {
        Operacion op = popCola(prog->text);
        bin traduccion = traducirOperacion(op, prog->symtable, pos);
        agregarConsSalida(builder, traduccion);
        freeOperacion(op);
        pos++;
    }
    debug_print("buildPrograma: Seccion .text construida exitosamente\n");
    while (lengthCola(prog->data) > 0) {
        bin* literal = popCola(prog->data);
        agregarConsSalida(builder, *literal);
        free(literal);
        pos++;
    }
    debug_print("buildPrograma: Seccion .data construida exitosamente\n");
    construirSalida(builder);
    debug_print("buildPrograma: Archivo de salida creado exitosamente\n");
    freeConsPrograma(prog);
}