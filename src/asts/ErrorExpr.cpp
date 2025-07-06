#include "asts/ErrorExpr.h"


ErrorExpr::ErrorExpr(string _message): message(_message) {

}

ErrorExpr::~ErrorExpr() {

}

Value* ErrorExpr::codegen(Compiler& c) {
    cerr << message << endl;
    return nullptr;
}