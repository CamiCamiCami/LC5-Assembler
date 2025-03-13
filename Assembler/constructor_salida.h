#ifndef LCCCC_CONSTRUCTOR_SALIDA
#define LCCCC_CONSTRUCTOR_SALIDA

#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

ConsSalida initConstructorSalida(char path[], addr orig);

void agregarConsSalida(ConsSalida cons, bin b);

void construirSalida(ConsSalida cons);

#endif