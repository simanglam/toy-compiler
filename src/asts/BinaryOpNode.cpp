#include "Compiler.h"
#include "asts/BinaryOpNode.h"
#include "asts/VariableNode.h"

BinaryOpNode::BinaryOpNode(BaseExpr* _lhs, TOKENS _op, BaseExpr* _rhs): lhs(_lhs), op(_op), rhs(_rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs; delete rhs;
}


Value* BinaryOpNode::codegen(Compiler& c) {

    if (op == TOK_OP_ASSIGN) {
        VariableNode* lid = static_cast<VariableNode*>(lhs);
        if (!lid)  {
            cerr << "Expect variable at lhs of assign operator" << endl;
            return nullptr;
        }
        Value* var = c.localVariables[lid->getName()]; 
        if (!var) var = c.globalVar[lid->getName()];
        if (!var) {
            cerr << "Unknow variable: " << lid->getName() << endl;
            return nullptr;
        }
        
        Value* storeValue = rhs->codegen(c);
        if (storeValue->getType() != var->getType()){
            switch (storeValue->getType()->getTypeID()){
                case Type::IntegerTyID:
                    storeValue = c.Builder->CreateSIToFP(storeValue, Type::getDoubleTy(*c.TheContext), "doubleTemp");
                    break;
                default:
                    storeValue = c.Builder->CreateFPToSI(storeValue, Type::getInt32Ty(*c.TheContext), "intTemp");
                    break;
            }
        }
        c.Builder->CreateStore(storeValue, var);
        return var;
    }
    

    llvm::Value* lhsCode = lhs->codegen(c);
    llvm::Value* rhsCode = rhs->codegen(c);
    if (!lhsCode || !rhsCode)
        return nullptr;
    switch (op){
        case TOK_OP_ADD:
            return c.Builder->CreateAdd(lhsCode, rhsCode, "addtmp");
        case TOK_OP_MINUS:
            return c.Builder->CreateSub(lhsCode, rhsCode, "subtmp");
        case TOK_OP_TIMES:
            return c.Builder->CreateMul(lhsCode, rhsCode, "timetmp");
        case TOK_OP_DIVIDE:
            return c.Builder->CreateSDiv(lhsCode, rhsCode, "divtmp");
        case TOK_OP_UNEQUAL:
            return c.Builder->CreateICmpNE(lhsCode, rhsCode, "uneqltemp");
        case TOK_OP_EQUAL:
            return c.Builder->CreateICmpEQ(lhsCode, rhsCode, "uneqltemp");
        case TOK_OP_LE:
            return c.Builder->CreateICmpSLE(lhsCode, rhsCode, "uneqltemp");
        case TOK_OP_LT:
            return c.Builder->CreateICmpSLT(lhsCode, rhsCode, "uneqltemp");
        case TOK_OP_GE:
            return c.Builder->CreateICmpSGE(lhsCode, rhsCode, "uneqltemp");
        case TOK_OP_GT:
            return c.Builder->CreateICmpSGT(lhsCode, rhsCode, "uneqltemp");
        default:
            break;
    }
    return nullptr;
    
}
