#include <iostream>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Type.h>

#include "Compiler.h"
#include"asts/ConstExpr.h"

using namespace llvm;

DoubleExpr::DoubleExpr(double _val): val(_val) {}


Value* DoubleExpr::codegenExpr(Compiler& c) {
    return ConstantFP::get(Type::getDoubleTy(*c.TheContext), val);
}

bool DoubleExpr::eval(Analyser& c) {
    evalType = FLOAT;
    return true;
}