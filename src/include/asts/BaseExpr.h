#ifndef __BaseExpr_HEADER__
#define __BaseExpr_HEADER__
#include <string>
#include <llvm/IR/Value.h>
using namespace llvm;
using namespace std;

class Compiler;

class BaseExpr{
public:
    BaseExpr();
    virtual ~BaseExpr();
    virtual Value* codegen(Compiler&) = 0;
};


#include "Compiler.h"

#endif