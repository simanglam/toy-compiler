#include "asts/DeclareNode.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include "Compiler.h"
#include "Analyser.h"

using namespace llvm;

DeclareNode::DeclareNode(TypeInfo* _type, string _id, DeclareNodeStrategy* _strategy, Expression* _initVal, Expression* _size, vector<Expression*>& _values): id(_id), type(_type), initVal(_initVal), size(_size), values(_values), strategy(_strategy) {}

DeclareNode::~DeclareNode() {
    delete initVal;
}

TypeInfo* DeclareNode::getType() {
    return type;
}

string& DeclareNode::getName() {
    return id;
}

Expression* DeclareNode::getInitVal() {
    return initVal;
}

Expression* DeclareNode::getSize() {
    return size;
}

vector<Expression*>& DeclareNode::getValues() {
    return values;
}

void DeclareNode::codegen(Compiler& c) {
    strategy->codegen(c, this);
}

bool DeclareNode::eval(Analyser& a) {
    bool result = true;
    if (initVal){
        result = initVal->eval(a);
    }

    EVALTYPE evalType = type->getEvalType();
    if (id.length() != 0 && a.localSymbolTable[id]) {
        cerr << "Redefined id: " << id << endl;
        return false;
    }
    if (id.length() != 0) {
        a.localSymbolTable[id] = evalType;
    }
    for (Expression* e : values) {
        result = e->eval(a) && result;
    }

    return true && result;
}