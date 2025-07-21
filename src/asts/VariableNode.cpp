#include <iostream>

#include "asts/VariableNode.h"

VariableNode::VariableNode(string _name): name(_name) {};

string& VariableNode::getName() {
    return name;
}

Value* VariableNode::codegen(Compiler& c) {
    Value* var = c.localVariables[name];
    if (var) {
        return c.Builder->CreateLoad(c.localVariables[name]->getAllocatedType(), var, name.c_str());
    }
    
    var = c.globalVar[name];

    if (var) {
        return c.Builder->CreateLoad(c.globalVar[name]->getValueType(), var, name.c_str());
    }

    if (!var) {
        cerr << "Unknown Variable: " << name << endl;
        return nullptr;
    }
    return c.Builder->CreateLoad(c.localVariables[name]->getAllocatedType(), var, name.c_str());
    
};

bool VariableNode::eval(Analyser& a) {
    if (!(a.localSymbolTable[name] || a.globalSymbolTable[name])){
        cerr << "Unknown variable: " << name << endl;
        return false;
    }
    evalType = (a.localSymbolTable[name]) ? a.localSymbolTable[name] : a.globalSymbolTable[name];
    return true;
}