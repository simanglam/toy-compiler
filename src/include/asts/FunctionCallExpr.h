#ifndef __FunctionCallExpr_HEADER__
#define __FunctionCallExpr_HEADER__

#include "asts/BaseExpr.h"

class FunctionCallExpr : public BaseExpr{
    vector<BaseExpr *> args;
    string name;
public:
    FunctionCallExpr(string&, vector<BaseExpr*>&);
    ~FunctionCallExpr();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif
