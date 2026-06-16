#include "Token.h"
#include "ASTNode.h"

#ifndef AST_H
#define AST_H

struct AstNode createAST(struct Tokens tokens, int startIndex);

#endif