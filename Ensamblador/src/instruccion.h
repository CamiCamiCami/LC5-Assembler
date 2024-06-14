#include "utils.h"


Instruccion deStringInstruccion(char token[], bool* error);

int conseguirArgsTipoInstruccion(Instruccion ins, int args[5]);

bin conseguirBaseInstruccion(Instruccion ins);

Traductor conseguirTraductorInstruccion(Instruccion ins);

void comoStringInstruccion(Instruccion ins, char str[10]);