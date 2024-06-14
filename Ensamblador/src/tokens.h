#include "utils.h"

Token* parsearTokens(char linea[], int* c_tkn);

Token initToken(char token[]);

void freeToken(Token token);

void comoStringToken(Token token, char copia[]);

int lengthToken(Token token);
