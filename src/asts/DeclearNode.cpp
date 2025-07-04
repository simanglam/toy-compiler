#include "asts/DeclearNode.h"

DeclearNode::DeclearNode(string _id, TOKENS _type, BaseExpr* _initVal): id(_id), type(_type), initVal(_initVal) {
    
}

TOKENS DeclearNode::getType() {
    return type;
}

string& DeclearNode::getName() {
    return id;
}


Value* DeclearNode::codegen(Compiler& c) {
    return nullptr;
}