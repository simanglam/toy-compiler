#ifndef __Analyser_Header__
#define __Analyser_Header__
#include "asts/BaseExpr.h"
#include <map>
#include <vector>

using namespace std;

class FunctionInfo {
public:
    vector<EVALTYPE> argType;
    EVALTYPE returnType;
};

class Analyser {
public:
    map<string, EVALTYPE> globalSymbolTable;
    map<string, EVALTYPE> localSymbolTable;
    map<string, FunctionInfo> functionTable;
    EVALTYPE returnType;
    Analyser();
    ~Analyser();
    bool eval(BaseExpr*);
};

#endif