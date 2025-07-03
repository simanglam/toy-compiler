#include "Compiler.h"

Compiler::Compiler(Parser& _p): p(_p) {
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<Module>("my cool jit", *TheContext);
    Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

Compiler::~Compiler() {
    
}