#include "asts/IfExpr.h"

#include "llvm/IR/BasicBlock.h"

using namespace llvm;


IfExpr::IfExpr(BaseExpr* _cond, BlockNode* _ifBody, BlockNode* _thenBody): cond(_cond), ifBody(_ifBody), thenBody(_thenBody) {
    
}

IfExpr::~IfExpr(){
    delete cond;
    delete ifBody;
    delete thenBody;
}

Value* IfExpr::codegen(Compiler& c) {
    llvm::BasicBlock* thenBlock = BasicBlock::Create(*c.TheContext, "then", c.currentFunction);
    llvm::BasicBlock* elseBlock = BasicBlock::Create(*c.TheContext, "else");
    llvm::BasicBlock* mergeBlock = BasicBlock::Create(*c.TheContext, "ifcont");
    c.Builder->CreateCondBr(cond->codegen(c), thenBlock, elseBlock);
    c.Builder->SetInsertPoint(thenBlock);
    ifBody->codegen(c);
    thenBlock = c.Builder->GetInsertBlock();
    c.Builder->CreateBr(mergeBlock);
    c.currentFunction->insert(c.currentFunction->end(), elseBlock);
    c.Builder->SetInsertPoint(elseBlock);
    if (thenBody) thenBody->codegen(c);
    c.Builder->CreateBr(mergeBlock);

    c.currentFunction->insert(c.currentFunction->end(), mergeBlock);
    c.Builder->SetInsertPoint(mergeBlock);
    return nullptr;
}