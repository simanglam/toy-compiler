#include "asts/BlockNode.h"

using namespace std;

BlockNode::BlockNode(vector<Expression*> _expressions): expressions(_expressions){
    
}

BlockNode::~BlockNode(){
    for (Expression* e : expressions){
        delete e;
    }
}

void BlockNode::codegen(Compiler& c) {
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
