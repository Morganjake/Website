#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/variable.h"
#include "../headers/output.h"

#include "../modules/stdlib.c"

#define STD_OUTPUT_ID 0
#define VAR_OUTPUT_ID 1


struct Value returnInt(int i) {
    int* resPtr = malloc(sizeof(int));
    *resPtr = i;
    return (struct Value) {IntegerType, resPtr};
}


struct Value returnString(char* s) {
    char* resPtr = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(s, resPtr);
    return (struct Value) {IntegerType, (int*) resPtr};
}


// Outputs the variables for the frontend
// It's here so I can use the print function without needing an stdlib header file
void outputVars(struct Variables variables) {
    for (int i = 0; i < variables.variableCount; i++) {
        printf("%d", VAR_OUTPUT_ID);
        printf("%s: ", variables.variables[i].name);

        struct Value* valContainer = malloc(sizeof(struct Values));
        valContainer[0] = variables.variables[i].value;

        print((struct Values) {valContainer, 1});
    } 
}


struct Value callFunction(char* functionName, struct Values args) {
    
    if (strcmp(functionName, "print") == 0) {
        printf("%d", STD_OUTPUT_ID);
        return print(args);
    }
    else {
        char* errMessage = malloc(sizeof(char) * (strlen("Function Error: unkown function \"") + strlen(functionName) + 4));
        strcpy(errMessage, "Function Error: unkown function \"");
        strcat(errMessage, functionName);
        strcat(errMessage, "()\"");
        error(errMessage);
    }
}