#ifndef LCCCC_COLA
#define LCCCC_COLA

#include "utils.h"


Cola initCola();

void pushCola(Cola cola, void* valor);

void* popCola(Cola cola);

int lengthCola(Cola cola);

bool emptyCola(Cola cola);

void freeCola(Cola cola);

#endif