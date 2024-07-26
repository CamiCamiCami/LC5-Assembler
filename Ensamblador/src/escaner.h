#ifndef LCCCC_ESCANER
#define LCCCC_ESCANER

#include "utils.h"

Escaner initEscaner(char path[]);

char* nextEscaner(Escaner escaner);

void resetEscaner(Escaner escaner);

bool tieneProximoEscaner(Escaner escaner);

void closeEscaner(Escaner escaner);

#endif