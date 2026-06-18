#include "../Headers/token.h"
#include "../Headers/astNode.h"

#ifndef OUTPUT_H
#define OUTPUT_H

extern char* globalLine;

void outputTokens(struct Tokens* allTokens, int lineCount);
void outputAst(struct AstNode* allAsts, int lineCount, int indentLevel);
void error(char* errorMessage);

#endif