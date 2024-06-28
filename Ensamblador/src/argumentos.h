#include "utils.h"

Argumento initArgumento(Token tkn);

Argumento directInitArgumento(int n_reg, int n, char string[], char etiqueta[], ArgsTipo tipo);

void freeArgumento(Argumento arg);

int tipoArgumento(Argumento arg);

void* valorArgumento(Argumento arg);

void printArgumento(Argumento arg);

void toStringArgumento(Argumento arg, char* rtn);

bool argCoincideTipo(ArgsTipo req_tipo, Argumento arg);

