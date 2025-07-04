#include <iostream>

#include "asts/VariableNode.h"

VariableNode::VariableNode(string _name): name(_name) {};

Value* VariableNode::codegen(Compiler& c) {
    return nullptr;
};