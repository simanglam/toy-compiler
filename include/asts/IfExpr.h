#ifndef __IfExpr_HEADER__
#define __IfExpr_HEADER__
class IfExpr;

#include "asts/Expression.h"

class IfExpr : public Expression {
    Expression* cond;
    BlockNode* ifBody;
    BlockNode* thenBody;
public:
    IfExpr(Expression*, BlockNode*, BlockNode*);
    ~IfExpr();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif