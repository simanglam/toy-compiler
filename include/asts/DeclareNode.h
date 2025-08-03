#ifndef __DeclareNode_HEADER__
#define __DeclareNode_HEADER__
class DeclareNode;

#include "asts/Expression.h"

class DeclareNode : public Expression {
    TOKENS type;
    string id;
    Expression* initVal;
public:
    DeclareNode(string = "", TOKENS = TOK_ERROR, Expression* = nullptr);
    ~DeclareNode();
    llvm::Value* codegen(Compiler&) override;
    TOKENS getType();
    string& getName();
    bool eval(Analyser&) override;
};

#endif