#ifndef __Expression_HEADER__
#define __Expression_HEADER__

#include <string>
#include <llvm/IR/Value.h>
#include "EvalType.h"
#include "asts/ASTNode.h"

class Expression: public ASTNode {
public:
    EVALTYPE evalType = UNDIFINED;
    Expression();
    virtual ~Expression();
    void codegen(Compiler&) override;
    virtual llvm::Value* codegenExpr(Compiler&) = 0;
    virtual llvm::Value* codegenAddr(Compiler&);
    virtual bool isLvalue();
    virtual bool isConstantExpr();
    virtual double getValue();
};

#endif