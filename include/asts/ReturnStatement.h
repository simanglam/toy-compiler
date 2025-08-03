#ifndef __ReturnStatement_Header__
#define __ReturnStatement_Header__
class ReturnStatement;

#include "Compiler.h"
#include "asts/Expression.h"

class ReturnStatement: public Expression {
    Expression* expr;
public:
    ReturnStatement(Expression*);
    ~ReturnStatement();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif