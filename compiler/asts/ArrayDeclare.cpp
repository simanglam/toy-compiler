#include "asts/ArrayDeclare.h"

ArrayDeclare::ArrayDeclare(TOKENS _type, vector<BaseExpr*>& _values, BaseExpr* _size, string& _name): type(_type), values(_values), size(_size), name(_name) {
    
}

ArrayDeclare::~ArrayDeclare() {
    for (BaseExpr* e : values)
        delete e;
    delete size;
}

Value* ArrayDeclare::codegen(Compiler& c) {
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
    AllocaInst* arrayAlloc = c.allocateArray(type, size->codegen(c), old_name);
    c.localVariables[old_name] = arrayPointer;
    c.Builder->CreateStore(arrayAlloc, arrayPointer);
    
    return arrayPointer;
}

bool ArrayDeclare::eval(Analyser& a) {
    a.localSymbolTable[name] = INTEGER;
    return true;
}