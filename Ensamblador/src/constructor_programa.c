#include "constructor_programa.h"
#include "cola.h"
#include "symtable.h"



ConsPrograma initConstructorPrograma() {
    ConsPrograma prog = malloc(sizeof(struct __constructor_programa));

    prog->data = initCola();
    prog->text = initCola();
    prog->symtable = initSymTable(0);

    return prog;
}

void addInstruccionPrograma(ConsPrograma prog, Instruccion ins, char label[]) {
    if (label != NULL) {
        insertSymTable(prog->symtable, label, lengthCola(prog->text));
    }
    pushCola(prog->text, ins);
}

void addLiteralPrograma(ConsPrograma prog, bin literal, char label[]){
    
}

void buildPrograma(ConsPrograma prog, char path[]);