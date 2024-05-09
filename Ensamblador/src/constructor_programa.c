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

    return prog;
}

void addInstruccionPrograma(ConsPrograma prog, Operacion op, char label[]) {
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->text);
        insertSymTable(prog->symtable, label, initFullAddr(TEXT, pos));
    }
    pushCola(prog->text, op);
}

void addDataPrograma(ConsPrograma prog, bin literal, char label[]){
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

    addr pos = prog->orig;
    while (lengthCola(prog->text) > 0) {
        Operacion op = popCola(prog->text);
        bin traduccion = traducirOperacion(op, prog->symtable, pos);
        agregarConsSalida(builder, traduccion);
        pos++;
    }

    while (lengthCola(prog->data) > 0) {
        bin traduccion = popCola(prog->data);
        agregarConsSalida(builder, traduccion);
        pos++;
    }

    construirSalida(builder);
    freeConsPrograma(prog);
}