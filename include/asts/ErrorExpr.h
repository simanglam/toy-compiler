#ifndef __ErrorExpr_HEADER__
#define __ErrorExpr_HEADER__
#include "asts/Expression.h"
#include <string>

class Compiler;

class ErrorExpr : public Expression{
    std::string message;
public:
    ErrorExpr(std::string);
    ~ErrorExpr();
    void codegen(Compiler&) override;
    llvm::Value* codegenExpr(Compiler&) override;
    bool eval(Analyser&) override;
};

#endif