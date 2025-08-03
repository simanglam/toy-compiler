#include "asts/UnaryExpr.h"

#include "Compiler.h"
#include "Analyser.h"


UnaryExpr::UnaryExpr(Expression* _target, TOKENS _op): target(_target), op(_op) {}

UnaryExpr::~UnaryExpr() {
    delete target;
}

Value* UnaryExpr::codegenExpr(Compiler& c) {
    Value* v = target->codegenExpr(c);
    if (op == TOK_OP_NOT){
        if (target->evalType == FLOAT)
            v = c.Builder->CreateFCmpONE(v, ConstantFP::get(v->getType(), 0.0), "fcmp");
        c.Builder->CreateIntCast(v, Type::getInt32Ty(*c.TheContext), true, "intCast");
        return c.Builder->CreateNot(v);
        
    }
    else
        return c.Builder->CreateNeg(v, "negTemp");
}

bool UnaryExpr::eval(Analyser& a) {
    bool result = target->eval(a);
    if (op == TOK_OP_NOT)
        evalType = INTEGER;
    else 
        evalType = target->evalType;
    return result;
}