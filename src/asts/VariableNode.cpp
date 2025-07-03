#include <iostream>

#include "asts/VariableNode.h"

VariableNode::VariableNode(string _name): name(_name) {};

Value* VariableNode::codegen() {
    return nullptr;
};

void VariableNode::print() {
    std::cout << name << " ";
};

int VariableNode::result() {
    return 0;
}