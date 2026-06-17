#ifndef VARIABLE_H
#define VARIABLE_H

enum dataType {
    NullType,
    IntegerType,
    StringType,
};

struct Value {
    enum dataType type;
    int* valuePtr;
};

struct Values {
    struct Value* values;
    int count;
};

struct Variable {
    char* name;
    struct Value value;
};

struct Variables {
    struct Variable* variables;
    int variableCount;
};

#endif