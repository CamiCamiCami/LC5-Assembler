#include "operacion.h"
#include <stdio.h>
#include <stdbool.h>
#include "symtable/symtable.h"

void checkArgs(Operacion op){
    Instruccion ins = op->ins;
    Argumento* args = op->args;
    int c_arg = op->argc;

    int esperado[5];
    int c_esperado = conseguirArgsTipo(ins, esperado);

    if(c_arg != c_esperado){
        // Manejo de Error
        fprintf(stderr, "Argumentos invalidos para opracion %i. Esperaba %i argumento/s pero recibio %i\n", ins, c_esperado, c_arg);
        exit(1);
    }

    for (int i = 0; i < c_esperado; i++){
        if (esperado[i] != args[i]->tipo){
            // Manejo de Error
            fprintf(stderr, "Argumentos invalidos para operacion %i. en la posicion %i, esperaba tipo %i pero recibio tipo %i\n", ins, i+1, esperado[i], args[i]);
            exit(1);
        }
    }

    return true;
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

bin formatNum(unsigned int* n, unsigned int size){
    if(size > 12){
        // Manejo de Error
        fprintf(stderr, "formato de numero demasiado largo: %i bits\n", size);
        exit(1);
    }
    if (size == 0){
        // Manejo de Error
        fprintf(stderr, "formato de numero de largo 0 no tiene sentido\n", size);
        exit(1);
    }
    
    int max_val = (2^size) - 1;
    if (*n > max_val){
        // Manejo de Error
        fprintf(stderr, "Valor fuera de rango. esperaba 0-%i pero recibio %i\n", max_val, *n);
        exit(1);
    }

    return (bin) *n;
}

bin formatSHNum(unsigned int* SH, unsigned int* n){
    if (*SH > 4){
        // Manejo de Error
        fprintf(stderr, "Valor de shifteo fuera de rango. esperaba 0-4 pero recibio %i\n", *SH);
        exit(1);
    }
    bin b = formatNum(n, 4);
    return (bin)(b << *SH);
}

bin solveRelReference(SymTable table, addr orig, addr pos, char label[], unsigned int size){
    addr dest = orig + searchSymTable(table, label);
    addr offset = dest - pos - 1;
    return formatNum(offset, size);
}

bin traducirADD(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirSUB(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirAND(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirOR(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirADDI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatNum(op->args[2]->valor, 6);
}

bin traducirANDI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatSHNum(op->args[2]->valor, op->args[3]->valor);
}

bin traducirORI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatSHNum(op->args[2]->valor, op->args[3]->valor);
}

bin traducirBRp(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + solveRelReference(tabla, orig, pos, op->args[0]->valor, 10);
}

bin traducirBRz(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + solveRelReference(tabla, orig, pos, op->args[0]->valor, 10);
}

bin traducirBRn(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + solveRelReference(tabla, orig, pos, op->args[0]->valor, 10);
}

bin traducirJR(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirJALR(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirTRAP(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 8);
}

bin traducirRETI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins);
}

bin traducirNOT(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11), shiftReg(op->args[1]->valor, 8);
}

bin traducirJAL(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + solveRelReference(tabla, orig, pos, op->args[0]->valor, 12);
}

bin traducirLD(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11), solveRelReference(tabla, orig, pos, op->args[1]->valor, 9);
}

bin traducirST(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11), solveRelReference(tabla, orig, pos, op->args[1]->valor, 9);
}

bin traducirLDR(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirSTR(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 2);
}

bin traducirLUI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, orig, pos, op->args[1]->valor, 8);
}

bin traducirLORI(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, orig, pos, op->args[1]->valor, 8);
}

bin traducirLJMP(Operacion op, SymTable tabla, addr orig, addr pos){
    checkArgs(op);
    return conseguirBase(op->ins) + solveRelReference(tabla, orig, pos, op->args[0]->valor, 12);
}