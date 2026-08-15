
#include "Token.h"

#ifndef ASTNODE_H
#define ASTNODE_H

enum astNodeType {
    ScopeNode,
    EmptyNode,
    ValueNode,
    VariableNode,
    AssignmentNode,
    MathOperatorNode,
    LogicalOperatorNode,
    SelectionNode,
    ScopeBracketNode,
    FunctionNode
};


struct AstNode {
    enum astNodeType type;
    struct Token token;
    struct AstNode* childNodes;
    int childNodeCount;
};

#endif