#ifndef __VariableNode_HEADER__
#define __VariableNode_HEADER__

#include "asts/BaseExpr.h"
#include <llvm/IR/Value.h>
#include <string>

using namespace llvm;
using namespace std;

class VariableNode : public BaseExpr {
    string name;
public:
    VariableNode(string);
    Value* codegen(Compiler&) override;
    string& getName();
};

#endif