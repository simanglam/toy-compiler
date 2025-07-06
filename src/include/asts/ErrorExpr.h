#ifndef __ErrorExpr_HEADER__
#define __ErrorExpr_HEADER__
#include "asts/BaseExpr.h"

class Compiler;

class ErrorExpr : public BaseExpr{
    string message;
public:
    ErrorExpr(string);
    ~ErrorExpr();
    Value* codegen(Compiler&);
};

#endif