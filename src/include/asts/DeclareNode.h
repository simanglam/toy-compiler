#ifndef __DeclareNode_HEADER__
#define __DeclareNode_HEADER__
class DeclareNode;

#include "asts/BaseExpr.h"

class DeclareNode : public BaseExpr {
    TOKENS type;
    string id;
    BaseExpr* initVal;
public:
    DeclareNode(string = "", TOKENS = TOK_ERROR, BaseExpr* = nullptr);
    ~DeclareNode();
    llvm::Value* codegen(Compiler&) override;
    TOKENS getType();
    string& getName();
};

#endif