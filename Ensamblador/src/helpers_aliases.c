#include "helpers.h"
#include "argumentos.h"
#include "operacion.h"
#include <math.h>

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

void checkArgsAlias(AliasOp aop){
    Alias alias = aop->alias;
    Argumento* args = aop->args;
    int argc = aop->argc;

    ArgsTipo* esperado = alias->arg_tipo;
    int c_esperado = alias->argc;

    debug_print("Chequeando operacion %s\n", alias->name);
    
    for (int i = 0; i < argc; i++)
        printArgumento(args[i]);

    for (int i = 0; i < c_esperado; i++){
        char repr[50];
        argTipoComoStr(esperado[i], repr);
        debug_print("esperado[%i] = %s\n", i, repr);
    }
    for (int i = 0; i < argc; i++){
        debug_print("%i | ", args[i]->tipo);
        char repr[50];
        argTipoComoStr(args[i]->tipo, repr);
        debug_print("args[%i]->tipo = %s\n", i, repr);
    }

    if(argc != c_esperado){
        // Manejo de Error
        fprintf(stderr, "Argumentos invalidos para opracion %s. Esperaba %i argumento/s pero recibio %i\n", alias->name, c_esperado, argc);
        exit(1);
    }

    for (int i = 0; i < c_esperado; i++){
        if (!(esperado[i] & args[i]->tipo)){
            // Manejo de Error
            char str_esperado[50], str_recibido[50];
            argTipoComoStr(esperado[i], str_esperado);
            argTipoComoStr(args[i]->tipo, str_recibido);
            fprintf(stderr, "Argumentos invalidos para operacion %s. en la posicion %i, esperaba tipo %s pero recibio tipo %s\n", alias->name, i+1, str_esperado, str_recibido);
            exit(1);
        }
    }
}

double ceil(double n) {
    return ((double)((int) n)) == n ? (int) n : ((int) n) + 1;
}

int sign(int n) {
    return n < 0? -1 : 1;
}

Operacion* expandirADD(AliasOp aop, int* c_op) {
    checkArgsAlias(aop);
    const int maxADDI = 0b0000000000011111;
    Registro reg = aop->args[0]->valor;
    Operacion* expansion;
    int caso = 0;
    if(aop->args[1]->tipo & TIPO_REGISTRO)  caso += 1;
    if(aop->args[2]->tipo & TIPO_REGISTRO)  caso += 1;

    switch (caso) {
    case 0:;     // Dos constantes
        int s1 = *((int*) aop->args[1]->valor);
        int s2 = *((int*) aop->args[2]->valor);
        short res = s1 + s2;
        int upper = ((res & (short)0b1111111100000000) >> 8);
        int lower = ((res & (short)0b0000000011111111));
        expansion = malloc(sizeof(Operacion) * 2);
        *c_op = 2;
        Argumento args_lui[] = {directInitArgumento(reg, TIPO_REGISTRO),
                                directInitArgumento(&upper, TIPO_NUMERO)};
        expansion[0] = initOperacion(LUI, args_lui, 2);
        Argumento args_lori[] = {directInitArgumento(reg, TIPO_REGISTRO),
                                 directInitArgumento(&lower, TIPO_NUMERO)};
        expansion[1] = initOperacion(LUI, args_lori, 2);
        return expansion;
    case 1:;
        Registro sum1;
        int sum2;
        
        if(aop->args[1]->tipo & TIPO_REGISTRO) {
            sum1 = aop->args[1]->valor;
            sum2 = *((int*)aop->args[2]->valor);
        } else {
            sum1 = aop->args[2]->valor;
            sum2 = *((int*)aop->args[1]->valor);
        }

        double size = (double)sum2 / (double)maxADDI;
        expansion = malloc(sizeof(Operacion) * ceil(size));
        int i = 0;
        for (int i = 0; abs(sum2) > maxADDI; sum2 -= sign(sum2)*maxADDI, i++) {
            Argumento args[] = {directInitArgumento(reg, TIPO_REGISTRO),
                                 directInitArgumento(sum1, TIPO_REGISTRO),
                                 directInitArgumento((int*)&maxADDI, TIPO_NUMERO)};
            expansion[i] = initOperacion(IADDI, args, 3);
        }
        Argumento arg_addi[] = {directInitArgumento(reg, TIPO_REGISTRO),
                            directInitArgumento(sum1, TIPO_REGISTRO),
                            directInitArgumento(&sum2, TIPO_NUMERO)};
        expansion[i] = initOperacion(IADDI, arg_addi, 3);
        *c_op = i+1;
        return expansion;
    case 2:   // Dos Registros
        expansion = malloc(sizeof(Operacion));
        *c_op = 1;
        Argumento arg_add[] = {directInitArgumento(reg, TIPO_REGISTRO),
                            directInitArgumento(((Registro)aop->args[1]->valor), TIPO_REGISTRO),
                            directInitArgumento(((Registro)aop->args[2]->valor), TIPO_REGISTRO)};
        expansion[0] = initOperacion(IADD, arg_add, 3);
        return expansion;
    default:
        fprintf(stderr, "Error de Programacion\n");
        exit(1);
    }
}

Operacion* expandirMOV(AliasOp aop, int *c_op) {
    checkArgsAlias(aop);
    Argumento arg1 = aop->args[0];
    Argumento arg2 = aop->args[1];
    Operacion* expansion = NULL;

    if (arg1->tipo & TIPO_REGISTRO) {
        Registro dest = arg1->valor;

        if(arg2->tipo & TIPO_REGISTRO) {
            Registro remitente = arg2->valor;
            expansion = malloc(sizeof(Operacion) * 2);
            *c_op = 2;
            Argumento arg_xor[] = {directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(dest, TIPO_REGISTRO)};
            expansion[0] = initOperacion(XOR, arg_xor, 3);
            Argumento arg_or[] = {directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(remitente, TIPO_REGISTRO)};
            expansion[1] = initOperacion(OR, arg_or, 3);
        } else if(arg2->tipo & TIPO_NUMERO) {
            bin inm_lui = *((int*)arg2->valor) >> 8;
            bin inm_lori = *((int*)arg2->valor) & 0b0000000011111111;
            expansion = malloc(sizeof(Operacion) * 2);
            *c_op = 2;
            Argumento arg_lui[] = {directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(&inm_lui, TIPO_NUMERO)};
            expansion[0] = initOperacion(LUI, arg_lui, 2);
            Argumento arg_lori[] = {directInitArgumento(dest, TIPO_REGISTRO),
                                   directInitArgumento(&inm_lori, TIPO_NUMERO)};
            expansion[1] = initOperacion(LORI, arg_lori, 2);
        } else if(arg2->tipo & TIPO_ETIQUETA) {
            char *label = ((char*)arg2->valor);
            expansion = malloc(sizeof(Operacion) * 1);
            *c_op = 1;
            Argumento arg_ld[] = {directInitArgumento(dest, TIPO_REGISTRO),
                                  directInitArgumento(label, TIPO_ETIQUETA)};
            expansion[0] = initOperacion(LD, arg_ld, 2);
        } else {
            fprintf(stderr, "expandirMOV: Error de Programacion");
            exit(1);
        }
    } else if (arg1->tipo & TIPO_ETIQUETA) {
        char *label = arg1->valor;

        if(arg2->tipo & TIPO_REGISTRO) {
            Registro remitente = ((Registro)arg2->valor);
            expansion = malloc(sizeof(Operacion) * 1);
            *c_op = 1;
            Argumento arg_st[] = {directInitArgumento(remitente, TIPO_REGISTRO),
                                  directInitArgumento(label, TIPO_ETIQUETA)};
            expansion[0] = initOperacion(ST, arg_st, 2);
        } else if(arg2->tipo & TIPO_NUMERO) {
            fprintf(stderr, "expandirMOV: Inmediato a memoria no está implementado");
            exit(1);
        } else {
            fprintf(stderr, "expandirMOV: Error de Programacion");
            exit(1);
        }
    }

    return expansion;
}

