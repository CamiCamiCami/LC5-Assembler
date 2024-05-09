#include "full_address.h"
#include "seccion.h"

FullAddr initFullAddr(Seccion s, unsigned int offset){
    FullAddr addr = malloc(sizeof(struct __full_address));
    addr->offset = offset;
    addr->seccion = s;
    return addr;
}

unsigned int getOffset(FullAddr addr){
    return addr->offset;
}

void setOffset(FullAddr addr, unsigned int offset){
    addr->offset = offset;
}

Seccion getSeccion(FullAddr addr){
    return addr->seccion;
}

void setSeccion(FullAddr addr, Seccion s){
    addr->seccion = s;
}

void freeFullAddr(FullAddr addr){
    free(addr);
}

addr solveAddr(FullAddr addr) {
    return (getStartSeccion(addr->seccion) + addr->offset);
}