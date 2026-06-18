#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/token.h"
#include "../Headers/astNode.h"
#include "../Headers/variable.h"
#include "../Headers/output.h"


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
        else {
            error("Maths Error: Strings are only allowed to be concatenated together");
        }
    }
    else {
        char *types[] = {
            "Null",
            "Integer",
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
