#include "ASTNode.h"
#include "variable.h"

#ifndef PARSE_H
#define PARSE_H

struct Value parseNode(struct AstNode node, struct Variables* variablesPtr);

#endif