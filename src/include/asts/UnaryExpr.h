#ifndef __UnaryExpr_HEADER__
#define __UnaryExpr_HEADER__

#include "asts/BaseExpr.h"

class UnaryExpr : public BaseExpr {
    BaseExpr* target;
    TOKENS op;
public:
    UnaryExpr(BaseExpr*, TOKENS);
    ~UnaryExpr();
    Value* codegen(Compiler&) override;
};

#endif