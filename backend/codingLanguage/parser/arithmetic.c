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

        res.type = IntegerType;
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

        char* l = types[leftOperand.type]; char* r = types[rightOperand.type];
        char* errMessage = malloc(sizeof(char) * (strlen("Maths Error: Unsupported operations for types \"") + strlen(l) + strlen("\" and \"") + strlen(r) + strlen("\"")));
        strcpy(errMessage, "Maths Error: Unsupported operations for types \"");
        strcat(errMessage, l); strcat(errMessage, "\" and \""); strcat(errMessage, r); strcat(errMessage, "\"");

        error(errMessage);
        error("Maths Error: Unsupported operations for types ");
    }

    return res;
}
