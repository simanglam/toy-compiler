#include "Compiler.h"
#include "asts/DeclareStatement.h"

DeclareStatement::DeclareStatement() {}
DeclareStatement::~DeclareStatement() {
    for (DeclareNode* declare : declares)
        delete declare;
}

void DeclareStatement::pushNode(DeclareNode* node) {
    declares.push_back(node);
}

void DeclareStatement::codegen(Compiler& c) {
    for (DeclareNode* declare : declares){
        declare->codegen(c);
    }
}


bool DeclareStatement::eval(Analyser& a) {
    for (DeclareNode* declare : declares) {
        declare->eval(a);
    }
}
