#ifndef __GlobalDeclearNode_HEADER__
#define __GlobalDeclearNode_HEADER__
class GlobalDeclearNode;

#include "asts/BaseExpr.h"

class GlobalDeclearNode : public BaseExpr {
    TOKENS type;
    string id;
    BaseExpr* initVal;
    int iVal;
    double dVal;
public:
    GlobalDeclearNode(string = "", TOKENS = TOK_ERROR, int = 0, double = 0.0);
    ~GlobalDeclearNode();
    Value* codegen(Compiler&) override;
};

#endif