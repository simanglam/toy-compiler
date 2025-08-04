#ifndef __BinaryOpNode_HEADER__
#define __BinaryOpNode_HEADER__

#include "asts/Expression.h"

class BinaryOpNode : public Expression {
    Expression* lhs;
    TOKENS op;
    Expression* rhs;
public:
    BinaryOpNode(Expression*, TOKENS, Expression*);
    ~BinaryOpNode();
    Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
    bool isLvalue() override;
    Value* codegenAddr(Compiler&) override;
};

#endif

