#include "asts/ReturnStatement.h"

ReturnStatement::ReturnStatement(BaseExpr* _exp): expr(_exp) {}

ReturnStatement::~ReturnStatement() {
    delete expr;
}

Value* ReturnStatement::codegen(Compiler& c) {
    return expr ? c.Builder->CreateRet(expr->codegen(c)) : c.Builder->CreateRetVoid();
}

bool ReturnStatement::eval(Analyser& a) {
    if (!expr) {
        return true;
    }
    expr->eval(a);
    bool result = true && (expr->evalType == a.returnType);
    if (!result) {
        cerr << "Return type error" << endl;
    }
    return result;
}