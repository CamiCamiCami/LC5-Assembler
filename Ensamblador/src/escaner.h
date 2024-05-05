#include <stdio.h>
#include <stdbool.h>

typedef FILE* Escaner;

Escaner initEscaner(char path[]);

char* nextEscaner(Escaner escaner);

void resetEscaner(Escaner escaner);

bool tieneProximoEscaner(Escaner escaner);

void closeEscaner(Escaner escaner);
