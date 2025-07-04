#include "asts/GlobalDeclearNode.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"

using namespace llvm;

GlobalDeclearNode::GlobalDeclearNode(string _id, TOKENS _type, int _iVal, double _dVal): id(_id), type(_type), iVal(_iVal), dVal(_dVal) {
    
}

GlobalDeclearNode::~GlobalDeclearNode() {
    // delete ;
}

Value* GlobalDeclearNode::codegen(Compiler& c) {
    llvm::Type* type;
    llvm::Constant* val;
    
    switch (this->type) {
        case TOK_TYPE_INT:
            type = llvm::Type::getInt32Ty(*c.TheContext);
            val = llvm::ConstantInt::get(type, iVal);
            break;
        case TOK_TYPE_DOUBLE:
            type = llvm::Type::getDoubleTy(*c.TheContext);
            val = llvm::ConstantFP::get(type, dVal);
            break;
        default: break;
    }
    llvm::GlobalVariable *gVar = new llvm::GlobalVariable(
        *c.TheModule,
        type,
        false,                              // isConstant
        llvm::GlobalValue::ExternalLinkage,
        val,
        llvm::Twine(id.c_str())
    );
    return val;
}