#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/token.h"
#include "../headers/output.h"

// Maximum size of a single token
#define MaxTokenBufferSize 1024 * 8


bool isAlphabetic(char Char) {
	return (Char >= 65 && Char <= 90) || (Char >= 97 && Char <= 122);
}


bool isNumeric(char Char) {
	return Char >= 48 && Char <= 57;
}


bool isAlphanumeric(char Char) {
	return isAlphabetic(Char) || isNumeric(Char);
}


// Function to reset the token buffer and update the list of tokens
void updateTokens(struct Token** TokensPtr, char* TokenBuffer, int* TokenCountPtr,
	int* TokenBufferLocationPtr, enum TokenType TokenType) {

	*TokensPtr = realloc(*TokensPtr, (*TokenCountPtr + 1) * sizeof(struct Token));

	(*TokensPtr)[*TokenCountPtr].value = malloc(strlen(TokenBuffer) + 1);
	strcpy((*TokensPtr)[*TokenCountPtr].value, TokenBuffer);

	(*TokensPtr)[*TokenCountPtr].tokenType = TokenType;

	// Resets TokenBuffer
	memset(TokenBuffer, 0, MaxTokenBufferSize);

	*TokenBufferLocationPtr = 0;
	(*TokenCountPtr)++;
}


struct Tokens tokenizeLine(char* line) {
    struct Tokens tokens;
    tokens.tokens = NULL;
    tokens.tokenCount = 0;

    char tokensBuffer[MaxTokenBufferSize];
    memset(tokensBuffer, 0, MaxTokenBufferSize);
    int TokenBufferLocation = 0;

    int i = 0;

    int bracketCount = 0; // Verifies that every opening bracket has a valid corresponding closing bracket

    while (i < strlen(line)) {

        if (line[i] == ' ') {
            i++;
        }
        else if (isAlphabetic(line[i])) {

            while (isAlphanumeric(line[i]) || line[i] == '_' || line[i] == '-') {
                tokensBuffer[TokenBufferLocation] = line[i];
                TokenBufferLocation++;
                i++;
            }
            tokensBuffer[TokenBufferLocation] = '\0';
            if (i < strlen(line) && line[i] == '(') {
                updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, FunctionToken);
            }
            else {
                updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, VariableToken);
            }
        }
        else if (isNumeric(line[i])) {

            bool hasDecimal = false;

            while (isNumeric(line[i]) || line[i] == '.') {
                if (line[i] == '.') {
                    if (hasDecimal) { error("Syntax Error: Too many decimal points in float value"); }
                    hasDecimal = true;
                }
                tokensBuffer[TokenBufferLocation] = line[i];
                TokenBufferLocation++;
                i++;
            }
            tokensBuffer[TokenBufferLocation] = '\0';
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, hasDecimal ? FloatToken : IntegerToken);
        }
        else if (line[i] == '"') {
            i++; // Skip the opening quote

            while (line[i] != '"' && line[i] != '\0') {
                tokensBuffer[TokenBufferLocation] = line[i];
                TokenBufferLocation++;
                i++;
            }
            tokensBuffer[TokenBufferLocation] = '\0';
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, StringToken);

            if (line[i] == '"') { i++; } // Skip the closing quote
        }
        else if (line[i] == '(' || line[i] == ')') {

            if (line[i] == '(') {
                bracketCount++;
            }
            else if (line[i] == ')') {
                bracketCount--;
                if (bracketCount < 0) { error("Syntax Error: Invalid brackets"); }
            }

            tokensBuffer[0] = line[i];
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, BracketToken);
            i++;
        }
        else if (line[i] == '=') {
            tokensBuffer[0] = line[i];
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, AssignmentToken);
            i++;
        }
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '\\') { // Yeah the divisor is flipped for C reasons
            tokensBuffer[0] = line[i];
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, MathOperatorToken);
            i++;
        }
        else if (line[i] == ',') {
            tokensBuffer[0] = line[i];
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, CommaToken);
            i++;
        }
        else if (line[i] == ';') {
            tokensBuffer[0] = line[i];
            updateTokens(&tokens.tokens, tokensBuffer, &tokens.tokenCount, &TokenBufferLocation, EOLToken);
            i++;
        }
        else {
            error("Syntax Error: Invalid syntax");
        }
    }

    if (bracketCount > 0) { error("Syntax Error: Invalid brackets"); }

    return tokens;
}