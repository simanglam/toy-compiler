#include "asts/Expression.h"

Expression::Expression() {}
Expression::~Expression() {}

void Expression::codegen(Compiler& c) {
    this->codegenExpr(c);
}

llvm::Value* Expression::codegenAddr(Compiler& c) {
    return nullptr;
}


bool Expression::isLvalue() {
    return false;
}

bool Expression::isConstantExpr() {
    return false;
}

double Expression::getValue() {
    return 0;
}