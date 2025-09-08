#ifndef __DeclareNodeStrategy_Header__
#define __DeclareNodeStrategy_Header__

#include <llvm/IR/Value.h>
#include "Compiler.h"

class DeclareNode;

enum DeclareType {
    GLOBAL,
    LOCAL
};

class DeclareNodeStrategy {
public:
    virtual ~DeclareNodeStrategy();
    static DeclareNodeStrategy* getStrategy(DeclareType);
    virtual void codegen(Compiler&, DeclareNode*) = 0;
};

#endif