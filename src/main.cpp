#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/IR/LegacyPassManager.h"

#include "include/Scanner.h"
#include "include/Token.h"
#include "include/Parser.h"


static map<int, int> opTable;

int main(int argc, char ** argv){
    string filename = "./test.txt";
    Scanner s(filename);
    Parser p(s);
    Compiler c(p);
    BaseExpr* ast = nullptr;
    auto TargetTriple = sys::getDefaultTargetTriple();
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    if (!Target) {
        errs() << Error;
        return 1;
    }
    
    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, Reloc::PIC_);
    c.TheModule->setDataLayout(TargetMachine->createDataLayout());
    c.TheModule->setTargetTriple(TargetTriple);

    while ((ast = p.parseLine()) != nullptr){
        ast->codegen(c);
        delete ast;
    }
    c.TheModule.get()->print(outs(), nullptr);
    auto outputFilename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(outputFilename, EC, sys::fs::OF_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    legacy::PassManager pass;
    auto FileType = CodeGenFileType::AssemblyFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TargetMachine can't emit a file of this type";
        return 1;
    }
}