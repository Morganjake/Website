#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/token.h"
#include "../headers/astNode.h"
#include "../headers/output.h"

struct AstNodes {
    struct AstNode* nodes;
    int nodeCount;
};


struct AstNode buildAST(struct AstNodes astNodes);
struct AstNode createAST(struct Tokens tokens, int startIndex);


struct AstNodes createASTArray(struct Tokens tokens, int startIndex) {
    struct AstNode* nodes = malloc(sizeof(struct AstNode) * (tokens.tokenCount - startIndex));
    int nodeCount = 0;

    for (int i = startIndex; i < tokens.tokenCount; i++) {
        struct AstNode node;
        node.token = tokens.tokens[i];
        node.childNodes = NULL; // This is needed for reallocations without any allocations
        node.childNodeCount = 0; // This is needed to prevent the value of child node count being some random number
        switch(tokens.tokens[i].tokenType) {
            case EOLToken: return (struct AstNodes) {nodes, nodeCount};
            case VariableToken: node.type = VariableNode; break;
            case NullToken: node.type = ValueNode; break;
            case IntegerToken: node.type = ValueNode; break;
            case FloatToken: node.type = ValueNode; break;
            case BooleanToken: node.type = ValueNode; break;
            case StringToken: node.type = ValueNode; break;
            case AssignmentToken:
                node.type = AssignmentNode;
                struct AstNode variableName = buildAST((struct AstNodes) {nodes, nodeCount});
                struct AstNode value = createAST(tokens, i + 1);

                if (variableName.type != VariableNode) {
                    error("Syntax Error: Only variables can be assigned to");
                }
                else if (value.type == EmptyNode) {
                    error("Syntax Error: Variable needs value to be assigned");
                }

                node.childNodes = malloc(sizeof(struct AstNode) * 2);
                node.childNodeCount = 2;
                node.childNodes[0] = variableName;
                node.childNodes[1] = value;
                nodes[0] = node;
                return (struct AstNodes) {nodes, 1};
            case BracketToken:
                int firstBracketPos = i;
                int bracketCount = 1;

                while (bracketCount != 0 && i < tokens.tokenCount) {
                    i++;
                    if (tokens.tokens[i].tokenType == BracketToken && strcmp(tokens.tokens[i].value, "(") == 0) { bracketCount++; }
                    if (tokens.tokens[i].tokenType == BracketToken && strcmp(tokens.tokens[i].value, ")") == 0) { bracketCount--; }
                }
                node = createAST((struct Tokens) {tokens.tokens, i}, firstBracketPos + 1);
                break;
            case ScopeBracketToken: node.type = ScopeBracketNode; break;
            case MathOperatorToken: node.type = MathOperatorNode; break;
            case LogicalOperatorToken: node.type = LogicalOperatorNode; break;
            case SelectionToken:
                node.type = SelectionNode;

                struct AstNode condition = createAST(tokens, i + 1);

                if (condition.type == EmptyNode) {
                    error("Syntax Error: empty condition not allowed");
                }

                node.childNodes = malloc(sizeof(struct AstNode) * 2);
                node.childNodeCount = 1;
                node.childNodes[0] = condition;
                nodes[0] = node;
                return (struct AstNodes) {nodes, 1};
            case FunctionToken:
                node.type = FunctionNode;
                i += 1; // Skip function and bracket token (if a function token exists it is always followed by an open bracket)
                int argStart = i + 1;
                bracketCount = 1;
                while (bracketCount != 0 && i < tokens.tokenCount) {
                    i++;
                    if (tokens.tokens[i].tokenType == BracketToken && strcmp(tokens.tokens[i].value, "(") == 0) { bracketCount++; }
                    if (tokens.tokens[i].tokenType == BracketToken && strcmp(tokens.tokens[i].value, ")") == 0) { bracketCount--; }
                    if (tokens.tokens[i].tokenType == CommaToken || bracketCount == 0) {
                        if (argStart == i) { break; } // Means the function has no arguments
                        struct AstNode arg = createAST((struct Tokens) {tokens.tokens, i}, argStart);
                        node.childNodes = realloc(node.childNodes, sizeof(struct AstNode) * (node.childNodeCount + 1));
                        node.childNodes[node.childNodeCount] = arg;
                        node.childNodeCount += 1;
                        argStart = i + 1;
                    }
                }
                break;
        }

        nodes[nodeCount] = node;
        nodeCount++;
    }

    return (struct AstNodes) {nodes, nodeCount};
}


void removeASTNode(struct AstNodes* astNodes, int index) {
    struct AstNode* newAstNodes = malloc(sizeof(struct AstNode) * (astNodes->nodeCount - 1));

    int j = 0;
    for (int i = 0; i < astNodes->nodeCount; i++) {
        if (i != index) {
            newAstNodes[j] = astNodes->nodes[i];
            j++;
        }
    }

    free(astNodes->nodes);
    astNodes->nodes = newAstNodes;
    astNodes->nodeCount -= 1;
}


struct AstNode createAST(struct Tokens tokens, int startIndex) {
    struct AstNodes astNodes = createASTArray(tokens, startIndex);
    return buildAST(astNodes);
}


struct AstNode buildAST(struct AstNodes astNodes) {

    if (astNodes.nodeCount == 0) {
        return (struct AstNode) { EmptyNode, NullToken, NULL, 0};
    }

    for (int i = 0; i < astNodes.nodeCount; i++) {
        struct AstNode node = astNodes.nodes[i];
        if (node.childNodeCount != 0) { continue; } // If the node already has children it has already been built and should be a sub-node
        if (node.type == MathOperatorNode && (strcmp(node.token.value, "*") == 0 || strcmp(node.token.value, "\\") == 0)) {

            if (i == 0 || astNodes.nodes[i - 1].type == EmptyNode) { // If i is 0 there is nothing to the left of the operator
                error("Syntax Error: Operator missing left operand");
            }
            else if (i == astNodes.nodeCount - 1 || astNodes.nodes[i + 1].type == EmptyNode) {
                error("Syntax Error: Operator missing right operand");
            }

            node.childNodes = malloc(sizeof(struct AstNode) * 2);
            node.childNodeCount = 2;
            node.childNodes[0] = astNodes.nodes[i - 1]; node.childNodes[1] = astNodes.nodes[i + 1];
            removeASTNode(&astNodes, i + 1);  removeASTNode(&astNodes, i - 1);
            astNodes.nodes[i - 1] = node;
            i--;
        }
    }

    for (int i = 0; i < astNodes.nodeCount; i++) {
        struct AstNode node = astNodes.nodes[i];
        if (node.childNodeCount != 0) { continue; } // If the node already has children it has already been built and should be a sub-node
        if (node.type == MathOperatorNode && (strcmp(node.token.value, "+") == 0 || strcmp(node.token.value, "-") == 0)) {
            if (i == 0 || astNodes.nodes[i - 1].type == EmptyNode) { // If i is 0 there is nothing to the left of the operator
                error("Syntax Error: Operator missing left operand");
            }
            else if (i == astNodes.nodeCount - 1 || astNodes.nodes[i + 1].type == EmptyNode) {
                error("Syntax Error: Operator missing right operand");
            }

            node.childNodes = malloc(sizeof(struct AstNode) * 2);
            node.childNodeCount = 2;
            node.childNodes[0] = astNodes.nodes[i - 1]; node.childNodes[1] = astNodes.nodes[i + 1];
            removeASTNode(&astNodes, i + 1);  removeASTNode(&astNodes, i - 1);
            astNodes.nodes[i - 1] = node;
            i--;
        }
    }

    for (int i = 0; i < astNodes.nodeCount; i++) {
        struct AstNode node = astNodes.nodes[i];
        if (node.childNodeCount != 0) { continue; } // If the node already has children it has already been built and should be a sub-node
        if (node.type == LogicalOperatorNode) {
            
            if (i == 0 || astNodes.nodes[i - 1].type == EmptyNode) { // If i is 0 there is nothing to the left of the operator
                error("Syntax Error: Operator missing left operand");
            }
            else if (i == astNodes.nodeCount - 1 || astNodes.nodes[i + 1].type == EmptyNode) {
                error("Syntax Error: Operator missing right operand");
            }

            node.childNodes = malloc(sizeof(struct AstNode) * 2);
            node.childNodeCount = 2;
            node.childNodes[0] = astNodes.nodes[i - 1]; node.childNodes[1] = astNodes.nodes[i + 1];
            removeASTNode(&astNodes, i + 1);  removeASTNode(&astNodes, i - 1);
            astNodes.nodes[i - 1] = node;
            i--;
            
        }
    }

    if (astNodes.nodeCount != 1) {
        error("Syntax Error: Invalid syntax");
    }

    return astNodes.nodes[0];
}


struct AstNode layerAST(struct AstNode* asts, int startIdx, int lineCount) {

    struct AstNode scope = (struct AstNode) {ScopeNode, NullToken, NULL, 0};
    int newLineCount = 0;

    int i = startIdx;
    while (i < lineCount) {
        struct AstNode ast  = asts[i];

        scope.childNodes = realloc(scope.childNodes, sizeof(struct AstNode) * (scope.childNodeCount + 1));

        if (ast.type == SelectionNode) {
            if (i >= lineCount - 2) { error("Syntax Error: Invalid brackets"); }
            
            i++;
            int firstBracketPos = i + 1;
            int bracketCount = 1;
            
            while (i < lineCount && bracketCount > 0) {
                i++;
                if (asts[i].type == ScopeBracketNode) {
                    if (strcmp(asts[i].token.value, "{") == 0) { bracketCount++; }
                    if (strcmp(asts[i].token.value, "}") == 0) { bracketCount--; }
                }
            }

            if (bracketCount > 0) {
                error("Syntax Error: Invalid brackets");
            }

            ast.childNodeCount++;
            ast.childNodes[1] = layerAST(asts, firstBracketPos, i);
        }
        else if (ast.type == ScopeBracketNode) {
            error("Syntax Error: Invalid brackets");
        }

        scope.childNodes[scope.childNodeCount] = ast;
        scope.childNodeCount++;
        i++;
    }

    return scope;
}