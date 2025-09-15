#include "asts/DeclareNode.h"
#include "asts/DeclareNodeStrategy.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/GlobalVariable.h>

DeclareNodeStrategy::~DeclareNodeStrategy() {};

class LocalStrategy : public DeclareNodeStrategy {
public:
    ~LocalStrategy() { };

    void codegen(Compiler& c, DeclareNode* node) override {
        string id = node->getName();
        Expression* size = node->getSize();
        Expression* initVal = node->getInitVal();
        vector<Expression*>& values = node->getValues();
        TypeInfo* type = node->getType();
        if (!size){
            c.localVariables[id] = c.allocateVar(type->toLLVMType(c.TheContext), id);
            llvm::Value* initV = 
                initVal 
                    ? initVal->codegenExpr(c) 
                    : Constant::getNullValue(type->toLLVMType(c.TheContext));
                c.Builder->CreateStore(initV, c.localVariables[id]);
        }
        else {
            string old_name = id;
            string body = id + "_body";
            AllocaInst* arrayAlloc = c.allocateVar(type->toLLVMType(c.TheContext), old_name, size->codegenExpr(c));
            AllocaInst* arrayBody = c.allocateVar(type->toLLVMType(c.TheContext)->getPointerTo(), body);
            c.localVariables[old_name] = arrayBody;
            c.Builder->CreateStore(arrayAlloc, arrayBody, "FUCK");

            //Value* arrayBody = c.Builder->CreateLoad(arrayAlloc->getAllocatedType(), arrayAlloc);

            int idx = 0;
            for (Expression* e : values) {
                c.Builder->CreateStore(
                    e->codegenExpr(c),
                    c.Builder->CreateGEP(arrayAlloc->getType(),
                        arrayAlloc,
                        {c.Builder->getInt32(idx++)}
                    )
                );
            }
        }
    }
};


class GlobalStrategy : public DeclareNodeStrategy {
public:
    ~GlobalStrategy() { };

    void codegen(Compiler& c, DeclareNode* node) override {
        if (node->getInitVal() && !node->getInitVal()->isConstantExpr()){
            cout << "Not const expression" << endl;
            return ;
        }

        node->getInitVal()->codegenExpr(c);
        Constant* constant = nullptr;
        if (node->getInitVal()){
            if (node->getType()->toLLVMType(c.TheContext)->isIntegerTy())
                constant = ConstantInt::get(node->getType()->toLLVMType(c.TheContext), node->getInitVal()->getValue(), true);
            else 
                constant = ConstantFP::get(node->getType()->toLLVMType(c.TheContext), node->getInitVal()->getValue());
        }
        
        c.globalVar[node->getName()] = new llvm::GlobalVariable(
            *c.TheModule,
            node->getType()->toLLVMType(c.TheContext),
            false,
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            constant,
            node->getName()
        );
    }
};

DeclareNodeStrategy* DeclareNodeStrategy::getStrategy(DeclareType type) {
    switch (type) {
    case DeclareType::GLOBAL:
        return new GlobalStrategy();
    default:
        return new LocalStrategy();
    }
}