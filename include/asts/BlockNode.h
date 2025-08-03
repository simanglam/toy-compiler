#ifndef __BlockNode_HEADER__
#define __BlockNode_HEADER__
class BlockNode;

#include <vector>
#include "asts/Statement.h"
#include "asts/Expression.h"

class BlockNode : public Statement {
    std::vector<Expression*> expressions;
public:
    BlockNode(std::vector<Expression*>);
    ~BlockNode();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif