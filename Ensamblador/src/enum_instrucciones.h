
typedef unsigned short bin;

enum __instrucciones_base{
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
    LJMP
};

typedef enum __instrucciones_base InstruccionProcesador;

InstruccionProcesador deString(char token[]);

int conseguirArgsTipo(InstruccionProcesador INS, int args[5]);

bin conseguirBase(InstruccionProcesador INS);