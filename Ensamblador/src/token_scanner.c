#include "token_scanner.h"

TokenScanner initScanner(char filename[]) {
    TokenScanner new_scanner = fopen(filename, "r");

    if (new_scanner == NULL) {
        // error
        exit(1);
    }

    return new_scanner;
}

char* createCommaString() {
    char* coma_str = malloc(sizeof(char) * 2);
    coma_str[0] = ',';
    coma_str[1] = '\0';
    return coma_str;
}

char readChar(TokenScanner scanner) {
    return fgetc(scanner);
}

bool isLegalChar(char c) {
    bool invisible = c <= 31 || c == 127;
    bool space = c == 32;
    bool number = 48 <= c && c <= 57;
    bool semicolon = c == 59;
    bool uppercase = 65 <= c && c <= 90;
    bool lowercase = 97 <= c && c <= 122;
    bool underscore = c == 95;
    bool comma = c == 44;
    return invisible || space || number || semicolon || uppercase || lowercase || underscore || comma;
}

bool isComma(char c) {
    return c == 44;
}

bool isEOF(char c) {
    return c == EOF;
}

bool isSpaceSeparator(char c) {
    bool invisible = c <= 31 || c == 127;
    bool space = c == 32;
    bool tab = c == 9; 
    bool newline = c == 10;
    return invisible || space || tab || newline;
}

#define BUFFER_SIZE_STEP 15
char* insert2buffer (char* buffer, int* idx, char insert) {
    bool canInsert = ((*idx) % BUFFER_SIZE_STEP) > 0;
    if (!canInsert) {
        buffer = realloc(buffer, (*idx) + BUFFER_SIZE_STEP);
    }
    buffer[*idx] = insert;
    (*idx)++;
    return buffer;
}

void skipSpaceCharacters(TokenScanner scanner) {
    char last;
    for (last = readChar(scanner); isSpaceSeparator(last) && !isEOF(last); last = readChar(scanner));

    if (!feof(scanner)) {
        fseek(scanner, -1, SEEK_CUR);
    }
}

char* readToken(TokenScanner scanner) {
    char first_chr = readChar(scanner);

    if (first_chr == '\"') {
        return readStringToken(scanner);
    }
    if (first_chr == ',') {
        return createComaString();
    }

    char* buffer = NULL;
    int bufferidx = 0;

    char last;
    for (last = readChar(scanner); !isSpaceSeparator(last) && !isComma(last) && !isEOF(last); last = readChar(scanner)) {
        if (!isLegalChar(last)) {
            // error
            exit(1);
        }

        insert2buffer(buffer, &bufferidx, last);
    }

    if (isComma(last)) {
        // Devuelve la coma al stream
        fseek(scanner, -1, SEEK_CUR);
    } else {
        skipSpaceCharacters(scanner);
    }

    insert2buffer(buffer, &bufferidx, '\0');
    return buffer;
}

bool isQuotationMark (char c) {
    return c == 34;
}

char* readStringToken(TokenScanner scanner) {
    char* buffer = NULL;
    int bufferidx = 0;
    insert2buffer(buffer, &bufferidx, '\"');

    char last;
    for (last = readChar(scanner); !isQuotationMark(last); last = readChar(scanner)) {
        if (last == '\\') {
            insert2buffer(buffer, &bufferidx, decode_escape(readChar(scanner)));
        } else if (isEOF(last)) {
            // error
            exit(1);
        } else {
            insert2buffer(buffer, &bufferidx, last);
        }
    }

    insert2buffer(buffer, &bufferidx, '\"');
    insert2buffer(buffer, &bufferidx, '\0');

    skipSpaceCharacters(scanner);

    return buffer;
}

bool hasNextToken(TokenScanner scanner) {
    return !feof(scanner);
}

void closeScanner(TokenScanner scanner) {
    fclose(scanner);
}
