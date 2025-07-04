#ifndef __BlockNode_HEADER__
#define __BlockNode_HEADER__
class BlockNode;

#include <vector>

#include "asts/BaseExpr.h"

class BlockNode : public BaseExpr {
    vector<BaseExpr*> expressions;
public:
    BlockNode(vector<BaseExpr*>);
    ~BlockNode();
    llvm::Value* codegen(Compiler&);
};

#endif