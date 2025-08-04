#ifndef __BlockNode_HEADER__
#define __BlockNode_HEADER__

#include <vector>
#include "asts/Statement.h"
#include "asts/ASTNode.h"

class BlockNode : public Statement {
    std::vector<ASTNode*> expressions;
public:
    BlockNode(std::vector<ASTNode*>);
    ~BlockNode();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif