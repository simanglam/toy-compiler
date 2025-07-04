#ifndef __DeclearNode_HEADER__
#define __DeclearNode_HEADER__
class DeclearNode;

#include "asts/BaseExpr.h"

class DeclearNode : public BaseExpr {
    TOKENS type;
    string id;
    BaseExpr* initVal;
public:
    DeclearNode(string = "", TOKENS = TOK_ERROR, BaseExpr* = nullptr);
    llvm::Value* codegen(Compiler&) override;
    TOKENS getType();
    string& getName();
};

#endif