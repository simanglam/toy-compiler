#ifndef __FunctionCallExpr_HEADER__
#define __FunctionCallExpr_HEADER__

#include "asts/Expression.h"

class FunctionCallExpr : public Expression{
    vector<Expression *> args;
    string name;
public:
    FunctionCallExpr(string&, vector<Expression*>&);
    ~FunctionCallExpr();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif
