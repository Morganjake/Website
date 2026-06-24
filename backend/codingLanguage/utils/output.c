#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/token.h"
#include "../headers/astNode.h"

#define ERR_OUTPUT_ID 2
#define TOK_OUTPUT_ID 3
#define AST_OUTPUT_ID 4

char* globalLine;

void outputTokens(struct Tokens* allTokens, int lineCount) {

    char* tokenTypeNames[] = {
        "EOL Token",
        "Variable Token",
        "Null Token",
        "Integer Token",
        "Float Token",
        "Boolean Token",
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
            printf("%d%s\n", TOK_OUTPUT_ID, tokenTypeNames[token.tokenType]);
            printf("%d%s\n", TOK_OUTPUT_ID, token.value);
        }
    }
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
            printf("%d%d\n%d%s\n%d\"%s\"\n", AST_OUTPUT_ID, indentLevel, AST_OUTPUT_ID, astNodeTypeNames[ast.type], AST_OUTPUT_ID, ast.token.value);
        }
        else {
            printf("%d%d\n%d%s\n%d%s\n", AST_OUTPUT_ID, indentLevel, AST_OUTPUT_ID, astNodeTypeNames[ast.type], AST_OUTPUT_ID, ast.token.value);
        }

        for (int k = 0; k < ast.childNodeCount; k++) {
            outputAst(&ast.childNodes[k], 1, indentLevel + 1);
        }
    }
}


void error(char* errorMessage) {
    printf("%d%s\n", ERR_OUTPUT_ID, globalLine);
    printf("%d%s\n", ERR_OUTPUT_ID, errorMessage);
    exit(0);
}


void errorf(char* e1, char* e2, char* e3) {
    char* errMessage = malloc(sizeof(char) * (strlen(e1) + strlen(e2) + strlen(e3) + 1));
    strcpy(errMessage, e1);
    strcat(errMessage, e2);
    strcat(errMessage, e3);
    errMessage[strlen(e1) + strlen(e2) + strlen(e3)] = '\0';
    error(errMessage);
}