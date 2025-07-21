#ifndef __ReturnStatement_Header__
#define __ReturnStatement_Header__
class ReturnStatement;

#include "Compiler.h"
#include "asts/BaseExpr.h"

class ReturnStatement: public BaseExpr {
    BaseExpr* expr;
public:
    ReturnStatement(BaseExpr*);
    ~ReturnStatement();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif