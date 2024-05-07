#include "../utils.h"


SymList initSymList();

bool emptySymList(SymList lista);

SymList insertSymList(SymList lista, char* llave, int dato);

SymList removeSymList(SymList lista, char* llave);

int searchSymList(SymList lista, char* llave);

void freeSymList(SymList lista);
