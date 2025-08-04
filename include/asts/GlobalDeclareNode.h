#ifndef __GlobalDeclareNode_HEADER__
#define __GlobalDeclareNode_HEADER__
class GlobalDeclareNode;

#include "asts/Expression.h"
#include "asts/Statement.h"
#include "Token.h"
#include <string>

class GlobalDeclareNode : public Statement {
    TOKENS type;
    std::string id;
    Expression* initVal;
    int iVal;
    double dVal;
public:
    GlobalDeclareNode(std::string = "", TOKENS = TOK_ERROR, int = 0, double = 0.0);
    ~GlobalDeclareNode();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif