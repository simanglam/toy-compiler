#include <iostream>

#include "asts/VariableNode.h"
#include "Compiler.h"
#include "Analyser.h"

VariableNode::VariableNode(string _name): name(_name) {};

string& VariableNode::getName() {
    return name;
}

Value* VariableNode::codegenExpr(Compiler& c) {
    Value* var = c.localVariables[name];
    if (var) {
        return c.Builder->CreateLoad(c.localVariables[name]->getAllocatedType(), var, name.c_str());
    }
    
    var = c.globalVar[name];

    if (var) {
        return c.Builder->CreateLoad(c.globalVar[name]->getValueType(), var, name.c_str());
    }


    cerr << "Unknown Variable: " << name << endl;
    return nullptr;
};

Value* VariableNode::codegenAddr(Compiler& c) {
    Value* var = c.localVariables[name];
    if (var) return var;
    
    var = c.globalVar[name];
    if (var) return var;

    cerr << "Unknown Variable: " << name << endl;
    return nullptr;
};

bool VariableNode::eval(Analyser& a) {
    if ((!a.localSymbolTable.count(name) && !a.globalSymbolTable.count(name))){
        cerr << "Unknown variable: " << name << endl;
        return false;
    }
    evalType = a.localSymbolTable.count(name) ? a.localSymbolTable[name] : a.globalSymbolTable[name];
    return true;
}

bool VariableNode::isLvalue() {
    return true;
}

bool VariableNode::isConstantExpr() {
    return false;
}

double VariableNode::getValue() {
    return 0;
}
