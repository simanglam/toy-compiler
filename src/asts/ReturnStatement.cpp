#include "asts/ReturnStatement.h"

ReturnStatement::ReturnStatement(BaseExpr* _exp): expr(_exp) {}

Value* ReturnStatement::codegen(Compiler& c) {
    return c.Builder->CreateRet(expr->codegen(c));
}