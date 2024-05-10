#include "utils.h"


Instruccion deStringInstruccion(char token[]);

int conseguirArgsTipoInstruccion(Instruccion ins, int args[5]);

bin conseguirBaseInstruccion(Instruccion ins);

Traductor conseguirTraductorInstruccion(Instruccion ins);

void comoStringInstruccion(Instruccion ins, char str[5]);