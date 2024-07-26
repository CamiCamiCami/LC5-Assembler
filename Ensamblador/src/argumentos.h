#ifndef LCCCC_ARGUMENTOS
#define LCCCC_ARGUMENTOS

#include "utils.h"

Argumento initArgumento(Token tkn);

Argumento directInitArgumento(void* arg, ArgsTipo tipo);

void freeArgumento(Argumento arg);

int tipoArgumento(Argumento arg);

void* valorArgumento(Argumento arg);

void printArgumento(Argumento arg);

void toStringArgumento(Argumento arg, char* rtn);

bool argCoincideTipo(ArgsTipo req_tipo, Argumento arg);

#endif