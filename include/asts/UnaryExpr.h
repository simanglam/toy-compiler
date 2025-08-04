#ifndef __UnaryExpr_HEADER__
#define __UnaryExpr_HEADER__

#include "asts/Expression.h"
#include "Token.h"

class UnaryExpr : public Expression {
    Expression* target;
    TOKENS op;
public:
    UnaryExpr(Expression*, TOKENS);
    ~UnaryExpr();
    llvm::Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif