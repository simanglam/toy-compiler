#include "asts/GlobalDeclareNode.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"

#include "Compiler.h"
#include "Analyser.h"

using namespace llvm;

GlobalDeclareNode::GlobalDeclareNode(string _id, TOKENS _type, int _iVal, double _dVal): id(_id), type(_type), iVal(_iVal), dVal(_dVal) {
    
}

GlobalDeclareNode::~GlobalDeclareNode() {
    // delete ;
}

void GlobalDeclareNode::codegen(Compiler& c) {
    llvm::Type* type;
    llvm::Constant* val;
    
    switch (this->type) {
        case TOK_TYPE_INT:
            type = llvm::Type::getInt32Ty(*c.TheContext);
            val = llvm::ConstantInt::get(type, iVal, true);
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
        false,
        llvm::GlobalValue::ExternalLinkage,
        val,
        llvm::Twine(id.c_str())
    );
    c.globalVar[id] = gVar;
}

bool GlobalDeclareNode::eval(Analyser& a) {
    EVALTYPE evalType = (type == TOK_TYPE_INT) ? INTEGER : FLOAT;
    if (a.globalSymbolTable[id]) {
        cerr << "You can't redefined variable: " << id << endl;
        return false;
    }
    a.globalSymbolTable[id] = evalType;
    return true;
}