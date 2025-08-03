#ifndef __GlobalDeclareNode_HEADER__
#define __GlobalDeclareNode_HEADER__
class GlobalDeclareNode;

#include "asts/Expression.h"

class GlobalDeclareNode : public Expression {
    TOKENS type;
    string id;
    Expression* initVal;
    int iVal;
    double dVal;
public:
    GlobalDeclareNode(string = "", TOKENS = TOK_ERROR, int = 0, double = 0.0);
    ~GlobalDeclareNode();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif