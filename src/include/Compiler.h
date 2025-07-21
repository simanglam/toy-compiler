#ifndef __Compiler_Header__
#define __Compiler_Header__
class Compiler;

#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <Parser.h>

using namespace llvm;

class Compiler {
    Parser& p;
public:
    std::unique_ptr<llvm::LLVMContext> TheContext;
    std::unique_ptr<llvm::Module> TheModule;
    std::unique_ptr<IRBuilder<>> Builder;
    std::map<std::string, llvm::AllocaInst*> localVariables;
    std::map<std::string, llvm::GlobalVariable*> globalVar;
    Function* currentFunction;
    void compileToASM();
    void compileToIR();

    AllocaInst* allocateVar(llvm::Type*, string&);
    Compiler(Parser&);
    ~Compiler();
};

#endif