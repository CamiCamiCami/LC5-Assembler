#include "constructor_programa.h"
#include "constructor_salida.h"
#include "cola.h"
#include "symtable.h"
#include "full_address.h"
#include "operacion.h"
#include "psoperacion.h"
#include "alias.h"
#include "seccion.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#define DEFAULT_ORIG 3000


/* Tipo Interno Entrada de Dato */

struct __data_entrada {
    bool es_etiqueta;
    bin literal;
    char* etiqueta;
};

typedef struct __data_entrada* EntradaDato;

EntradaDato initEntradaDato_Literal(bin literal) {
    EntradaDato dato = malloc(sizeof(struct __data_entrada));
    dato->es_etiqueta = false;
    dato->literal = literal;
    dato->etiqueta = NULL;
    return dato;
}

EntradaDato initEntradaDato_Etiqueta(char etiqueta[]) {
    EntradaDato dato = malloc(sizeof(struct __data_entrada));
    dato->es_etiqueta = true;
    dato->literal = 0;
    dato->etiqueta = malloc(sizeof(char) * (strlen(etiqueta) + 1));
    strcpy(dato->etiqueta, etiqueta);
    return dato;
}

char* getDato_Etiqueta(EntradaDato dato) {
    if (!dato->es_etiqueta) {
        // Manejo de Error
        fprintf(stderr, "El dato es un literal, no tiene etiqueta\n");
        exit(1);
    }
    return dato->etiqueta;
}

bin getDato_Literal(EntradaDato dato) {
    if (!dato->es_etiqueta) {
        // Manejo de Error
        fprintf(stderr, "El dato es una etiqueta, no tiene literal\n");
        exit(1);
    }
    return dato->literal;
}

void freeDato(EntradaDato dato) {
    if (dato->es_etiqueta){
        free(dato->etiqueta);
    }
    free(dato);
}

bin traducirDato(EntradaDato dato, SymTable tabla) {
    if (dato->es_etiqueta) {
        FullAddr full_addr = searchSymTable(tabla, dato->etiqueta);
        addr address = solveAddr(full_addr);
        return (bin) address;
    } else {
        return dato->literal;
    }
}


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

void addProgramaOperacion(ConsPrograma prog, Operacion op, char label[]) {
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

void addProgramaPseudoOperacion(ConsPrograma prog, PseudoOp pso, char label[]) {
    efectuarPseudoOp(prog, pso, label);
}

void addProgramaAlias(ConsPrograma prog, AliasOp aliasop, char label[]) {
    int cant_op;
    Operacion* traduccion = expandirAliasOp(aliasop, &cant_op);
    addProgramaOperacion(prog, traduccion[0], label);
    for (int i = 1; i < cant_op; i++)
        addProgramaOperacion(prog, traduccion[i], NULL);
    free(traduccion);
}

void addProgama(ConsPrograma prog, void* comando, TipoComando tipo, char label[]) {
    switch (tipo) {
    case OPERACION:
        addProgramaOperacion(prog, comando, label);
        break;
    case PSEUDOOP:
        addProgramaPseudoOperacion(prog, comando, label);
        break;
    case ALIAS:
        addProgramaAlias(prog, comando, label);
        break;
    default:
        fprintf(stderr, "Tipo de comando desconocido %i", tipo);
        break;
    }
}

void addLiteralPrograma(ConsPrograma prog, bin literal, char label[]) {
    if (prog->reached_end) {
        debug_print("addLiteralPrograma: No se agrego la operacion, fin del programa alcanzado\n");
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->data);
        insertSymTable(prog->symtable, label, initFullAddr(DATA, pos));
        debug_print("addLiteralPrograma: Encontro label %s sobre un literal\n", label);
    }

    EntradaDato dato = initEntradaDato_Literal(literal);
    pushCola(prog->data, dato);
    debug_print("addLiteralPrograma: Literal agregado exitosamente\n");
}

void addPointerPrograma(ConsPrograma prog, char puntero[], char label[]) {
    if (prog->reached_end) {
        debug_print("addPointerPrograma: No se agrego la operacion, fin del programa alcanzado\n");
        return;
    }
    if (label != NULL) {
        unsigned int pos = lengthCola(prog->data);
        insertSymTable(prog->symtable, label, initFullAddr(DATA, pos));
        debug_print("addPointerPrograma: Encontro label %s sobre un literal\n", label);
    }

    EntradaDato dato = initEntradaDato_Etiqueta(puntero);
    pushCola(prog->data, dato);
    debug_print("addPointerPrograma: Literal agregado exitosamente\n");
}

void setOrig(ConsPrograma prog, addr orig) {
    prog->orig = orig;
    debug_print("setOrig: origen seteado a %u\n", orig);
}

void programaLlegoAlFin(ConsPrograma prog) {
    prog->reached_end = true;
    debug_print("programaLlegoAlFin: Fin encontrado\n");
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
        EntradaDato dato = popCola(prog->data);
        bin literal = traducirDato(dato, prog->symtable);
        agregarConsSalida(builder, literal);
        freeDato(dato);
        pos++;
    }
    debug_print("buildPrograma: Seccion .data construida exitosamente\n");
    construirSalida(builder);
    debug_print("buildPrograma: Archivo de salida creado exitosamente\n");
    freeConsPrograma(prog);
}