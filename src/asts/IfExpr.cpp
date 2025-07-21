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
    BasicBlock* thenBlock = BasicBlock::Create(*c.TheContext, "then", c.currentFunction);
    BasicBlock* elseBlock = BasicBlock::Create(*c.TheContext, "else");
    BasicBlock* mergeBlock = BasicBlock::Create(*c.TheContext, "ifcont");
    Value* v = cond->codegen(c);
    if (!v) return nullptr;
    if (v->getType()->getTypeID() != Type::TypeID::IntegerTyID) {
        v = c.Builder->CreateTrunc(v, Type::getInt8Ty(*c.TheContext), "trunc");
    }

    v = c.Builder->CreateICmpNE(v, ConstantInt::get(v->getType(), 0, true), "ifcond");
    c.Builder->CreateCondBr(v, thenBlock, elseBlock);
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

bool IfExpr::eval(Analyser& a) {
    bool result = true;
    if (thenBody)
        result && thenBody->eval(a);
    return result && cond->eval(a) && ifBody->eval(a);
}