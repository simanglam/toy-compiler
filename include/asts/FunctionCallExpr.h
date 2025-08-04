#ifndef __FunctionCallExpr_HEADER__
#define __FunctionCallExpr_HEADER__

#include "asts/Expression.h"
#include <vector>
#include <string>

class FunctionCallExpr : public Expression{
    std::vector<Expression *> args;
    std::string name;
public:
    FunctionCallExpr(std::string&, std::vector<Expression*>&);
    ~FunctionCallExpr();
    llvm::Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif
