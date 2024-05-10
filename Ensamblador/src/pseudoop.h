#include "utils.h"


PseudoOp deStringPseudoOp(char codigo[]);

void comoStringPseudoOp(PseudoOp pso, char repr[]);

AfectarPrograma efectoPseudoOp(PseudoOp pso); 

unsigned int conseguirArgsTipoPseudoOp(PseudoOp pso, ArgsTipo args[5]);