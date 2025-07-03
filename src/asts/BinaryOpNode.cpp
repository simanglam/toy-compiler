#include <iostream>
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

Value* BinaryOpNode::codegen() {
    return nullptr;
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