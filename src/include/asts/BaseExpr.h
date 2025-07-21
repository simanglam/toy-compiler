#ifndef __BaseExpr_HEADER__
#define __BaseExpr_HEADER__
#include <string>
#include <llvm/IR/Value.h>
using namespace llvm;
using namespace std;

class Compiler;
class Analyser;

enum EVALTYPE {
    UNDIFINED, INTEGER, FLOAT, INTVAR, FLOATVAR
};

class BaseExpr{
public:
    EVALTYPE evalType = UNDIFINED;
    BaseExpr();
    virtual ~BaseExpr();
    virtual Value* codegen(Compiler&) = 0;
    virtual bool eval(Analyser&) = 0;
};


#include "Compiler.h"
#include "Analyser.h"

#endif