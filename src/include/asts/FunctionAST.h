#ifndef __FunctionAST_HEADER__
#define __FunctionAST_HEADER__
class FunctionAST;

#include "asts/BaseExpr.h"
#include "asts/BlockNode.h"
#include "Compiler.h"

#include <llvm/IR/Function.h>

using namespace llvm;


class FunctionAST: BaseExpr {
    BlockNode* body;
public:
    FunctionAST();
    Function* codegen(Compiler&);
};

#endif