#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/token.h"
#include "headers/tokenizer.h"
#include "headers/ast.h"
#include "headers/astNode.h"
#include "headers/variable.h"
#include "headers/parse.h"
#include "headers/output.h"

#include "parser/parserHeaders/functionCaller.h"

#define VAR_OUTPUT_ID 1


int main(int argc, char *argv[]) {

    char* text = malloc(sizeof(char));
    text[0] = '\0';
    
    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);

        text = realloc(text, strlen(text) + len + 2);
        strcat(text, argv[i]);
        if (i < argc - 1) {
            text = realloc(text, strlen(text) + 2);
            strcat(text, " ");
        }
    }

    char** lines = malloc(sizeof(char*));
    int lineCount = 0;

    char* curLine = malloc(sizeof(char));
    curLine[0] = '\0';
    bool inString = false;

    for (int i = 0; text[i] != '\0'; i++) {

        // We don't add scope brackets to the line as we want them to be considered as a seperate line
        if (!((text[i] == '{' || text[i] == '}') && !inString)) {
            int len = strlen(curLine);
            if (len == 0 && text[i] == ' ') { continue; } // Don't add leading whitespace to the line
            curLine = realloc(curLine, len + 2);
            curLine[len] = text[i];
            curLine[len + 1] = '\0';
        }

        if (text[i] == '\n') {
            continue;
        }
        else if (text[i] == '"') {
            inString = !inString;
        }
        else if ((text[i] == ';' || text[i] == '{' || text[i] == '}') && !inString) {

            if (strlen(curLine) > 0) { // The only time this condition is false is when a scope bracket proceeds another scope bracket or semi-colon
                lines = realloc(lines, sizeof(char*) * (lineCount + 1));
                lines[lineCount] = malloc(strlen(curLine) + 1);
                strcpy(lines[lineCount], curLine);
                lineCount++;
            }

            free(curLine);
            curLine = malloc(sizeof(char));
            curLine[0] = '\0';

            // Because we did not add them to the line, we add them to their own seperate line
            if (text[i] == '{' || text[i] == '}') {
                lines = realloc(lines, sizeof(char*) * (lineCount + 1));
                lines[lineCount] = text[i] == '{' ? "{\0" : "}\0";
                lineCount++;
            }
        }
    }

    // Add the last line if it's not empty
    if (strlen(curLine) > 0) {
        lines = realloc(lines, sizeof(char*) * (lineCount + 1));
        lines[lineCount] = malloc(strlen(curLine) + 1);
        strcpy(lines[lineCount], curLine);
        lineCount++;
    }

    struct Tokens* allTokens = malloc(sizeof(struct Tokens) * lineCount);
    struct AstNode* allAsts = malloc(sizeof(struct AstNode) * lineCount);
    struct Variables variables = (struct Variables) {malloc(0), 0};

    for (int i = 0; i < lineCount; i++) {
        globalLine = lines[i];
        struct Tokens tokens = tokenizeLine(lines[i]);
        allTokens[i] = tokens;
    }
    
    outputTokens(allTokens, lineCount);

    for (int i = 0; i < lineCount; i++) {
        globalLine = lines[i];
        allAsts[i] = createAST(allTokens[i], 0);
    }

    struct AstNode scope = layerAST(allAsts, 0, lineCount);

    outputAst(scope, 0);
    
    parseNode(scope, &variables);

    outputVars(variables);

    free(allTokens);
    free(allAsts);
    free(variables.variables);

    free(text);
    free(curLine);
    free(lines);
    return 0;
}
