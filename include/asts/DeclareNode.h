#ifndef __DeclareNode_HEADER__
#define __DeclareNode_HEADER__
class DeclareNode;

#include "asts/Expression.h"
#include "Token.h"
#include <string>

class DeclareNode : public Expression {
    TOKENS type;
    string id;
    Expression* initVal;
public:
    DeclareNode(string = "", TOKENS = TOK_ERROR, Expression* = nullptr);
    ~DeclareNode();
    TOKENS getType();
    string& getName();
    llvm::Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif