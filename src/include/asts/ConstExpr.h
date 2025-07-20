#ifndef __ConstExpr_HEADER__
#define __ConstExpr_HEADER__

#include "asts/BaseExpr.h"
#include <llvm/IR/Value.h>

using namespace llvm;

class IntegerExpr : public BaseExpr {
    int val;
public:
    IntegerExpr(int);
    Value* codegen(Compiler&) override;
};

class DoubleExpr : public BaseExpr {
    double val;
public:
    DoubleExpr(double);
    Value* codegen(Compiler&) override;
};

#endif