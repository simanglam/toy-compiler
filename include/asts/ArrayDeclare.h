#ifndef __ArrayDeclare_HEADER__
#define __ArrayDeclare_HEADER__

#include "Expression.h"

class ArrayDeclare: public Expression {
    TOKENS type;
    vector<Expression*> values;
    Expression* size;
    string name;
public:
    ArrayDeclare(TOKENS, vector<Expression*>&, Expression*, string&);
    ~ArrayDeclare();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};


#endif