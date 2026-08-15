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
        "Math Operator Token",
        "Logical Operator Token",
        "Bracket Token",
        "Scope Bracket Token",
        "Selection Token",
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


void outputAst(struct AstNode ast, int indentLevel) {

    char *astNodeTypeNames[] = {
        "Scope Node",
        "Empty Node",
        "Value",
        "Variable Node",
        "Assignment Node",
        "Math Operator",
        "Logical Operator",
        "Selection Node",
        "Scope Bracket Node",
        "Function Node"
    };
    
    if (ast.type == ValueNode && ast.token.tokenType == StringToken) {
        printf("%d%d\n%d%s:\n%d\"%s\"\n", AST_OUTPUT_ID, indentLevel, AST_OUTPUT_ID, astNodeTypeNames[ast.type], AST_OUTPUT_ID, ast.token.value);
    }
    else if (ast.type == ScopeNode) {
        printf("%d%d\n%dScope Node\n%d\n", AST_OUTPUT_ID, indentLevel, AST_OUTPUT_ID, AST_OUTPUT_ID);
    }
    else {
        printf("%d%d\n%d%s:\n%d%s\n", AST_OUTPUT_ID, indentLevel, AST_OUTPUT_ID, astNodeTypeNames[ast.type], AST_OUTPUT_ID, ast.token.value);
    }

    for (int k = 0; k < ast.childNodeCount; k++) {

        if (ast.type == ScopeNode) {
            printf("%d%d\n%d\n%d\n", AST_OUTPUT_ID, indentLevel + 1, AST_OUTPUT_ID, AST_OUTPUT_ID);
        }
        
        outputAst(ast.childNodes[k], indentLevel + 1);

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


void errorf5(char* e1, char* e2, char* e3, char* e4, char* e5) {
    char* errMessage = malloc(sizeof(char) * (strlen(e1) + strlen(e2) + strlen(e3) + strlen(e4) + strlen(e5) + 1));
    strcpy(errMessage, e1);
    strcat(errMessage, e2);
    strcat(errMessage, e3);
    strcat(errMessage, e4);
    strcat(errMessage, e5);
    errMessage[strlen(e1) + strlen(e2) + strlen(e3) + strlen(e4) + strlen(e5)] = '\0';
    error(errMessage);
}