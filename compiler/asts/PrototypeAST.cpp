#include "asts/PrototypeAST.h"
#include "asts/Expression.h"

#include "Compiler.h"
#include "Analyser.h"

PrototypeAST::PrototypeAST(string _name, vector<DeclareNode*> _args, TOKENS _returnType): name(_name), args(_args), returnType(_returnType) {}

PrototypeAST::~PrototypeAST() {
    for (DeclareNode* node : args)
        delete node;
}

string PrototypeAST::getName() {
    return name;
}

vector<DeclareNode*>& PrototypeAST::getArgs() {
    return args;
}

void PrototypeAST::codegen(Compiler& c) {
    vector<llvm::Type*> Args;

    for (DeclareNode* node : args) {
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
        default: break;
    }

    FunctionType* FT = FunctionType::get(returnType, Args, false);
    Function* F = Function::Create(FT, GlobalValue::ExternalLinkage, llvm::Twine(name), c.TheModule);
}

bool PrototypeAST::eval(Analyser& a) {
    if (a.functionTable.count(name)){
        cerr << "You can't redifined the function: " << name << endl;
        return false;
    }
    EVALTYPE evalType = (returnType == TOK_TYPE_INT) ? INTEGER : FLOAT;
    FunctionInfo f;
    for (DeclareNode* arg : args){
        EVALTYPE e = UNDIFINED;
        switch (arg->getType())
        {
        case TOK_TYPE_INT:
            e = INTEGER;
            break;
        case TOK_TYPE_DOUBLE:
            e = FLOAT;
            break;
        default:
            e = UNDIFINED;
            break;
        }
        f.argType.push_back(e);
    }
    f.returnType = evalType;
    a.functionTable[name] = f;
    return true;
}