#ifndef __BlockNode_HEADER__
#define __BlockNode_HEADER__
class BlockNode;

#include <vector>

#include "asts/Expression.h"

class BlockNode : public Expression {
    vector<Expression*> expressions;
public:
    BlockNode(vector<Expression*>);
    ~BlockNode();
    llvm::Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif