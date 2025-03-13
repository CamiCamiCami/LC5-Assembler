#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;  // Declare yyin
int yyparse();      // Declare yyparse

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Failed to open file");
        return 1;
    }

    yyin = inputFile;  // Set yyin to the input file
    yyparse();         // Call the parser
    fclose(inputFile); // Close the file after parsing
    return 0;
}