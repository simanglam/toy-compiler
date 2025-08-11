#ifndef __BinaryOpStrategy__Header__
#define __BinaryOpStrategy__Header__

#include <llvm/IR/Value.h>

#include "Token.h"
#include "EvalType.h"
#include "asts/Expression.h"


class BinaryOpStrategy {
public:
    BinaryOpStrategy();
    virtual ~BinaryOpStrategy();

    virtual llvm::Value* codegen(llvm::Value*, llvm::Value*, TOKENS, Compiler&) = 0;
    static BinaryOpStrategy& getStrategy(EVALTYPE);
    
};

#endif