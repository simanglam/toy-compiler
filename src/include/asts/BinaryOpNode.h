#ifndef __BinaryOpNode_HEADER__
#define __BinaryOpNode_HEADER__

#include "asts/BaseAST.h"

class BinaryOpNode : public BaseAST {
    BaseAST* lhs;
    char op;
    BaseAST* rhs;
public:
    BinaryOpNode(BaseAST*, char, BaseAST*);
    ~BinaryOpNode();
    void print() override;
    Value* codegen(Compiler&) override;
    int result() override;
};

#endif