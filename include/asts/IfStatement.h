#ifndef __IfExpr_HEADER__
#define __IfExpr_HEADER__
class IfExpr;

#include "asts/Expression.h"
#include "asts/Statement.h"
#include "asts/BlockNode.h"

class IfExpr : public Statement {
    Expression* cond;
    BlockNode* ifBody;
    BlockNode* thenBody;
public:
    IfExpr(Expression*, BlockNode*, BlockNode*);
    ~IfExpr();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif