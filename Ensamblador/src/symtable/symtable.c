#include "symtable.h"
#include <string.h>

#define DEFAULT_SEED 61

unsigned int hash(const char* in, size_t len)
{
    unsigned int h = DEFAULT_SEED;
    unsigned int c;
    size_t i;

    for (i=0; i<len; i++) {
        c = in[i];
        h ^= c;
        h *= 16777619; /* FNV prime */
    }

    return h;
}

SymTable initSymTable(int largo){
    SymTable tabla = malloc(sizeof(struct __symtable));
    tabla->array = malloc(sizeof(SymList) * largo);
    for(int i = 0; i < largo; i++)
        tabla->array[i] = initSymList();
    tabla->largo = largo;
    return tabla;
} 

SymTable insertSymTable(SymTable tabla, char* llave, addr dato){
    int idx = hash(llave, strlen(llave)) % tabla->largo;
    tabla->array[idx] = insertSymList(tabla->array[idx], llave, dato);
    return tabla;
}

SymTable removeSymTable(SymTable tabla, char* llave){
    int idx = hash(llave, strlen(llave)) % tabla->largo;
    tabla->array[idx] = removeSymList(tabla->array[idx], llave);
    return tabla;
}

addr searchSymTable(SymTable tabla, char* llave){
    int idx = hash(llave, strlen(llave)) % tabla->largo;
    return searchSymList(tabla->array[idx], llave);
}

void freeSymTable(SymTable tabla){
    for(int i = 0; i < tabla->largo; i++){
        freeSymList(tabla->array[i]);
    }
    free(tabla->array);
    free(tabla);
};