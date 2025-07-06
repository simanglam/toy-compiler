
#include "asts/FunctionCallExpr.h"

FunctionCallExpr::FunctionCallExpr(string& _name, vector<BaseExpr*>& _args): name(_name), args(_args) {

}

FunctionCallExpr::~FunctionCallExpr() {
    for (BaseExpr* arg : args)
        delete arg;
}

Value* FunctionCallExpr::codegen(Compiler& c) {
    Function* f = c.TheModule->getFunction(name);
    if (!f) return nullptr;
    vector<Value*> argValues;
    for (BaseExpr* arg : args)
        argValues.push_back(arg->codegen(c));
    return c.Builder->CreateCall(f, argValues);
}