#include "constructor_programa.h"
#include "constructor_salida.h"
#include "cola.h"
#include "symtable.h"
#include "full_address.h"
#include "operacion.h"
#include "seccion.h"


#define DEFAULT_ORIG 3000

ConsPrograma initConstructorPrograma() {
    ConsPrograma prog = malloc(sizeof(struct __constructor_programa));

    prog->data = initCola();
    prog->text = initCola();
    prog->symtable = initSymTable(0);
    prog->orig = DEFAULT_ORIG;
    prog->reached_end = false;

    return prog;
}

void addOperacionPrograma(ConsPrograma prog, Operacion op, char label[]) {
    if (prog->reached_end) {
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->text);
        insertSymTable(prog->symtable, label, initFullAddr(TEXT, pos));
    }
    pushCola(prog->text, op);
}

void addDataPrograma(ConsPrograma prog, bin literal, char label[]) {
    if (prog->reached_end) {
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->data);
        insertSymTable(prog->symtable, label, initFullAddr(DATA, pos));
    }

    bin* ptr = malloc(sizeof(bin));
    *ptr = literal;
    pushCola(prog->data, ptr);
}

void setOrig(ConsPrograma prog, addr orig) {
    prog->orig = orig;
}

void freeConsPrograma(ConsPrograma prog) {
    freeSymTable(prog->symtable);
    freeCola(prog->text);
    freeCola(prog->data);
    free(prog);
}

void buildPrograma(ConsPrograma prog, char path[]) {
    ConsSalida builder = initConstructorSalida(path, prog->orig);

    setStartSeccion(TEXT, prog->orig);
    setStartSeccion(DATA, (getStartSeccion(TEXT) + lengthCola(prog->text)));

    agregarConsSalida(builder, (bin)prog->orig);

    addr pos = prog->orig;
    while (lengthCola(prog->text) > 0) {
        Operacion op = popCola(prog->text);
        bin traduccion = traducirOperacion(op, prog->symtable, pos);
        agregarConsSalida(builder, traduccion);
        // freeOp
        pos++;
    }

    while (lengthCola(prog->data) > 0) {
        bin* literal = popCola(prog->data);
        agregarConsSalida(builder, *literal);
        free(literal);
        pos++;
    }

    construirSalida(builder);
    freeConsPrograma(prog);
}