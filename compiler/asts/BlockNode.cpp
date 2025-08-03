#include "asts/BlockNode.h"

BlockNode::BlockNode(vector<Expression*> _expressions): expressions(_expressions){
    
}

BlockNode::~BlockNode(){
    for (Expression* e : expressions){
        delete e;
    }
}

Value* BlockNode::codegen(Compiler& c) {
    for (Expression* e : expressions){
        e->codegen(c);
    }
}

bool BlockNode::eval(Analyser& c) {
    bool result = true;
    for (Expression* e : expressions){
        result = e->eval(c) && result;
    }
    return result;
}
