#include "symtable.h"
#include "full_address.h"

/* Definicion de tipos internos */

struct __symbol {
    char* label;
    FullAddr address;
};

struct __symbol_list {
    struct __symbol* symbol;
    struct __symbol_list* sig;
};

typedef struct __symbol_list* SymList;
typedef struct __symbol* Symbol;

/* Funciones de Symbol */

Symbol initSymbol(char* label, FullAddr address){
    Symbol sym = malloc(sizeof(struct __symbol));
    char* label_cpy = malloc(sizeof(char) * (strlen(label) + 1));
    strcpy(label_cpy, label);
    sym->label = label_cpy;
    sym->address = address;
    return sym;
}

char* getLabel(Symbol sym){
    return sym->label;
}

Symbol setLabel(Symbol sym, char* label){
    free(sym->label);
    char* label_cpy = malloc(sizeof(char) * strlen(label));
    strcpy(label_cpy, label);
    sym->label = label_cpy;
    return sym;
}

FullAddr getAddress(Symbol sym){
    return sym->address;
}

Symbol setAddress(Symbol sym, FullAddr address){
    freeFullAddr(sym->address);
    sym->address = address;
    return sym;
}

void freeSymbol(Symbol sym){
    free(sym->label);
    freeFullAddr(sym->address);
    free(sym);
}


/* Funciones de SymList */

#define LLAVE(t) getLabel(t->symbol)
#define DATO(t) getAddress(t->symbol)


SymList initSymList(){
    return NULL;
}

bool emptySymList(SymList map){
    return map == NULL;
}

SymList insertSymList(SymList map, char* llave, FullAddr dato){
    if (emptySymList(map)){
        Symbol sym = initSymbol(llave, dato);
        SymList nodo = malloc(sizeof(struct __symbol_list));
        nodo->sig = initSymList();
        nodo->symbol = sym;
        return nodo;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        return map;
    } else {
        map->sig = insertSymList(map->sig, llave, dato);
        return map;
    }
}

SymList removeSymList(SymList map, char* llave){
    if (emptySymList(map)){
        return map;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        freeSymbol(map->symbol);
        SymList nodo = map->sig;
        free(map);
        return nodo;
    } else {
        map->sig = removeSymList(map->sig, llave);
        return map;
    }
}

FullAddr searchSymList(SymList map, char* llave){
    if (emptySymList(map)){
        return NULL;
    } else if (strcmp(llave, LLAVE(map)) == 0) {
        return DATO(map);
    } else {
        return searchSymList(map->sig, llave);
    }
}

void freeSymList(SymList map){
    if (emptySymList(map)){
        return;
    }
    freeSymList(map->sig);
    freeSymbol(map->symbol);
    free(map);
}


/* Funciones de libreria */

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

#define LARGO_DEFAULT 10

SymTable initSymTable(int largo){
    if (largo < 1) {
        largo = LARGO_DEFAULT;
    }
    SymTable tabla = malloc(sizeof(struct __symbol_table));
    tabla->array = malloc(sizeof(SymList) * largo);
    for(int i = 0; i < largo; i++)
        tabla->array[i] = initSymList();
    tabla->largo = largo;
    return tabla;
} 

void insertSymTable(SymTable tabla, char* label, FullAddr addr){
    int idx = hash(label, strlen(label)) % tabla->largo;
    tabla->array[idx] = insertSymList(tabla->array[idx], label, addr);
}

void removeSymTable(SymTable tabla, char* llave){
    int idx = hash(llave, strlen(llave)) % tabla->largo;
    tabla->array[idx] = removeSymList(tabla->array[idx], llave);
}

FullAddr searchSymTable(SymTable tabla, char* llave){
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
