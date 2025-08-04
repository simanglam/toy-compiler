#include "asts/ErrorExpr.h"
#include <iostream>

using namespace std;


ErrorExpr::ErrorExpr(string _message): message(_message) {

}

ErrorExpr::~ErrorExpr() {

}

void ErrorExpr::codegen(Compiler& c) {
    cerr << message << endl;
}

llvm::Value* ErrorExpr::codegenExpr(Compiler& c) {
    this->codegen(c);
    return nullptr;
}

bool ErrorExpr::eval(Analyser& c) {
    return false;
}