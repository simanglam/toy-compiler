#ifndef __PrototypeAST_HEADER__
#define __PrototypeAST_HEADER__
class PrototypeAST;

#include "asts/Statement.h"
#include "asts/DeclareNode.h"

#include <vector>
#include <llvm/IR/Function.h>

using namespace llvm;


class PrototypeAST: public Statement {
    TOKENS returnType;
    vector<DeclareNode*> args;
    string name;
public:
    PrototypeAST(string, vector<DeclareNode*>, TOKENS);
    ~PrototypeAST();
    void codegen(Compiler&) override;
    string getName();
    vector<DeclareNode*>& getArgs();
    bool eval(Analyser&) override;
};

#endif