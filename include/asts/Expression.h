#ifndef __Expression_HEADER__
#define __Expression_HEADER__
#include <string>
#include <llvm/IR/Value.h>
#include "EvalType.h"
#include "asts/ASTNode.h"

class Compiler;
class Analyser;

class Expression: public ASTNode {
public:
    EVALTYPE evalType = UNDIFINED;
    Expression();
    virtual ~Expression();
    virtual void codegen(Compiler&) = 0;
    virtual Value* codegenExpr(Compiler&) = 0;
    virtual bool eval(Analyser&) = 0;
};


#include "Compiler.h"
#include "Analyser.h"

#endif