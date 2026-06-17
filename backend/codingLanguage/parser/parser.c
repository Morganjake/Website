#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/token.h"
#include "../headers/astNode.h"
#include "../headers/variable.h"

#include "parserHeaders/typeConverter.h"
#include "parserHeaders/arithmetic.h"
#include "parserHeaders/functionCaller.h"


struct VariableExistsResult {
    struct Value value;
    int index;
};


// Gets a variable from the variable list
struct VariableExistsResult getVariable(char* name, struct Variables* variablesPtr) {

    for (int i = 0; i < variablesPtr->variableCount; i++) {
        if (strcmp(name, variablesPtr->variables[i].name) == 0) {
            return (struct VariableExistsResult) {variablesPtr->variables[i].value, i};
        }
    }

    return (struct VariableExistsResult) {(struct Value) {NullType, NULL}, -1};
}


struct Value parseNode(struct AstNode node, struct Variables* variablesPtr) {

    struct Variable var = (struct Variable) {"", (struct Value) {NullType, NULL}};

    if (node.type == ValueNode) {
        // node.token.tokenType - 2 works because the positions of the value tokens and types are offset by two in the enums
        return (struct Value) {node.token.tokenType - 2, convertTokenToType(node.token)};
    }
    else if (node.type == EmptyNode) {
        return (struct Value) {NullType, NULL};
    }
    else if (node.type == VariableNode) {
        struct VariableExistsResult res = getVariable(node.token.value, variablesPtr);
        return res.index == -1 ? (struct Value) {NullType, NULL} : res.value;
    }
    else if (node.type == AssignmentNode) {
        char* varName = node.childNodes[0].token.value;
        struct Value varValue = parseNode(node.childNodes[1], variablesPtr);

        struct VariableExistsResult res = getVariable(varName, variablesPtr);

        if (res.index == -1) { // Variable doesn't exist
            
            variablesPtr->variableCount++;
            variablesPtr->variables = realloc(variablesPtr->variables, variablesPtr->variableCount * sizeof(struct Variable));

            variablesPtr->variables[variablesPtr->variableCount - 1] = (struct Variable) {varName, varValue};
        }
        else {
            variablesPtr->variables[res.index] = (struct Variable) {varName, varValue};
        }
        return varValue;
    }
    else if (node.type == MathOperatorNode) {

        struct Value leftOperand = parseNode(node.childNodes[0], variablesPtr);
        struct Value rightOperand = parseNode(node.childNodes[1], variablesPtr);

        return calculateMath(leftOperand, rightOperand, node.token.value);
    }
    else if (node.type == FunctionNode) {
        
        struct Value* functionArgs = malloc(sizeof(struct Value) * node.childNodeCount);

        for (int i = 0; i < node.childNodeCount; i++) {
            functionArgs[i] = parseNode(node.childNodes[i], variablesPtr);
        }

        struct Value res = callFunction(node.token.value, (struct Values) {functionArgs, node.childNodeCount});
        return res;
    }
}