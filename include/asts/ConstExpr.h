#ifndef __ConstExpr_HEADER__
#define __ConstExpr_HEADER__

#include "asts/Expression.h"
#include <llvm/IR/Value.h>

using namespace llvm;

class IntegerExpr : public Expression {
    int val;
public:
    IntegerExpr(int);
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

class DoubleExpr : public Expression {
    double val;
public:
    DoubleExpr(double);
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif