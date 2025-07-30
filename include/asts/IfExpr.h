#ifndef __IfExpr_HEADER__
#define __IfExpr_HEADER__
class IfExpr;

#include "asts/BaseExpr.h"

class IfExpr : public BaseExpr {
    BaseExpr* cond;
    BlockNode* ifBody;
    BlockNode* thenBody;
public:
    IfExpr(BaseExpr*, BlockNode*, BlockNode*);
    ~IfExpr();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif