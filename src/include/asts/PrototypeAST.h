#ifndef __PrototypeAST_HEADER__
#define __PrototypeAST_HEADER__
class PrototypeAST;

#include "asts/BaseExpr.h"
#include "asts/DeclearNode.h"

#include <vector>
#include <llvm/IR/Function.h>

using namespace llvm;


class PrototypeAST: public BaseExpr {
    TOKENS returnType;
    vector<DeclearNode*> args;
    string name;
public:
    PrototypeAST(string, vector<DeclearNode*>, TOKENS);
    ~PrototypeAST();
    Function* codegen(Compiler&) override;
    string getName();
    vector<DeclearNode*>& getArgs();
};

#endif