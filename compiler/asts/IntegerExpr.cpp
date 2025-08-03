#include <iostream>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Type.h>

#include "Compiler.h"
#include"asts/ConstExpr.h"

using namespace llvm;

IntegerExpr::IntegerExpr(int _val): val(_val) {}


Value* IntegerExpr::codegenExpr(Compiler& c) {
    return ConstantInt::get(Type::getInt32Ty(*c.TheContext), val, true);
}

bool IntegerExpr::eval(Analyser& a) {
    evalType = EVALTYPE::INTEGER;
    return true;
}