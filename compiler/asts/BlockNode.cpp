#include "asts/BlockNode.h"

using namespace std;

BlockNode::BlockNode(vector<ASTNode*> _expressions): expressions(_expressions){
    
}

BlockNode::~BlockNode(){
    for (ASTNode* e : expressions){
        delete e;
    }
}

void BlockNode::codegen(Compiler& c) {
    for (ASTNode* e : expressions){
        e->codegen(c);
    }
}

bool BlockNode::eval(Analyser& c) {
    bool result = true;
    for (ASTNode* e : expressions){
        result = e->eval(c) && result;
    }
    return result;
}
