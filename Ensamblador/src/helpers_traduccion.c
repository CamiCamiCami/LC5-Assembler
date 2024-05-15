#include "helpers_traduccion.h"
#include "operacion.h"
#include "instruccion.h"
#include "symtable.h"
#include "full_address.h"
#include "constructor_programa.h"

#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

void checkArgsOperacion(Operacion op){
    Instruccion ins = op->ins;
    Argumento* args = op->args;
    int c_arg = op->argc;

    int esperado[5];
    int c_esperado = conseguirArgsTipoInstruccion(ins, esperado);

    char repr_op[10];
    comoStringInstruccion(op->ins, repr_op);
    debug_print("Chequeando operacion %s\n", repr_op);

    for (int i = 0; i < c_esperado; i++){
        char repr[50];
        argTipoComoStr(esperado[i], repr);
        debug_print("esperado[%i] = %s\n", i, repr);
    }
    for (int i = 0; i < c_arg; i++){
        char repr[50];
        argTipoComoStr(args[i]->tipo, repr);
        debug_print("args[%i]->tipo = %s\n", i, repr);
    }

    if(c_arg != c_esperado){
        // Manejo de Error
        char str[5];
        comoStringInstruccion(op->ins, str);
        fprintf(stderr, "Argumentos invalidos para opracion %s. Esperaba %i argumento/s pero recibio %i\n", str, c_esperado, c_arg);
        exit(1);
    }

    for (int i = 0; i < c_esperado; i++){
        if (!(esperado[i] & args[i]->tipo)){
            // Manejo de Error
            char str_ins[5], str_esperado[10], str_recibido[10];
            comoStringInstruccion(op->ins, str_ins);
            argTipoComoStr(esperado[i], str_esperado);
            argTipoComoStr(args[i]->tipo, str_recibido);
            fprintf(stderr, "Argumentos invalidos para operacion %s. en la posicion %i, esperaba tipo %s pero recibio tipo %s\n", str_ins, i+1, str_esperado, str_recibido);
            exit(1);
        }
    }
}


bin shiftReg(Registro r, unsigned int pos){
    if (pos < 1 || 15 < pos){
        // Manejo de Error
        fprintf(stderr, "Destino de shifteado ilegal. Se quiso shiftear un registro hasta la posicion %i\n", pos);
        exit(1);
    }
    unsigned short n = (unsigned short)r->NUMERO;
    return n << (pos-2);
}


bin _formatNum(short n, unsigned int size){
    if(size > 16){
        // Manejo de Error
        fprintf(stderr, "formato de numero demasiado largo: %i bits\n", size);
        exit(1);
    }
    if (size == 0){
        // Manejo de Error
        fprintf(stderr, "formato de numero de largo 0 no tiene sentido\n");
        exit(1);
    }
    
    /*
    short max_val = (1 << (size-1U)) - 1; // 2^(size-1) - 1
    short min_val = -(1 << (size-1U));

    if (n < min_val || max_val < n){
        // Manejo de Error
        fprintf(stderr, "Valor fuera de rango. esperaba (%i)-(%i) pero recibio %i\n", min_val, max_val, n);
        exit(1);
    }
    */

    bin mask = 0b1111111111111111 >> (16-size);
    bin res = mask & n;
    char str[17];
    comoStr(res, str);
    debug_print("_formatNum: %s\n", str);
    return res;
}

bin formatNum(short* n, unsigned int size){
	return _formatNum(*n, size);
}


bin formatSHNum(short* SH, short* n){
    if (*SH > 4){
        // Manejo de Error
        fprintf(stderr, "Valor de shifteo fuera de rango. esperaba 0-4 pero recibio %i\n", *SH);
        exit(1);
    }
    bin b = formatNum(n, 4);
    b = (bin)(*SH << 4) + b;
    char str[17];
    comoStr(b, str);
    debug_print("formatSHNum: %s\n", str);
    return b;
}

bin solveRelReference(SymTable table, addr pos, char label[], unsigned int size){
    FullAddr label_full_addr = searchSymTable(table, label);
    if (label_full_addr == NULL){
        // Manejo de Error
        fprintf(stderr, "No pudo resolver refenecia a %s\n", label);
        exit(1);
    }

    addr label_addr = solveAddr(label_full_addr);
    short offset = label_addr - pos - 1;
    debug_print("solveRelReference: offset = (label_addr = %u) - (pos = %u) = %i\n", label_addr, pos, offset);
    return _formatNum(offset, size);
}

bin traducirADD(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirSUB(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirAND(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirOR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirADDI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatNum(op->args[2]->valor, 6);
}

bin traducirANDI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatSHNum(op->args[2]->valor, op->args[3]->valor);
}

bin traducirORI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatSHNum(op->args[2]->valor, op->args[3]->valor);
}

bin traducirBRp(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + solveRelReference(tabla, pos, op->args[0]->valor, 10);
}

bin traducirBRz(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + solveRelReference(tabla, pos, op->args[0]->valor, 10);
}

bin traducirBRn(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + solveRelReference(tabla, pos, op->args[0]->valor, 10);
}

bin traducirJR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirJALR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirTRAP(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirRETI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins);
}

bin traducirNOT(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8);
}

bin traducirJAL(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + solveRelReference(tabla, pos, op->args[0]->valor, 12);
}

bin traducirLD(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, pos, op->args[1]->valor, 9);
}

bin traducirST(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, pos, op->args[1]->valor, 9);
}

bin traducirLDR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirSTR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirLUI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + formatNum(op->args[1]->valor, 8);
}

bin traducirLORI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + shiftReg(op->args[0]->valor, 11) + formatNum(op->args[1]->valor, 8);
}

bin traducirLJMP(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return conseguirBaseInstruccion(op->ins) + solveRelReference(tabla, pos, op->args[0]->valor, 12);
}