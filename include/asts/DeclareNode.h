#ifndef __DeclareNode_HEADER__
#define __DeclareNode_HEADER__

#include "asts/Expression.h"
#include "asts/Statement.h"
#include "Token.h"
#include <string>

class DeclareNode : public Statement {
    TOKENS type;
    string id;
    Expression* initVal;
public:
    DeclareNode(string = "", TOKENS = TOK_ERROR, Expression* = nullptr);
    ~DeclareNode();
    TOKENS getType();
    string& getName();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif