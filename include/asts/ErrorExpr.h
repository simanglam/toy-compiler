#ifndef __ErrorExpr_HEADER__
#define __ErrorExpr_HEADER__
#include "asts/Expression.h"

class Compiler;

class ErrorExpr : public Expression{
    string message;
public:
    ErrorExpr(string);
    ~ErrorExpr();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif