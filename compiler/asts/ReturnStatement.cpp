#include "Analyser.h"
#include "asts/CastNode.h"
#include "asts/ReturnStatement.h"

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
    bool result =  expr->eval(a) && true;

    if (expr->evalType != a.returnType) {
        expr = new CastNode(expr, a.returnType, CastNodeStrategy::getCastStrategy(expr->evalType));
        result = expr->eval(a) && result;
    }

    if (!result) {
        cerr << "Return type error" << endl;
    }
    
    return result;
}