#include "statement_builder.h"



StatementBuilder initStatementBuilder() {
    StatementBuilder new = malloc(sizeof(struct __statement_builder));
	new->label = NULL;
	new->insruction = NULL;
	new->arg_idx = 0;
	new->args = NULL;
    return new;
}

void addInstructionOrLabel(StatementBuilder builder, char* token) {
	bool err = false;
	void* ins = NULL;
	ins = deStringInstruccion(token, &err);
	if (!err) {
		builder->insruction = ins;
		builder->type = OPERATION;
		return;
	} 

	ins = deStringPseudoIns(token, &err);
	if(!err) {
		builder->insruction = ins;
		builder->type = PSEUDOOP;
		return;
	}

	ins = deStringAlias(token, &err);
	if(!err) {
		builder->insruction = ins;
		builder->type = ALIAS;
		return;
	} else {
		addLabel(builder, token);
		return;
	}
}

void addLabel(StatementBuilder builder, char* token) {
	if (builder->label != NULL) {
		// Manejo de Error
		exit(1);
	}

	builder->label = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(builder->label, token);
}

int argsRequired(StatementBuilder builder) {
	switch (builder->type) {
	case OPERATION: return ((Instruction)builder->insruction)->argc;
	case PSEUDOOP: return (((PseudoIns)builder->insruction)->necesita_arg ? 1 : 0);
	case ALIAS: return ((Alias)builder->insruction)->argc;
	default:
		// error
		exit(1);
	}
}

void addArgument(StatementBuilder builder, char* token) {
	if (builder->arg_idx >= argsRequired(builder)) {
		// error
		exit(1);
	}

	builder->args[builder->arg_idx++] = initArgumento(token);
}

void addTokenStatementBuilder(StatementBuilder builder, char* token) {
	if (builder->insruction == NULL) {
		addInstructionOrLabel(builder, token);
		int req_args = argsRequired(builder);
		if (req_args > 0) 
			builder->args = malloc(sizeof(Argumento) * req_args);
	} else {
		addArgument(builder, token);
	}
}

bool isFinishedStatementBuilder(StatementBuilder builder) {
	return builder->insruction != NULL && builder->arg_idx >= argsRequired(builder);
}

StatementType getTypeStatementBuilder(StatementBuilder builder) {
	return builder->type;
}

// Returns a statement struct: Operation, PseudoOp or Alias
void* buildStatement(StatementBuilder builder) {
	if (!isFinishedStatementBuilder(builder)) {
		// error
		exit(1);
	}

	void* ret = NULL;

	switch (builder->type) {
		case OPERATION: 
			ret = initOperacion(builder->insruction, (builder->args == NULL ? NULL : builder->args));
			break;
		case PSEUDOOP: 
			ret = initPseudoOp(builder->insruction, (builder->args == NULL ? NULL : builder->args[0]));
			break;
		case ALIAS: 
			ret = initAliasOperacion(builder->insruction, (builder->args == NULL ? NULL : builder->args));
			break;
		default:
			// error
			exit(1);
	}
}

void freeBuildStatement(StatementBuilder) {

}