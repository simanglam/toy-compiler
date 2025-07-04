#ifndef __NumberNode_HEADER__
#define __NumberNode_HEADER__

#include "asts/BaseExpr.h"
#include <llvm/IR/Value.h>

using namespace llvm;

class NumberNode : public BaseExpr {
    int val;
public:
    NumberNode(int);
    Value* codegen(Compiler&) override;
};

#endif