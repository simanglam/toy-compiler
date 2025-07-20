#include "asts/UnaryExpr.h"

UnaryExpr::UnaryExpr(BaseExpr* _target, TOKENS _op): target(_target), op(_op) {}

UnaryExpr::~UnaryExpr() {
    delete target;
}

Value* UnaryExpr::codegen(Compiler& c) {
    return c.Builder->CreateNeg(target->codegen(c), "negTemp");
}
