#ifndef __Compiler_Header__
#define __Compiler_Header__
class Compiler;
class Parser;

#include <map>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include "CommandLineOptions.h"
#include "Parser.h"

class Compiler {
    CommandLineOptions& options;
public:
    llvm::LLVMContext* TheContext;
    llvm::Module* TheModule;
    IRBuilder<>* Builder;
    std::map<std::string, llvm::AllocaInst*> localVariables;
    std::map<std::string, llvm::GlobalVariable*> globalVar;
    Function* currentFunction;
    bool compile();
    bool writeToFile(outputType, string&);

    AllocaInst* allocateVar(llvm::Type*, string&, Value* = nullptr);
    GlobalVariable* allocateGlobalVar(llvm::Type*, string&);
    Compiler(CommandLineOptions&);
    ~Compiler();
};

#endif