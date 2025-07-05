#include "asts/ReturnStatement.h"

ReturnStatement::ReturnStatement(BaseExpr* _exp): expr(_exp) {}

ReturnStatement::~ReturnStatement() {
    delete expr;
}

Value* ReturnStatement::codegen(Compiler& c) {
    return expr ? c.Builder->CreateRet(expr->codegen(c)) : c.Builder->CreateRetVoid();
}