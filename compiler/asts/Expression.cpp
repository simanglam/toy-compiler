#include "asts/Expression.h"

Expression::Expression() {}
Expression::~Expression() {}

void Expression::codegen(Compiler& c) {
    this->codegenExpr(c);
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