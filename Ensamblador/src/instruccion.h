#include "utils.h"

enum __instruccion{
    ADD = 1,
    SUB,
    AND,
    OR,
    ADDI,
    ANDI,
    ORI,
    BRp,
    BRz,
    BRn,
    JR,
    JALR,
    TRAP,
    RETI,
    NOT,
    JAL,
    LD,
    ST,
    LDR,
    STR,
    LUI,
    LORI,
    LJMP,
    NULL_INS
};

typedef enum __instruccion Instruccion;

Instruccion deString(char token[]);

int conseguirArgsTipo(Instruccion ins, int args[5]);

bin conseguirBase(Instruccion ins);

Traductor conseguirTraduccion(Instruccion ins);
