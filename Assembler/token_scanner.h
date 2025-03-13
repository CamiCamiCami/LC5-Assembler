#include "utils.h"


TokenScanner initScanner(char filename[]);

char* readToken(TokenScanner scanner);

bool hasNextToken(TokenScanner scanner);

void closeScanner(TokenScanner scanner);

