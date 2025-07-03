#include <iostream>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Type.h>

#include "Compiler.h"
#include"asts/NumberNode.h"

using namespace llvm;



NumberNode::NumberNode(int _val): val(_val) {}

void NumberNode::print() {
    cout << val << " ";
}

Value* NumberNode::codegen(Compiler& c) {
    return ConstantInt::get(Type::getInt32Ty(*c.TheContext), val, true);
}

int NumberNode::result() {
    return val;
}