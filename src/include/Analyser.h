#ifndef __Analyser_Header__
#define __Analyser_Header__
#include "asts/BaseExpr.h"
#include "map"
using namespace std;

class Analyser {
public:
    map<string, EVALTYPE> globalSymbolTable;
    map<string, EVALTYPE> localSymbolTable;
    EVALTYPE returnType;
    Analyser();
    ~Analyser();
    bool eval(BaseExpr*);
};

#endif