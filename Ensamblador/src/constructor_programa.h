#include "utils.h"


ConsPrograma initConstructorPrograma();

void addInstruccionPrograma(ConsPrograma prog, Operacion op, char label[]);

void addDataPrograma(ConsPrograma prog, bin literal, char label[]);

void setOrig(ConsPrograma prog, addr orig);

void buildPrograma(ConsPrograma prog, char path[]);