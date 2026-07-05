#ifndef TOKENTYPES_H
#define TOKENTYPES_H

enum TokenType {
    EOLToken,
    VariableToken,
    NullToken,
    IntegerToken,
    FloatToken,
    BooleanToken,
    StringToken,
    AssignmentToken,
    BracketToken,
    MathOperatorToken,
	LogicalOperatorToken,
    FunctionToken,
    CommaToken
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