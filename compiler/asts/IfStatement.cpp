#include <llvm/IR/BasicBlock.h>

#include "Compiler.h"
#include "Analyser.h"

#include "asts/CastNode.h"
#include "asts/IfStatement.h"

using namespace llvm;


IfStatement::IfStatement(Expression* _cond, BlockNode* _ifBody, BlockNode* _thenBody): cond(_cond), ifBody(_ifBody), thenBody(_thenBody) {
    
}

IfStatement::~IfStatement(){
    delete cond;
    delete ifBody;
    delete thenBody;
}

void IfStatement::codegen(Compiler& c) {
    BasicBlock* thenBlock = BasicBlock::Create(*c.TheContext, "then", c.currentFunction);
    BasicBlock* elseBlock = BasicBlock::Create(*c.TheContext, "else");
    BasicBlock* mergeBlock = BasicBlock::Create(*c.TheContext, "ifcont");
    Value* v = cond->codegenExpr(c);

    if (!v) return ;

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

bool IfStatement::eval(Analyser& a) {
    bool result = true;
    result = cond->eval(a) && result;
    if (cond->evalType != BOOL) {
        cond = new CastNode(cond, BOOL, CastNodeStrategy::getCastStrategy(cond->evalType));
    }
        
    result = ifBody->eval(a) && result;
    
    if (thenBody)
        result = thenBody->eval(a) && result;
    return result;
}