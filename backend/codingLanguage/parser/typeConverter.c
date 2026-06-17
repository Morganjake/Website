#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/token.h"

// Turns the text of a token into a value token's type then returns a pointer to it
int* convertTokenToType(struct Token token) {

    if (token.tokenType == IntegerToken) {
        int* valuePtr = malloc(sizeof(int));
        *valuePtr = atoi(token.value);
        return valuePtr;
    }
    else if (token.tokenType == StringToken) {
        char* valuePtr = malloc((strlen(token.value) + 1) * sizeof(char));
        strcpy(valuePtr, token.value);
        return (int*) valuePtr;
    }
}