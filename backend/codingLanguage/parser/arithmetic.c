#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Headers/token.h"
#include "../Headers/astNode.h"
#include "../Headers/variable.h"
#include "../Headers/output.h"


struct Value calculateMath(struct Value leftOperand, struct Value rightOperand, char* operator) {

    struct Value res = (struct Value) {NullType, NULL};

    bool leftIsBool = false;
    bool rightIsBool = false;

    if (leftOperand.type == BooleanType) {
        leftOperand.type = IntegerType;
        leftIsBool = true;
    }
    if (rightOperand.type == BooleanType) {
        rightOperand.type = IntegerType;
        rightIsBool = true;
    }

    if (leftOperand.type == IntegerType && rightOperand.type == IntegerType) {

        int leftValue = *leftOperand.valuePtr;
        int rightValue = *rightOperand.valuePtr;

        int* resultPtr = malloc(sizeof(int));

        switch (operator[0]) {
            case '+': *resultPtr = leftValue + rightValue; break;
            case '-': *resultPtr = leftValue - rightValue; break;
            case '*': *resultPtr = leftValue * rightValue; break;
            case '\\': *resultPtr = leftValue / rightValue; break;
        }
        if (leftIsBool && rightIsBool) { // If both operands are bools, then the result needs to be unconverted back to a boolean
            res.type = BooleanType;
            *resultPtr = resultPtr == 0 ? 0 : 1;
        }
        else {
            res.type = IntegerType;
        }
        res.valuePtr = resultPtr;
    }
    else if (leftOperand.type == FloatType && rightOperand.type == FloatType) {
        float leftValue = *(float*) leftOperand.valuePtr;
        float rightValue = *(float*) rightOperand.valuePtr;

        float* resultPtr = malloc(sizeof(float));

        switch (operator[0]) {
            case '+': *resultPtr = leftValue + rightValue; break;
            case '-': *resultPtr = leftValue - rightValue; break;
            case '*': *resultPtr = leftValue * rightValue; break;
            case '\\': *resultPtr = leftValue / rightValue; break;
        }

        res.type = FloatType;
        res.valuePtr = (int*) resultPtr;
    }
    else if (leftOperand.type == IntegerType && rightOperand.type == FloatType ||
        leftOperand.type == FloatType && rightOperand.type == IntegerType) {

        float leftValue;
        float rightValue;
        if (leftOperand.type == IntegerType && rightOperand.type == FloatType) {
            leftValue = (float) *leftOperand.valuePtr;
            rightValue = *(float*) rightOperand.valuePtr;
        }
        else {
            leftValue = *(float*) leftOperand.valuePtr;
            rightValue = (float) *rightOperand.valuePtr;
        }
        float* resultPtr = malloc(sizeof(float));

        switch (operator[0]) {
            case '+': *resultPtr = leftValue + rightValue; break;
            case '-': *resultPtr = leftValue - rightValue; break;
            case '*': *resultPtr = leftValue * rightValue; break;
            case '\\': *resultPtr = leftValue / rightValue; break;
        }

        res.type = FloatType;
        res.valuePtr = (int*) resultPtr;
    }
    else if (leftOperand.type == StringType && rightOperand.type == StringType) {

        // Only + is supported for strings
        if (operator[0] == '+') {
            char* leftValue = (char*) leftOperand.valuePtr;
            char* rightValue = (char*) rightOperand.valuePtr;

            char* resultPtr = malloc((strlen(leftValue) + strlen(rightValue) + 1) * sizeof(char));
            strcpy(resultPtr, leftValue);
            strcat(resultPtr, rightValue);

            res.type = StringType;
            res.valuePtr = (int*) resultPtr;
        }
        else {
            error("Maths Error: Strings are only allowed to be concatenated together");
        }
    }
    else {
        char *types[] = {
            "Null",
            "Integer",
            "Float",
            "Boolean",
            "String",
        };

        if (leftIsBool) { leftOperand.type = BooleanType; }
        if (rightIsBool) { rightOperand.type = BooleanType; }

        errorf5("Maths Error: Unsupported operations for types \"", types[leftOperand.type], "\" and \"", types[rightOperand.type],  "\"");
    }

    return res;
}


struct Value calculateLogic(struct Value leftOperand, struct Value rightOperand, char* operator) {

    struct Value res = (struct Value) {BooleanType, NULL};
    int* resultPtr = malloc(sizeof(int));

    bool leftIsBool = false;
    bool rightIsBool = false;

    if (leftOperand.type == BooleanType) {
        leftOperand.type = IntegerType;
        leftIsBool = true;
    }
    if (rightOperand.type == BooleanType) {
        rightOperand.type = IntegerType;
        rightIsBool = true;
    }

    if (leftOperand.type == IntegerType && rightOperand.type == IntegerType) {
        int leftValue = *leftOperand.valuePtr;
        int rightValue = *rightOperand.valuePtr;

        if (strcmp(operator, "==") == 0) { *resultPtr = leftValue == rightValue ? 1 : 0; }
        if (strcmp(operator, "!=") == 0) { *resultPtr = leftValue != rightValue ? 1 : 0; }
        if (strcmp(operator, "<") == 0) { *resultPtr = leftValue < rightValue ? 1 : 0; }
        if (strcmp(operator, "<=") == 0) { *resultPtr = leftValue <= rightValue ? 1 : 0; }
        if (strcmp(operator, ">") == 0) { *resultPtr = leftValue > rightValue ? 1 : 0; }
        if (strcmp(operator, ">=") == 0) { *resultPtr = leftValue >= rightValue ? 1 : 0; }

        res.valuePtr = resultPtr;
    }
    else if (leftOperand.type == FloatType && rightOperand.type == FloatType) {
        float leftValue = *(float*) leftOperand.valuePtr;
        float rightValue = *(float*) rightOperand.valuePtr;

        if (strcmp(operator, "==") == 0) { *resultPtr = leftValue == rightValue ? 1 : 0; }
        if (strcmp(operator, "!=") == 0) { *resultPtr = leftValue != rightValue ? 1 : 0; }
        if (strcmp(operator, "<") == 0) { *resultPtr = leftValue < rightValue ? 1 : 0; }
        if (strcmp(operator, "<=") == 0) { *resultPtr = leftValue <= rightValue ? 1 : 0; }
        if (strcmp(operator, ">") == 0) { *resultPtr = leftValue > rightValue ? 1 : 0; }
        if (strcmp(operator, ">=") == 0) { *resultPtr = leftValue >= rightValue ? 1 : 0; }

        res.valuePtr = (int*) resultPtr;
    }
    else if (leftOperand.type == IntegerType && rightOperand.type == FloatType ||
        leftOperand.type == FloatType && rightOperand.type == IntegerType) {

        float leftValue;
        float rightValue;
        if (leftOperand.type == IntegerType && rightOperand.type == FloatType) {
            leftValue = (float) *leftOperand.valuePtr;
            rightValue = *(float*) rightOperand.valuePtr;
        }
        else {
            leftValue = *(float*) leftOperand.valuePtr;
            rightValue = (float) *rightOperand.valuePtr;
        }

        if (strcmp(operator, "==") == 0) { *resultPtr = leftValue == rightValue ? 1 : 0; }
        if (strcmp(operator, "!=") == 0) { *resultPtr = leftValue != rightValue ? 1 : 0; }
        if (strcmp(operator, "<") == 0) { *resultPtr = leftValue < rightValue ? 1 : 0; }
        if (strcmp(operator, "<=") == 0) { *resultPtr = leftValue <= rightValue ? 1 : 0; }
        if (strcmp(operator, ">") == 0) { *resultPtr = leftValue > rightValue ? 1 : 0; }
        if (strcmp(operator, ">=") == 0) { *resultPtr = leftValue >= rightValue ? 1 : 0; }

        res.valuePtr = (int*) resultPtr;
    }
    else if (leftOperand.type == StringType && rightOperand.type == StringType) {

        // Only + is supported for strings
        if (strcmp(operator, "==") == 0) {
            *resultPtr = strcmp((char*) leftOperand.valuePtr, (char*) rightOperand.valuePtr) == 0 ? 1 : 0;
            res.valuePtr = resultPtr;
        }
        else if (strcmp(operator, "!=") == 0) {
            *resultPtr = strcmp((char*) leftOperand.valuePtr, (char*) rightOperand.valuePtr) != 0 ? 1 : 0;
            res.valuePtr = resultPtr;
        }
        else {
            error("Logic Error: Unsupported operation for strings");
        }
    }
    else {
        char *types[] = {
            "Null",
            "Integer",
            "Float",
            "Boolean",
            "String",
        };

        if (leftIsBool) { leftOperand.type = BooleanType; }
        if (rightIsBool) { rightOperand.type = BooleanType; }

        errorf5("Logic Error: Unsupported operations for types \"", types[leftOperand.type], "\" and \"", types[rightOperand.type],  "\"");
    }
    return res;
}
