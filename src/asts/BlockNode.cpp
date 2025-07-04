#include "asts/BlockNode.h"

BlockNode::BlockNode(vector<BaseExpr*> _expressions): expressions(_expressions){
    
}

BlockNode::~BlockNode(){
    for (BaseExpr* e : expressions){
        delete e;
    }
}

Value* BlockNode::codegen(Compiler& c) {
    for (BaseExpr* e : expressions){
        e->codegen(c);
    }
}
