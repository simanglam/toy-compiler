
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
    return c.Builder->CreateCall(f, argValues, "calltmp");
}

bool FunctionCallExpr::eval(Analyser& a) {
    bool result = true;
    if (!a.functionTable.count(name)) {
        cerr << "Undefined function: " << name << endl;
        return false;
    }
    if (a.functionTable[name].argType.size() != args.size()){
        cerr << "Wrong number of args: " << name << endl;
        return false;
    }
    for (int i = 0; i < args.size(); i++){
        result = result && args[i]->eval(a);
    }
    for (int i = 0; i < args.size(); i++){
        result = result && (args[i]->evalType == a.functionTable[name].argType[i]);
        if (args[i]->evalType != a.functionTable[name].argType[i]){
            cerr << "Wrong function argument." << endl;
        }
    }
    evalType = a.functionTable[name].returnType;
    return true;
}