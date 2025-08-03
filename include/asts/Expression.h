#ifndef __Expression_HEADER__
#define __Expression_HEADER__
#include <string>
#include <llvm/IR/Value.h>
#include "EvalType.h"
using namespace llvm;
using namespace std;

class Compiler;
class Analyser;

class Expression{
public:
    EVALTYPE evalType = UNDIFINED;
    Expression();
    virtual ~Expression();
    virtual Value* codegen(Compiler&) = 0;
    virtual bool eval(Analyser&) = 0;
};


#include "Compiler.h"
#include "Analyser.h"

#endif