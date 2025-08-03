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
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif

