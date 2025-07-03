#ifndef __NumberNode_HEADER__
#define __NumberNode_HEADER__

#include "asts/BaseAST.h"
#include <llvm/IR/Value.h>

using namespace llvm;

class NumberNode : public BaseAST {
    int val;
public:
    NumberNode(int);
    Value* codegen(Compiler&) override;
    void print() override;
    int result() override;
};

#endif