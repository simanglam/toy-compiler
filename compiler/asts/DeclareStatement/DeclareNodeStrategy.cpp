#include "asts/DeclareNode.h"
#include "asts/DeclareNodeStrategy.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/GlobalVariable.h>

DeclareNode::~DeclareNode() {};

class LocalStrategy : public DeclareNodeStrategy {
public:
    ~LocalStrategy() override {};

    void codegen(Compiler& c, DeclareNode* node) override {
        
    }
};


class GlobalStrategy : public DeclareNodeStrategy {
public:
    ~GlobalStrategy() override {};

    void codegen(Compiler& c, DeclareNode* node) override {
        c.globalVar[node->getName()] = new llvm::GlobalVariable(
            node->getType()->getType(c.TheContext),
            false,
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            nullptr,
            node->getName()
        );
    }
};