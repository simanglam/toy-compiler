#include "asts/PrototypeAST.h"
#include "asts/Expression.h"

#include "Compiler.h"
#include "Analyser.h"

PrototypeAST::PrototypeAST(string _name, vector<DeclareNode*> _args, TypeInfo* _returnType): name(_name), args(_args), returnType(_returnType) {}

PrototypeAST::~PrototypeAST() {
    for (DeclareNode* node : args)
        delete node;
}

string PrototypeAST::getName() {
    return name;
}

vector<DeclareNode*>& PrototypeAST::getArgs() {
    return args;
}

void PrototypeAST::codegen(Compiler& c) {
    vector<llvm::Type*> Args;

    for (DeclareNode* node : args) {
        Args.push_back(node->getType()->toLLVMType(c.TheContext));
    }


    FunctionType* FT = FunctionType::get(returnType->toLLVMType(c.TheContext), Args, false);
    Function* F = Function::Create(FT, GlobalValue::ExternalLinkage, llvm::Twine(name), c.TheModule);
}

bool PrototypeAST::eval(Analyser& a) {
    if (a.functionTable.count(name)){
        cerr << "You can't redifined the function: " << name << endl;
        return false;
    }
    EVALTYPE evalType = returnType->getEvalType();
    FunctionInfo f;
    for (DeclareNode* arg : args){
        f.argType.push_back(arg->getType()->getEvalType());
    }
    f.returnType = evalType;
    a.functionTable[name] = f;
    return true;
}