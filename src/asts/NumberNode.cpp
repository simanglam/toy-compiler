#include <iostream>

#include"asts/NumberNode.h"


NumberNode::NumberNode(int _val): val(_val) {}

void NumberNode::print() {
    cout << val << " ";
}

Value* NumberNode::codegen() {
    return nullptr;
}

int NumberNode::result() {
    return val;
}