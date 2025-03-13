#ifndef LCCCC_ALIAS
#define LCCCC_ALIAS

#include "utils.h"
#include "argumentos.h"

AliasOp initAliasOperacion(Alias alias, Argumento args[]);

Operacion* expandirAliasOp(AliasOp aliasop, int* op_c);

void freeAliasOp(AliasOp aliasop);


#endif
