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
    if (options.inputs.size() != 0) {
        for (string file : options.inputs) {
            fstream f(file);
            Scanner s(f);
            Parser p(s);
            Analyser a;
            TheContext = new llvm::LLVMContext();
            TheModule = new Module(file, *TheContext);
            Builder = new IRBuilder<>(*TheContext);
            bool result = true;
            while ((ast = p.parseLine()) != nullptr){
                result = result && ast->eval(a);
                ast->codegen(*this);
                delete ast;
            }
            writeToFile(options.outputFileType, file);
            delete TheModule;
            delete Builder;
            delete TheContext;
        }
    }
    else {
        Scanner s(cin);
        Parser p(s);
        Analyser a;
        bool result = true;
        TheContext = new llvm::LLVMContext();
        TheModule = new Module("STDIN", *TheContext);
        Builder = new IRBuilder<>(*TheContext);
        while ((ast = p.parseLine()) != nullptr){
            result = result && ast->eval(a);
            ast->codegen(*this);
            delete ast;
        }
        string outputFileName("output.txt");
        writeToFile(options.outputFileType, outputFileName);
        delete TheModule;
        delete Builder;
        delete TheContext;
    }
}

bool Compiler::writeToFile(outputType outputFileType, string& fileName) {
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

    auto outputFilename = fileName.substr(0, fileName.find_last_of('.'));
    auto FileType = CodeGenFileType::Null;

    switch (outputFileType) {
        case ASM:
            outputFilename += ".s";
            FileType = CodeGenFileType::AssemblyFile;
            break;
        case OBJECT_FILE:
            outputFilename += ".o";
            FileType = CodeGenFileType::ObjectFile;
            break;
        case LLVM_IR:
            outputFilename += ".ll";
            break;
    }

    std::error_code EC;
    raw_fd_ostream dest(outputFilename, EC, sys::fs::OF_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return false;
    }

    legacy::PassManager pass;

    if (FileType != CodeGenFileType::Null) {
        if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
            errs() << "TargetMachine can't emit a file of this type";
            return false;
        }
        pass.run(*TheModule);
        dest.flush();
    }
    else {
        TheModule->print(dest, nullptr);
    }

    delete TargetMachine;

}


AllocaInst* Compiler::allocateVar(llvm::Type* type, string& name) {
    IRBuilder<> tempB(&currentFunction->getEntryBlock(), currentFunction->getEntryBlock().begin());
    return tempB.CreateAlloca(type, nullptr, Twine(name.c_str()));
}