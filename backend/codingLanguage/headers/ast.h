#include "Token.h"
#include "ASTNode.h"

#ifndef AST_H
#define AST_H

struct AstNode createAST(struct Tokens tokens, int startIndex);
struct AstNode layerAST(struct AstNode* asts, int startIdx, int lineCount);

#endif