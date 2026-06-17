#include <stdio.h>
#include <stdlib.h>

#include "../headers/token.h"
#include "../headers/astNode.h"


void outputTokens(struct Tokens* allTokens, int lineCount) {

    char* tokenTypeNames[] = {
        "EOL Token",
        "Variable Token",
        "Null Token",
        "Integer Token",
        "String Token",
        "Assignment Token",
        "Bracket Token",
        "Math Operator Token",
        "Function Token",
        "Comma Token"
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


void outputAst(struct AstNode* allAsts, int lineCount, int indentLevel) {

    char *astNodeTypeNames[] = {
        "Empty Node",
        "Value",
        "Variable Node",
        "Assignment Node",
        "Math Operator",
        "Function Node"
    };
    
    for (int i = 0; i < lineCount; i++) {
        struct AstNode ast = allAsts[i];
        
        if (ast.type == ValueNode && ast.token.tokenType == StringToken) {
            printf("%d\n%s\n\"%s\"\n", indentLevel, astNodeTypeNames[ast.type], ast.token.value);
        }
        else {
            printf("%d\n%s\n%s\n", indentLevel, astNodeTypeNames[ast.type], ast.token.value);
        }

        for (int k = 0; k < ast.childNodeCount; k++) {
            outputAst(&ast.childNodes[k], 1, indentLevel + 1);
        }
    }

    if (indentLevel == 0) { printf("END OF AST\n"); }
}
