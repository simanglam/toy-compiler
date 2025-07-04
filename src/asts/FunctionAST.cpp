#include "asts/FunctionAST.h"
#include "asts/NumberNode.h"
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
    cout << F->empty() << endl;
    if (!F->empty()) return nullptr;

    BasicBlock* BB = BasicBlock::Create(*c.TheContext, "entry", F);
    c.Builder->SetInsertPoint(BB);
    body->codegen(c);
    return F;
}