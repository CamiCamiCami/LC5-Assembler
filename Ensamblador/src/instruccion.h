#include "utils.h"


Instruccion deString(char token[]);

int conseguirArgsTipo(Instruccion ins, int args[5]);

bin conseguirBase(Instruccion ins);

Traductor conseguirTraductor(Instruccion ins);

void comoStringInstruccion(Instruccion ins, char str[5]);