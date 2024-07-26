#ifndef LCCCC_FULLADDRESS
#define LCCCC_FULLADDRESS

#include "utils.h"

FullAddr initFullAddr(Seccion s, unsigned int offset);

unsigned int getOffset(FullAddr addr);

void setOffset(FullAddr addr, unsigned int offset);

Seccion getSeccion(FullAddr addr);

void setSeccion(FullAddr addr, Seccion s);

void freeFullAddr(FullAddr addr);

// Solo puede resolver la direccion real cuando se sepa donde empieza cada seccion
addr solveAddr(FullAddr addr);

#endif