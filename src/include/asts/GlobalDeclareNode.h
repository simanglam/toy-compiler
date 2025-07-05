#ifndef __GlobalDeclareNode_HEADER__
#define __GlobalDeclareNode_HEADER__
class GlobalDeclareNode;

#include "asts/BaseExpr.h"

class GlobalDeclareNode : public BaseExpr {
    TOKENS type;
    string id;
    BaseExpr* initVal;
    int iVal;
    double dVal;
public:
    GlobalDeclareNode(string = "", TOKENS = TOK_ERROR, int = 0, double = 0.0);
    ~GlobalDeclareNode();
    Value* codegen(Compiler&) override;
};

#endif