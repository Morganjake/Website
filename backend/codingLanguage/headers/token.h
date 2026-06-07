#ifndef TOKENTYPES_H
#define TOKENTYPES_H

enum TokenType {
    VariableToken,
    AssignmentToken,
    NullToken,
    IntegerToken,
    StringToken,
    BracketToken,
    MathOperatorToken,
    EOLToken
};

struct Token {
    enum TokenType tokenType;
    char* value;
};

struct Tokens {
	struct Token* tokens;
	int tokenCount;
};

#endif