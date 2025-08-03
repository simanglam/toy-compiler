#include "asts/ReturnStatement.h"
#include "Analyser.h"

ReturnStatement::ReturnStatement(Expression* _exp): expr(_exp) {}

ReturnStatement::~ReturnStatement() {
    delete expr;
}

void ReturnStatement::codegen(Compiler& c) {
    expr ? c.Builder->CreateRet(expr->codegenExpr(c)) : c.Builder->CreateRetVoid();
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