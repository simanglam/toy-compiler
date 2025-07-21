#include "asts/FunctionAST.h"
#include "asts/ConstExpr.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>

using namespace llvm;

FunctionAST::FunctionAST(PrototypeAST* _proto, BlockNode* _body): proto(_proto), body(_body) {

}

FunctionAST::~FunctionAST() {
    delete proto; delete body;
}

Function* FunctionAST::codegen(Compiler& c) {
    Function* F = c.TheModule->getFunction(proto->getName());

    if (!F) F = proto->codegen(c);
    if (!F) return nullptr;
    if (!F->empty()) return nullptr;

    c.currentFunction = F;
    BasicBlock* BB = BasicBlock::Create(*c.TheContext, "entry", F);
    c.Builder->SetInsertPoint(BB);
    
    vector<DeclareNode*>& argNames = proto->getArgs();

    unsigned idx = 0;

    for (auto& arg : F->args()) {
        std::string& argName = argNames[idx++]->getName();
        arg.setName(argName);
    }

    for (auto& Arg : F->args()) {
        string name = string(Arg.getName());
        AllocaInst *Alloca = c.allocateVar(Arg.getType(), name);
        c.Builder->CreateStore(&Arg, Alloca);
        c.localVariables[name] = Alloca;
    }
    body->codegen(c);

    c.currentFunction = nullptr;
    c.localVariables.clear();

    return F;
}

bool FunctionAST::eval(Analyser& a) {
    bool result = true;
    if (a.globalSymbolTable[proto->getName()] == UNDIFINED){
        result = result && proto->eval(a);
    }
    a.returnType = a.globalSymbolTable[proto->getName()];

    for (auto arg : proto->getArgs()) {
        arg->eval(a);
    }

    result = result && body->eval(a);
    a.localSymbolTable.clear();
    a.returnType = UNDIFINED;
    return result;
}