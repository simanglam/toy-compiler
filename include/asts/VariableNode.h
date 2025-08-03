#ifndef __VariableNode_HEADER__
#define __VariableNode_HEADER__

#include "asts/Expression.h"
#include <llvm/IR/Value.h>
#include <string>

using namespace llvm;
using namespace std;

class VariableNode : public Expression {
    string name;
public:
    VariableNode(string);
    Value* codegen(Compiler&) override;
    string& getName();
    bool eval(Analyser&) override;
};

#endif