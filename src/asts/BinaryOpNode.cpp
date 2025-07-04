#include <iostream>

#include "Compiler.h"
#include "asts/BinaryOpNode.h"

BinaryOpNode::BinaryOpNode(BaseExpr* _lhs, char _op, BaseExpr* _rhs): lhs(_lhs), op(_op), rhs(_rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs; delete rhs;
}


Value* BinaryOpNode::codegen(Compiler& c) {
    Value* lhsCode = lhs->codegen(c);
    Value* rhsCode = rhs->codegen(c);
    if (!lhsCode || !rhsCode)
        return nullptr;
    switch (op){
        case '+':
            return c.Builder->CreateAdd(lhsCode, rhsCode);
        case '-':
            return c.Builder->CreateSub(lhsCode, rhsCode);
        case '*':
            return c.Builder->CreateMul(lhsCode, rhsCode);
        case '/':
            return c.Builder->CreateSDiv(lhsCode, rhsCode);
    }
    
}
