#ifndef __ArrayDeclare_HEADER__
#define __ArrayDeclare_HEADER__

#include "asts/Expression.h"
#include "asts/Statement.h"
#include "Token.h"
#include <vector>

class ArrayDeclare: public Statement {
    TOKENS type;
    vector<Expression*> values;
    Expression* size;
    string name;
public:
    ArrayDeclare(TOKENS, vector<Expression*>&, Expression*, string&);
    ~ArrayDeclare();
    void codegen(Compiler&) override;
    bool eval(Analyser&) override;
};


#endif