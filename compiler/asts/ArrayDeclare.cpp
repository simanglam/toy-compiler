#include "asts/ArrayDeclare.h"

#include "Compiler.h"
#include "Analyser.h"

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instructions.h>


using namespace llvm;

ArrayDeclare::ArrayDeclare(TOKENS _type, vector<Expression*>& _values, Expression* _size, string& _name): type(_type), values(_values), size(_size), name(_name) {
    
}

ArrayDeclare::~ArrayDeclare() {
    for (Expression* e : values)
        delete e;
    delete size;
}

void ArrayDeclare::codegen(Compiler& c) {
    Type* type = nullptr;
    switch (this->type){
    case TOK_TYPE_INT:
        type = Type::getInt32Ty(*c.TheContext);
        break;
    case TOK_TYPE_DOUBLE:
        type = Type::getDoubleTy(*c.TheContext);
        break;
    default:
        break;
    }
    string old_name = name;
    AllocaInst* arrayPointer = c.allocateVar(type->getPointerTo(), (name.append("body")));
    c.localVariables[old_name] = arrayPointer;
    AllocaInst* arrayAlloc = c.allocateArray(type, size->codegenExpr(c), old_name);
    c.Builder->CreateStore(arrayAlloc, arrayPointer);
    c.Builder->CreateMemSet(c.Builder->CreateGEP(arrayPointer->getType(), c.Builder->CreateLoad(arrayPointer->getAllocatedType(), arrayPointer), {c.Builder->getInt32(0)}), c.Builder->getInt8(0), size->codegenExpr(c), arrayAlloc->getAlign());
    
    int idx = 0;
    for (Expression* e : values) {
        c.Builder->CreateStore(e->codegenExpr(c), c.Builder->CreateGEP(arrayPointer->getType(), c.Builder->CreateLoad(arrayPointer->getAllocatedType(), arrayPointer), {c.Builder->getInt32(idx++)}));
    }
}

bool ArrayDeclare::eval(Analyser& a) {
    a.localSymbolTable[name] = INT_POINTER;
    return true;
}