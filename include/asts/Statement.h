#ifndef __Statement_HEADER__
#define __Statement_HEADER__
#include <string>
#include <llvm/IR/Value.h>
#include "EvalType.h"
#include "asts/ASTNode.h"

class Statement : public ASTNode {
public:
    Statement();
    virtual ~Statement();
};


#include "Compiler.h"
#include "Analyser.h"

#endif