#ifndef __ArrayDeclare_HEADER__
#define __ArrayDeclare_HEADER__

#include "Expression.h"
#include "Token.h"
#include <vector>

class ArrayDeclare: public Expression {
    TOKENS type;
    vector<Expression*> values;
    Expression* size;
    string name;
public:
    ArrayDeclare(TOKENS, vector<Expression*>&, Expression*, string&);
    ~ArrayDeclare();
    void codegen(Compiler&) override;
    llvm::Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
};


#endif