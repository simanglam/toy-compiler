#include <iostream>

#include "asts/VariableNode.h"

VariableNode::VariableNode(string _name): name(_name) {};

Value* VariableNode::codegen(Compiler& c) {
    if (!c.localVariables[name]) {
        cerr << "Unknown Variable: " << name << endl;
        return nullptr;
    }
    return c.Builder->CreateLoad(c.localVariables[name]->getAllocatedType(), c.localVariables[name], name.c_str());
    
};