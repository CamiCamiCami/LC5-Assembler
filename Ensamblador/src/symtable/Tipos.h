#include <stdbool.h>

typedef unsigned short addr; 

// Funciones
typedef int (*FuncionHash) (void* llave);
typedef bool (*Comparacion) (void* e1, void* e2);
typedef void (*Liberacion) (void* elem);
typedef void* (*Copia) (void* orig);
typedef void (*Vertir) (char dir[], void* dato);
typedef void* (*Leer) (char dir[]);

// Estructuras
typedef struct __symtable* SymTable;
typedef struct __symbol_list* SymList;
typedef struct __symbol* Symbol;