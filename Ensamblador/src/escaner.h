#include <stdlib.h>
#include <stdio.h>

typedef FILE* Escaner;

Escaner initEscaner(char path[]);

char* nextEscaner(Escaner escaner);

void resetEscaner(Escaner escaner);