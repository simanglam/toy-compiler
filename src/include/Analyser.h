#ifndef __Analyser_Header__
#define __Analyser_Header__
#include "asts/BaseExpr.h"
#include "map"
using namespace std;

class Analyser {
public:
    map<string, bool> symbolTable;
    EVALTYPE returnType;
    Analyser();
    ~Analyser();
    bool eval(BaseExpr*);
};

#endif