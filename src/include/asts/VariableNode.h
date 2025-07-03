#ifndef __VariableNode_HEADER__
#define __VariableNode_HEADER__

#include "asts/BaseAST.h"
#include <llvm/IR/Value.h>
#include <string>

using namespace llvm;
using namespace std;

class VariableNode : public BaseAST {
    string name;
public:
    VariableNode(string);
    Value* codegen() override;
    void print() override;
    int result() override;
};

#endif