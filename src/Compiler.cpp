#include "Compiler.h"

Compiler::Compiler(string& fileName): s(fileName), p(s) {
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<Module>("test.txt", *TheContext);
    Builder = std::make_unique<IRBuilder<>>(*TheContext);
    
}

Compiler::~Compiler() {
    
}

AllocaInst* Compiler::allocateVar(llvm::Type* type, string& name) {
    IRBuilder<> tempB(&currentFunction->getEntryBlock(), currentFunction->getEntryBlock().begin());
    return tempB.CreateAlloca(type, nullptr, Twine(name.c_str()));
}