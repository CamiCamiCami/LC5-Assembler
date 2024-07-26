#ifndef LCCCC_CONSTRUCTOR_PROGRAMA
#define LCCCC_CONSTRUCTOR_PROGRAMA

#include "utils.h"


ConsPrograma initConstructorPrograma();

void addProgama(ConsPrograma prog, void* comando, TipoComando tipo, char label[]);

void addLiteralPrograma(ConsPrograma prog, bin literal, char label[]);

void addPointerPrograma(ConsPrograma prog, char puntero[], char label[]);

void setOrig(ConsPrograma prog, addr orig);

void programaLlegoAlFin(ConsPrograma prog);

void buildPrograma(ConsPrograma prog, char path[]);

#endif