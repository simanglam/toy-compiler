#include "asts/DeclareNode.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include "Compiler.h"
#include "Analyser.h"

using namespace llvm;

DeclareNode::DeclareNode(TypeInfo* _type, string _id, Expression* _initVal, Expression* _size, vector<Expression*>& _values): id(_id), type(_type), initVal(_initVal), size(_size), values(_values) {}

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

vector<Expression*>& DeclareNode::getValues() {
    return values;
}

void DeclareNode::codegen(Compiler& c) {
    c.localVariables[id] = c.allocateVar(type->getType(c.TheContext), id);
    if (!size){
        llvm::Value* initV = 
            initVal 
                ? initVal->codegenExpr(c) 
                : Constant::getNullValue(type->getType(c.TheContext));

        c.Builder->CreateStore(initV, c.localVariables[id]);
    }
    else {
        string old_name = id;
        AllocaInst* arrayAlloc = c.allocateVar(type->getType(c.TheContext), old_name, size->codegenExpr(c));
        c.localVariables[old_name] = arrayAlloc;
        c.Builder->CreateMemSet(
            c.Builder->CreateGEP(arrayAlloc->getType(), 
            c.Builder->CreateLoad(arrayAlloc->getAllocatedType(), arrayAlloc), 
            {c.Builder->getInt32(0)}), 
            c.Builder->getInt8(0), 
            size->codegenExpr(c), 
            arrayAlloc->getAlign()
        );

        Value* arrayBody = c.Builder->CreateLoad(arrayAlloc->getAllocatedType(), arrayAlloc);
    
        int idx = 0;
        for (Expression* e : values) {
            c.Builder->CreateStore(
                e->codegenExpr(c),
                c.Builder->CreateGEP(arrayAlloc->getType(),
                    arrayBody,
                    {c.Builder->getInt32(idx++)}
                )
            );
        }
    }
    
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