#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/variable.h"
#include "../headers/output.h"
#include "../parser/parserHeaders/functionCaller.h"


struct Value print(struct Values args) {
    for (int i = 0; i < args.count; i++) {
        struct Value val = args.values[i];
        if (val.type == IntegerType) {
            printf("%d", *val.valuePtr);
        }
        else if (val.type == FloatType) {
            printf("%f\n", *(float*) val.valuePtr);
        }
        else if (val.type == StringType) {
            printf("%s", (char*) val.valuePtr);
        }

        printf(i != args.count - 1 ? ", " : "\n");
    }

    return returnInt(1);
}


struct Value convertToInt(struct Values args) {
    if (args.count != 1) { error("Argument Error: \"int\" function takes one input"); }
    struct Value arg = args.values[0];

    if (arg.type == IntegerType) {
        return returnInt(*arg.valuePtr);
    }
    else if (arg.type == FloatType) {
        return returnInt((int) *(float*) arg.valuePtr);
    }
    else if (arg.type == StringType) {
        char* string = (char*) arg.valuePtr;
        int pos = 0;

        if (strlen(string) == 0) {
            error("Value Error: Cannot convert empty string to integer");
        }
        
        if (string[0] == '-') {
            pos++;
            if (strlen(string) == 1) {
                error("Value Error: Cannot convert string \"-\" to integer");
            }
        }

        for (int i = pos; i < strlen(string); i++) {
            if (string[i] < 48 || string[i] > 57) {
                errorf("Value Error: Cannot convert string \"", string, "\" to integer");
            }
        }

        return returnInt(atoi((char*) arg.valuePtr));
    }
}


struct Value convertToFloat(struct Values args) {
    if (args.count != 1) { error("Argument Error: \"float\" function takes one input"); }
    struct Value arg = args.values[0];

    if (arg.type == IntegerType) {
        return returnFloat((float) *(int*) arg.valuePtr);
    }
    else if (arg.type == FloatType) {
        return returnFloat(*(float*) arg.valuePtr);
    }
    else if (arg.type == StringType) {
        char* string = (char*) arg.valuePtr;
        int pos = 0;

        if (strlen(string) == 0) {
            error("Value Error: Cannot convert empty string to float");
        }
        
        if (string[0] == '-') {
            pos++;
            if (strlen(string) == 1) {
                error("Value Error: Cannot convert string \"-\" to float");
            }
        }

        bool hasDecimal = false;

        for (int i = pos; i < strlen(string); i++) {
            if ((string[i] < 48 || string[i] > 57) && (string[i] == '.' && hasDecimal)) {
                errorf("Value Error: Cannot convert string \"", string, "\" to float");
            }
            if (string[i] == '.') { hasDecimal = true; }

        }

        return returnFloat(atof((char*) arg.valuePtr));
    }
}


struct Value convertToStr(struct Values args) {
    if (args.count != 1) { error("Argument Error: \"str\" function takes one input"); }
    struct Value arg = args.values[0];

    if (arg.type == IntegerType) {
        int numLen = snprintf(NULL, 0, "%d", *arg.valuePtr);
        char* stringBuffer = malloc(numLen + 1);
        snprintf(stringBuffer, numLen + 1, "%d", *arg.valuePtr);
        return returnString(stringBuffer);
    }
    else if (arg.type == FloatType) {
        int numLen = snprintf(NULL, 0, "%f", *(float*) arg.valuePtr);
        char* stringBuffer = malloc(numLen + 1);
        snprintf(stringBuffer, numLen + 1, "%f", *(float*) arg.valuePtr);
        return returnString(stringBuffer);
    }
    else if (arg.type == StringType) {
        return returnString((char*) arg.valuePtr);
    }
}