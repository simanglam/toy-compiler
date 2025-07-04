#include "asts/DeclearNode.h"

using namespace llvm;

DeclearNode::DeclearNode(string _id, TOKENS _type, BaseExpr* _initVal): id(_id), type(_type), initVal(_initVal) {}

DeclearNode::~DeclearNode() {
    delete initVal;
}

TOKENS DeclearNode::getType() {
    return type;
}

string& DeclearNode::getName() {
    return id;
}


Value* DeclearNode::codegen(Compiler& c) {
    if (c.localVariables[id]) {
        cerr << "You can't redefine the variable" << endl;
        return nullptr;
    }

    llvm::Type* t = nullptr;
    switch (type){
        case TOK_TYPE_DOUBLE:
            t = llvm::Type::getDoubleTy(*c.TheContext);
            break;
        case TOK_TYPE_INT:
            t = llvm::Type::getInt32Ty(*c.TheContext);
            break;
        default:
            break;
    }

    c.localVariables[id] = c.allocateVar(t, id);
    llvm::Value* initV = initVal ? initVal->codegen(c) : Constant::getNullValue(t);
    return c.Builder->CreateStore(initV, c.localVariables[id]);
}