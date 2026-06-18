#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/variable.h"
#include "../parser/parserHeaders/functionCaller.h"



// todo make output id a parameter
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