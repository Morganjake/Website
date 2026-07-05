#include "../Headers/token.h"
#include "../Headers/astNode.h"

#ifndef OUTPUT_H
#define OUTPUT_H

extern char* globalLine;

void outputTokens(struct Tokens* allTokens, int lineCount);
void outputAst(struct AstNode* allAsts, int lineCount, int indentLevel);
void error(char* errorMessage);
void errorf(char* e1, char* e2, char* e3);
void errorf5(char* e1, char* e2, char* e3, char* e4, char* e5);

#endif