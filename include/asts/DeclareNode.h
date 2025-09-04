#ifndef __DeclareNode_HEADER__
#define __DeclareNode_HEADER__

#include "asts/Expression.h"
#include "asts/Statement.h"
#include "Token.h"
#include "types/TypeInfo.h"
#include <vector>
#include <string>

static vector<Expression*> emptyValue;

class DeclareNode {
    TypeInfo* type;
    string id;
    Expression* initVal;
    Expression* size;
    vector<Expression*> values;
public:
    DeclareNode(TypeInfo*, string = "", Expression* = nullptr, Expression* = nullptr, vector<Expression*>& = emptyValue);
    ~DeclareNode();
    TypeInfo* getType();
    string& getName();
    void codegen(Compiler&);
    bool eval(Analyser&);
};

#endif