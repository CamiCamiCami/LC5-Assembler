#include "traductor.h"
#include "utils.h"
#include <stdio.h>

// Detiene el programa si los argumentos pasados no corresponden
void checkArgs(Instruccion ins){
    InstruccionProcesador INS = ins->INS;
    Argumento* args = ins->args;
    int c_arg = ins->argc;

    int esperado[5];
    int c_esperado = conseguirArgsTipo(INS, esperado);

    if(c_arg != c_esperado){
        // Manejo de Error
        fprintf(stderr, "Argumentos invalidos para opracion %i. Esperaba %i argumento/s pero recibio %i\n", INS, c_esperado, c_arg);
        exit(1);
    }

    for (int i = 0; i < c_esperado; i++){
        if (esperado[i] != args[i]->tipo){
            // Manejo de Error
            fprintf(stderr, "Argumentos invalidos para operacion %i. en la posicion %i, esperaba tipo %i pero recibio tipo %i\n", INS, i+1, esperado[i], args[i]);
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

bin traducirADD(Instruccion ins, SymTable tabla){
    checkArgs(ins);
    return conseguirBase(ins->INS) + shiftReg(ins->args[0]->valor, 11) + shiftReg(ins->args[1]->valor, 8) + shiftReg(ins->args[2]->valor, 2);
}

bin traducirSUB(Instruccion ins, SymTable tabla){
    checkArgs(ins);
    return conseguirBase(ins->INS) + shiftReg(ins->args[0]->valor, 11) + shiftReg(ins->args[1]->valor, 8) + shiftReg(ins->args[2]->valor, 2);
}

bin traducirAND(Instruccion ins, SymTable tabla){
    checkArgs(ins);
    return conseguirBase(ins->INS) + shiftReg(ins->args[0]->valor, 11) + shiftReg(ins->args[1]->valor, 8) + shiftReg(ins->args[2]->valor, 2);
}

bin traducirOR(Instruccion ins, SymTable tabla){
    checkArgs(ins);
    return conseguirBase(ins->INS) + shiftReg(ins->args[0]->valor, 11) + shiftReg(ins->args[1]->valor, 8) + shiftReg(ins->args[2]->valor, 2);
}


