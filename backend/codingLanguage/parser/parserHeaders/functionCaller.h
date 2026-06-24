#include "../../headers/variable.h"

#ifndef FUNCTIONCALLER_H
#define FUNCTIONCALLER_H

struct Value returnInt(int i);
struct Value returnFloat(float i);
struct Value returnBool(int i);
struct Value returnString(char* s);
void outputVars(struct Variables variables);
struct Value callFunction(char* functionName, struct Values args);

#endif