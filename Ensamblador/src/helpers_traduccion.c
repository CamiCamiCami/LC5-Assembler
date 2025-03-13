#include "helpers.h"


#define DEBUG 1
#define debug_print(...) do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

void checkArgsOperacion(Operacion op){
    Instruction ins = op->ins;
    Argumento* args = op->args;
    int c_arg = op->argc;

    ArgsTipo* esperado = ins->args_tipos;
    int c_esperado = ins->argc;

    debug_print("Chequeando operacion %s\n", ins->name);
    
    for (int i = 0; i < c_arg; i++)
        printArgumento(args[i]);

    for (int i = 0; i < c_esperado; i++){
        char repr[50];
        argTipoComoStr(esperado[i], repr);
        debug_print("esperado[%i] = %s\n", i, repr);
    }
    for (int i = 0; i < c_arg; i++){
        debug_print("%i | ", args[i]->tipo);
        char repr[50];
        argTipoComoStr(args[i]->tipo, repr);
        debug_print("args[%i]->tipo = %s\n", i, repr);
    }

    if(c_arg != c_esperado){
        // Manejo de Error
        fprintf(stderr, "Argumentos invalidos para opracion %s. Esperaba %i argumento/s pero recibio %i\n", ins->name, c_esperado, c_arg);
        exit(1);
    }

    for (int i = 0; i < c_esperado; i++){
        if (!(esperado[i] & args[i]->tipo)){
            // Manejo de Error
            char str_esperado[50], str_recibido[50];
            argTipoComoStr(esperado[i], str_esperado);
            argTipoComoStr(args[i]->tipo, str_recibido);
            fprintf(stderr, "Argumentos invalidos para operacion %s. en la posicion %i, esperaba tipo %s pero recibio tipo %s\n", op->ins->name, i+1, str_esperado, str_recibido);
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


/*
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
*/

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

bin traducirArimetica(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + shiftReg(op->args[2]->valor, 5);
}

bin traducirADDI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatNum(op->args[2]->valor, 6);
}

bin traducirBranch(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + solveRelReference(tabla, pos, op->args[0]->valor, 9);
}

bin traducirJUMP(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + solveRelReference(tabla, pos, op->args[0]->valor, 11);
}

bin traducirJR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 8);
}

bin traducirJALR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 8);
}

bin traducirTRAP(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + formatNum(op->args[0]->valor, 5);
}

bin traducirJAL(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + solveRelReference(tabla, pos, op->args[0]->valor, 11);
}

bin traducirLD(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, pos, op->args[1]->valor, 9);
}

bin traducirST(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + solveRelReference(tabla, pos, op->args[1]->valor, 9);
}

bin traducirLDR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatNum(op->args[2]->valor, 6);
}

bin traducirSTR(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + shiftReg(op->args[1]->valor, 8) + formatNum(op->args[2]->valor, 6);
}

bin traducirLUI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + formatNum(op->args[1]->valor, 8);
}

bin traducirLORI(Operacion op, SymTable tabla, addr pos){
    checkArgsOperacion(op);
    return op->ins->base + shiftReg(op->args[0]->valor, 11) + formatNum(op->args[1]->valor, 8);
}

bin traducirRTI(Operacion op, SymTable tabla, addr pos) {
    checkArgsOperacion(op);
    return op->ins->base;
}