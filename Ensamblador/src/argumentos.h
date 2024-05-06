#include "utils.h"

Argumento initArgumento(int tipo, void* valor);

Argumento* parsearArgumentos(char raw[], int* argc);

void freeArgumento(Argumento arg);

int tipoArgumento(Argumento arg);

void* valorArgumento(Argumento arg);

void printArgumento(Argumento arg);

void toStringArgumento(Argumento arg, char* rtn);

