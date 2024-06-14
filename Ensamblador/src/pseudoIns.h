#include "utils.h"


PseudoIns deStringPseudoIns(char codigo[], bool* error);

void comoStringPseudoIns(PseudoIns psi, char repr[]);

unsigned int conseguirArgsTipoPseudoIns(PseudoIns psi, ArgsTipo args[5]);

void efectuarPseudoOp (ConsPrograma prog, Token tkns[], unsigned int c_tkns, char label[]);