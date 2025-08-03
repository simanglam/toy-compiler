#include "asts/DeclareNode.h"

using namespace llvm;

DeclareNode::DeclareNode(string _id, TOKENS _type, Expression* _initVal): id(_id), type(_type), initVal(_initVal) {}

DeclareNode::~DeclareNode() {
    delete initVal;
}

TOKENS DeclareNode::getType() {
    return type;
}

string& DeclareNode::getName() {
    return id;
}

Value* DeclareNode::codegen(Compiler& c) {
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

bool DeclareNode::eval(Analyser& c) {
    bool result = true;
    if (initVal){
        result = initVal->eval(c);
    }

    evalType = (type == TOK_TYPE_INT) ? INTEGER : FLOAT;
    if (id.length() != 0 && c.localSymbolTable[id]) {
        cerr << "Redefined id: " << id << endl;
        return false;
    }
    if (id.length() != 0) {
        c.localSymbolTable[id] = evalType;
    }
    return true && result;
}