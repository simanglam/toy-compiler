#include "asts/IfStatement.h"

#include <llvm/IR/BasicBlock.h>

#include "Compiler.h"
#include "Analyser.h"

using namespace llvm;


IfExpr::IfExpr(Expression* _cond, BlockNode* _ifBody, BlockNode* _thenBody): cond(_cond), ifBody(_ifBody), thenBody(_thenBody) {
    
}

IfExpr::~IfExpr(){
    delete cond;
    delete ifBody;
    delete thenBody;
}

void IfExpr::codegen(Compiler& c) {
    BasicBlock* thenBlock = BasicBlock::Create(*c.TheContext, "then", c.currentFunction);
    BasicBlock* elseBlock = BasicBlock::Create(*c.TheContext, "else");
    BasicBlock* mergeBlock = BasicBlock::Create(*c.TheContext, "ifcont");
    Value* v = cond->codegenExpr(c);
    if (!v) return ;
    if (cond->evalType != INTEGER) {
        v = c.Builder->CreateFCmpONE(v, ConstantFP::get(v->getType(), 0.0), "ifcond");
    }
    else {
        v = c.Builder->CreateICmpNE(v, ConstantInt::get(v->getType(), 0, true), "ifcond");
    }
    c.Builder->CreateCondBr(v, thenBlock, elseBlock);
    c.Builder->SetInsertPoint(thenBlock);
    ifBody->codegen(c);
    thenBlock = c.Builder->GetInsertBlock();
    c.currentFunction->insert(c.currentFunction->end(), elseBlock);
    c.Builder->CreateBr(mergeBlock);
    c.Builder->SetInsertPoint(elseBlock);
    if (thenBody) {
        thenBody->codegen(c);
    }
    c.Builder->CreateBr(mergeBlock);
    c.currentFunction->insert(c.currentFunction->end(), mergeBlock);
    c.Builder->SetInsertPoint(mergeBlock);
    return ;
}

bool IfExpr::eval(Analyser& a) {
    bool result = true;
    result = cond->eval(a) && result;
    result = ifBody->eval(a) && result;
    
    if (thenBody)
        result = thenBody->eval(a) && result;
    return result;
}