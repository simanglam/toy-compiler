#ifndef __FunctionAST_HEADER__
#define __FunctionAST_HEADER__
class FunctionAST;

#include "asts/BaseExpr.h"
#include "asts/BlockNode.h"
#include "asts/PrototypeAST.h"
#include "Compiler.h"

#include <llvm/IR/Function.h>

using namespace llvm;


class FunctionAST: public BaseExpr {
    PrototypeAST* proto;
    BlockNode* body;
public:
    FunctionAST(PrototypeAST*, BlockNode*);
    ~FunctionAST();
    Function* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif