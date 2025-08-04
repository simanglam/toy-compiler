#ifndef __IfStatement_HEADER__
#define __IfStatement_HEADER__


#include "asts/Expression.h"
#include "asts/Statement.h"
#include "asts/BlockNode.h"

class IfStatement : public Statement {
    Expression* cond;
    BlockNode* ifBody;
    BlockNode* thenBody;
public:
    IfStatement(Expression*, BlockNode*, BlockNode*);
    ~IfStatement();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif