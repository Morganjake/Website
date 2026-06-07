#include <stdio.h>
#include <stdlib.h>

#include "../headers/Token.h"


void outputTokens(struct Tokens* allTokens, int lineCount) {

    char* tokenTypeNames[] = {
        "VariableToken",
        "AssignmentToken",
        "NullToken",
        "IntegerToken",
        "StringToken",
        "BracketToken",
        "MathOperatorToken",
        "EOLToken"
    };

    for (int i = 0; i < lineCount; i++) {
        struct Tokens tokens = allTokens[i];
        for (int j = 0; j < tokens.tokenCount; j++) {
            struct Token token = tokens.tokens[j];
            printf("%s\n", tokenTypeNames[token.tokenType]);
            printf("%s\n", token.value);
        }
    }
    printf("END OF TOKENS\n");
}


void outputAST() {
    printf("This is the Abstract Syntax Tree.\n");
    printf("END OF AST\n");
}


void outputOutput() {
    printf("This is the final output.\n");
}
