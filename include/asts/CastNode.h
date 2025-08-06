#ifndef __CastNode__Header__
#define __CastNode__Header__

#include "asts/Expression.h"

class CastNodeStrategy {
public:
    static CastNodeStrategy& getCastStrategy(EVALTYPE);
    CastNodeStrategy();
    virtual ~CastNodeStrategy();
    virtual llvm::Value* cast(llvm::Value*, EVALTYPE, Compiler&) = 0;
    virtual bool eval(EVALTYPE) = 0;
};

class CastNode : public Expression {
    Expression* expr;
    CastNodeStrategy& castStrategy;
public:

    CastNode(Expression*, EVALTYPE, CastNodeStrategy&);
    ~CastNode();
    bool eval(Analyser&) override;
    llvm::Value* codegenExpr(Compiler&) override;
};

#endif