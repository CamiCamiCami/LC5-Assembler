#include "helpers.h"


void checkArgs(PseudoOp pso){
    Argumento arg = pso->arg;
    PseudoIns psi = pso->psi;
    if (arg == NULL) {
        if (psi->necesita_arg) {
            char str[50];
            argTipoComoStr(psi->arg_tipo, str);
            fprintf(stderr, "Pseudo operacion %s esperaba un argumento de tipo %s pero no recibio ninguno\n", psi->name, str);
            exit(1);
        } else {
            return;
        }
    }

    if(!(psi->arg_tipo & arg->tipo)) {
        char str_esperado[50], str_recibido[50];
        argTipoComoStr(psi->arg_tipo, str_esperado);
        argTipoComoStr(arg->tipo, str_recibido);
        fprintf(stderr, "Argumentos invalidos para pseudo operacion %s. Esperaba tipo %s pero recibio tipo %s\n", psi->name, str_esperado, str_recibido);
        exit(1);
    }
}

void efectuarORIG(ConsPrograma prog, PseudoOp pso, char label[]) {
    checkArgs(pso);
    if (label != NULL) {
            // Manejo de error
            fprintf(stderr, "No se admiten etiqutas que apunten a .orig\n");
            exit(1);
    }
    int addr_int = *((int*) pso->arg->valor);
    if (addr_int < 0 || MAX_ADDR < addr_int){
            // Manejo de error
            fprintf(stderr, "Origen del programa no puede ser la direccion invalida %i. Fuera de rango 0-%i\n", addr_int, MAX_ADDR);
            exit(1);
        }
    setOrig(prog, (addr) addr_int);
}

void efectuarFILL(ConsPrograma prog, PseudoOp pso, char label[]) {
    checkArgs(pso);
    if (pso->arg->tipo & TIPO_ETIQUETA){
        addPointerPrograma(prog, pso->arg->valor, label);
    } else {
        addLiteralPrograma(prog, (bin)(*((unsigned int*) pso->arg->valor)), label);
    }
}

void efectuarBLKW(ConsPrograma prog, PseudoOp pso, char label[]) {
    checkArgs(pso);
    unsigned int c_blocks = *((unsigned int*)pso->arg->valor);
    if (c_blocks < 1){
        // Manejo de error
        fprintf(stderr, ".blkw no puede reservar ua cantidad de %i\n", c_blocks);
        exit(1);
    }

    addLiteralPrograma(prog, (bin) 0, label);
    c_blocks--;
    for (; c_blocks > 0; c_blocks--){
        addLiteralPrograma(prog, (bin) 0, NULL);
    }
}

void efectuarSTRINGZ(ConsPrograma prog, PseudoOp pso, char label[]) {
    checkArgs(pso);
    char* str = pso->arg->valor;

    addLiteralPrograma(prog, (bin) str[0], label);
    for (int i = 1; str[i] != '\0'; i++) {
        addLiteralPrograma(prog, (bin) str[i], NULL);
    }
    addLiteralPrograma(prog, (bin) '\0', NULL);
}

void efectuarEND(ConsPrograma prog, PseudoOp pso, char label[]) {
    checkArgs(pso);

    if (label != NULL) {
            // Manejo de error
            fprintf(stderr, "No se admiten etiqutas que apunten a .end\n");
            exit(1);
    }

    programaLlegoAlFin(prog);
}