#include "utils.h"


ConsPrograma initConstructorPrograma();

void addOperacionPrograma(ConsPrograma prog, Operacion op, char label[]);

void addLiteralPrograma(ConsPrograma prog, bin literal, char label[]);

void addPointerProgram(ConsPrograma prog, char puntero[], char label[]);

void setOrig(ConsPrograma prog, addr orig);

void buildPrograma(ConsPrograma prog, char path[]);