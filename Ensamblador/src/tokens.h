typedef char* Token;


int parsearTokens(char linea[], Token* tokens);

Token initToken(char token[]);

void freeToken(Token token);

void comoStringToken(Token token, char copia[]);

int lengthToken(Token token);

int comoOpcodeToken(Token token);
