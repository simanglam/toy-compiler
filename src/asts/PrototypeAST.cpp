#include "asts/PrototypeAST.h"

PrototypeAST::PrototypeAST(string _name, vector<DeclearNode*> _args, TOKENS _returnType): name(_name), args(_args), returnType(_returnType) {}

Function* PrototypeAST::codegen(Compiler& c) {
    vector<llvm::Type*> Args(args.size());

    for (DeclearNode* node : args) {
        llvm::Type* type;
        switch (node->getType()){
            case TOK_TYPE_INT:
                type = llvm::Type::getInt32Ty(*c.TheContext);
                break;
            case TOK_TYPE_DOUBLE:
                type = llvm::Type::getDoubleTy(*c.TheContext);
                break;
            default:
                break;
        }

        Args.push_back(type);
    }

    llvm::Type* returnType;
    switch (this->returnType) {
        case TOK_TYPE_INT:
            returnType = llvm::Type::getInt32Ty(*c.TheContext);
            break;
        case TOK_TYPE_DOUBLE:
            returnType = llvm::Type::getDoubleTy(*c.TheContext);
           break;
    }

    FunctionType* FT = FunctionType::get(returnType, false);
    Function* F = Function::Create(FT, GlobalValue::ExternalLinkage, llvm::Twine(name), c.TheModule.get());
    int Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(this->args[Idx++]->getName());
    return F;
}
