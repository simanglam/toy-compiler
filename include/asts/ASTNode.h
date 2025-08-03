#ifndef __ASTNode_HEADER__
#define __ASTNode_HEADER__
#include <string>
#include <llvm/IR/Value.h>
#include "EvalType.h"

class Compiler;
class Analyser;

class ASTNode {
public:
    ASTNode();
    virtual ~ASTNode();
    virtual bool eval(Analyser&) = 0;
    virtual void codegen(Compiler&) = 0;
};


#include "Compiler.h"
#include "Analyser.h"

#endif