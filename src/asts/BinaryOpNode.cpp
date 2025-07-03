#include <iostream>

#include "Compiler.h"
#include "asts/BinaryOpNode.h"

BinaryOpNode::BinaryOpNode(BaseAST* _lhs, char _op, BaseAST* _rhs): lhs(_lhs), op(_op), rhs(_rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs; delete rhs;
}

void BinaryOpNode::print(){
    lhs->print();
    std::cout << op << " ";
    rhs->print();
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

int BinaryOpNode::result() {
    int lhsResult = lhs->result();
    int rhsResult = rhs->result();
    switch (op){
    case '+':
        return lhsResult + rhsResult;
    case '-':
        return lhsResult - rhsResult;
    case '*':
        return lhsResult * rhsResult;
    case '/':
        return lhsResult / rhsResult;
    }
}