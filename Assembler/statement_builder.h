#ifndef LCCCC_STATEMENT_BUILDER
#define LCCCC_STATEMENT_BUILDER

#include "utils.h"
#include "argumentos.h"
#include "operacion.h"
#include "psoperacion.h"
#include "alias.h"


StatementBuilder initStatementBuilder();

void addTokenStatementBuilder(StatementBuilder builder, char* token);

bool isFinishedStatementBuilder(StatementBuilder builder);

// Returns a statement struct: Operation, PseudoOp or Alias
Statement buildStatement(StatementBuilder builder);

#endif