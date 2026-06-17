#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/token.h"
#include "../Headers/astNode.h"
#include "../Headers/variable.h"


struct Value calculateMath(struct Value leftOperand, struct Value rightOperand, char* operator) {

    struct Value res = (struct Value) {NullType, NULL};

    if (leftOperand.type == IntegerType && rightOperand.type == IntegerType) {
        int leftValue = *leftOperand.valuePtr;
        int rightValue = *rightOperand.valuePtr;

        int* resultPtr = malloc(sizeof(int));

        switch (operator[0]) {
            case '+': *resultPtr = leftValue + rightValue; break;
            case '-': *resultPtr = leftValue - rightValue; break;
            case '*': *resultPtr = leftValue * rightValue; break;
            case '/': *resultPtr = leftValue / rightValue; break;
        }

        res.type = IntegerType;
        res.valuePtr = resultPtr;
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
    }

    return res;
}
