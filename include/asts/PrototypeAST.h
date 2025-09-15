#ifndef __PrototypeAST_HEADER__
#define __PrototypeAST_HEADER__
class PrototypeAST;

#include "asts/Statement.h"
#include "asts/DeclareNode.h"
#include "types/TypeInfo.h"

#include <vector>
#include <llvm/IR/Function.h>

using namespace llvm;


class PrototypeAST: public Statement {
    vector<DeclareNode*> args;
    string name;
    TypeInfo* returnType;
public:
    PrototypeAST(string, vector<DeclareNode*>, TypeInfo*);
    ~PrototypeAST();
    void codegen(Compiler&) override;
    string getName();
    vector<DeclareNode*>& getArgs();
    bool eval(Analyser&) override;
};

#endif