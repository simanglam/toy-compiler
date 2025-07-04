#ifndef __BinaryOpNode_HEADER__
#define __BinaryOpNode_HEADER__

#include "asts/BaseExpr.h"

class BinaryOpNode : public BaseExpr {
    BaseExpr* lhs;
    char op;
    BaseExpr* rhs;
public:
    BinaryOpNode(BaseExpr*, char, BaseExpr*);
    ~BinaryOpNode();
    Value* codegen(Compiler&) override;
};

#endif

