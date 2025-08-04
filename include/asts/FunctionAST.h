#ifndef __FunctionAST_HEADER__
#define __FunctionAST_HEADER__
class FunctionAST;

#include "asts/Expression.h"
#include "asts/BlockNode.h"
#include "asts/PrototypeAST.h"
#include "Compiler.h"

#include <llvm/IR/Function.h>

using namespace llvm;


class FunctionAST: public Statement {
    PrototypeAST* proto;
    BlockNode* body;
public:
    FunctionAST(PrototypeAST*, BlockNode*);
    ~FunctionAST();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif