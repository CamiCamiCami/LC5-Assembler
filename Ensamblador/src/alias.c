#include "alias.h"

AliasOp initAliasOperacion(Alias alias, Argumento args[], int argc) {
    AliasOp aliasop = malloc(sizeof(struct __alias_operacion));
    aliasop->alias = alias;
    aliasop->args = malloc(sizeof(Argumento) * argc);
    for (int i = 0; i < argc; i++) {
        aliasop->args[i] = args[i];
    }
    aliasop->argc = argc;
    return aliasop;
}

Operacion* expandirAliasOp(AliasOp aliasop, int* op_c) {
    return aliasop->alias->expandir(aliasop, op_c);
}

void freeAliasOp(AliasOp aliasop) {
    for (int i = 0; i < aliasop->argc; i++)
        freeArgumento(aliasop->args[i]);
    free(aliasop->args);
    free(aliasop);
}