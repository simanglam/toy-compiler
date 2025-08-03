#include "asts/Expression.h"

Expression::Expression() {}
Expression::~Expression() {}

void Expression::codegen(Compiler& c) {
    this->codegenExpr(c);
}