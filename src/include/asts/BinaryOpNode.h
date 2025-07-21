#ifndef __BinaryOpNode_HEADER__
#define __BinaryOpNode_HEADER__

#include "asts/BaseExpr.h"

class BinaryOpNode : public BaseExpr {
    BaseExpr* lhs;
    TOKENS op;
    BaseExpr* rhs;
public:
    BinaryOpNode(BaseExpr*, TOKENS, BaseExpr*);
    ~BinaryOpNode();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif

