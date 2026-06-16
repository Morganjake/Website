#include "../Headers/Token.h"

#ifndef OUTPUT_H
#define OUTPUT_H

void outputTokens(struct Tokens* allTokens, int lineCount);
void outputAst(struct AstNode* allAsts, int lineCount, int indentLevel);
void outputOutput();

#endif