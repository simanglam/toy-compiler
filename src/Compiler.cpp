#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/IR/LegacyPassManager.h"

#include "Compiler.h"

Compiler::Compiler(CommandLineOptions& _options): options(_options) {
    
}

Compiler::~Compiler() {
    
}

bool Compiler::compile() {
    BaseExpr* ast;
    Analyser a;
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<Module>("", *TheContext);
    Builder = std::make_unique<IRBuilder<>>(*TheContext);
    string inputFile = options.inputs[0];
    fstream f(inputFile);
    Scanner s(f);
    Parser p(s);
    bool result = true;
    while ((ast = p.parseLine()) != nullptr){
        result = result && ast->eval(a);
        cerr << "OK" << endl;
        ast->codegen(*this);
        delete ast;
    }
    return writeToFile();
}

bool Compiler::writeToFile() {
    auto TargetTriple = sys::getDefaultTargetTriple();
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);
    auto CPU = "generic";
    auto Features = "";

    if (!Target) {
        errs() << Error;
        return false;
    }

    TargetOptions opt;
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, Reloc::PIC_);
    TheModule->setDataLayout(TargetMachine->createDataLayout());
    TheModule->setTargetTriple(TargetTriple);

    TheModule.get()->print(outs(), nullptr);
    auto outputFilename = "output.s";
    std::error_code EC;
    raw_fd_ostream dest(outputFilename, EC, sys::fs::OF_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return false;
    }

    legacy::PassManager pass;
    auto FileType = CodeGenFileType::AssemblyFile;


    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TargetMachine can't emit a file of this type";
        return false;
    }
    pass.run(*TheModule);
    dest.flush();

    delete TargetMachine;

}


AllocaInst* Compiler::allocateVar(llvm::Type* type, string& name) {
    IRBuilder<> tempB(&currentFunction->getEntryBlock(), currentFunction->getEntryBlock().begin());
    return tempB.CreateAlloca(type, nullptr, Twine(name.c_str()));
}