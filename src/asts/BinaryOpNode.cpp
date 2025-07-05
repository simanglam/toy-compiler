#include "Compiler.h"
#include "asts/BinaryOpNode.h"
#include "asts/VariableNode.h"

BinaryOpNode::BinaryOpNode(BaseExpr* _lhs, char _op, BaseExpr* _rhs): lhs(_lhs), op(_op), rhs(_rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs; delete rhs;
}


Value* BinaryOpNode::codegen(Compiler& c) {

    if (op == '=') {
        if (typeid(*lhs) != typeid(VariableNode)) {
            cerr << "Expect variable at lhs of assign operator" << endl;
            return nullptr;
        }
        VariableNode* lid = (VariableNode*)lhs;
        AllocaInst* var = c.localVariables[lid->getName()];
        if (!var) {
            cerr << "Unknow variable: " << lid->getName() << endl;
            return nullptr;
        }
        c.Builder->CreateStore(rhs->codegen(c), var);
        return var;
    }
    

    llvm::Value* lhsCode = lhs->codegen(c);
    llvm::Value* rhsCode = rhs->codegen(c);
    if (!lhsCode || !rhsCode)
        return nullptr;
    switch (op){
        case '+':
            return c.Builder->CreateAdd(lhsCode, rhsCode, "addtmp");
        case '-':
            return c.Builder->CreateSub(lhsCode, rhsCode, "subtmp");
        case '*':
            return c.Builder->CreateMul(lhsCode, rhsCode, "timetmp");
        case '/':
            return c.Builder->CreateSDiv(lhsCode, rhsCode, "divtmp");
    }
    return nullptr;
    
}
