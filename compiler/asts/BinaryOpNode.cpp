#include "Compiler.h"
#include "asts/BinaryOpNode.h"
#include "asts/VariableNode.h"

Value* castToSameType(Compiler& c, EVALTYPE target, Value* storeValue) {
    switch (target){
        case FLOAT:
            storeValue = c.Builder->CreateSIToFP(storeValue, Type::getDoubleTy(*c.TheContext), "floatCastTemp");
            break;
        case INTEGER:
            storeValue = c.Builder->CreateFPToSI(storeValue, Type::getInt32Ty(*c.TheContext), "IntCastTemp");
            break;
    }
    return storeValue;
}

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
        
        Value* storeValue = rhs->codegen(c);
        if (lhs->evalType != rhs->evalType){
            storeValue = castToSameType(c, lhs->evalType, storeValue);
        }
        return c.Builder->CreateStore(storeValue, var);
    }
    

    llvm::Value* lhsCode = lhs->codegen(c);
    llvm::Value* rhsCode = rhs->codegen(c);
    if (!lhsCode || !rhsCode)
        return nullptr;
    if (lhs->evalType != evalType) {
        lhsCode = castToSameType(c, evalType, lhsCode);
        lhs->evalType = evalType;
    }
    if (rhs->evalType != evalType) {
        rhsCode = castToSameType(c, evalType, rhsCode);
        rhs->evalType = evalType;
    }

    Value* returnVal = nullptr;
    if (rhs->evalType == INTEGER) {
        switch (op) {
            case TOK_OP_ADD:
                return c.Builder->CreateAdd(lhsCode, rhsCode, "addtmp");
            case TOK_OP_MINUS:
                return c.Builder->CreateSub(lhsCode, rhsCode, "subtmp");
            case TOK_OP_TIMES:
                return c.Builder->CreateMul(lhsCode, rhsCode, "timetmp");
            case TOK_OP_DIVIDE:
                return c.Builder->CreateSDiv(lhsCode, rhsCode, "divtmp");
            case TOK_OP_UNEQUAL:
                returnVal = c.Builder->CreateICmpNE(lhsCode, rhsCode, "uneqltemp");
            case TOK_OP_EQUAL:
                returnVal = c.Builder->CreateICmpEQ(lhsCode, rhsCode, "eqltemp");
            case TOK_OP_LE:
                returnVal = c.Builder->CreateICmpSLE(lhsCode, rhsCode, "leqtemp");
            case TOK_OP_LT:
                returnVal = c.Builder->CreateICmpSLT(lhsCode, rhsCode, "ltemp");
            case TOK_OP_GE:
                returnVal = c.Builder->CreateICmpSGE(lhsCode, rhsCode, "geqtemp");
            case TOK_OP_GT:
                returnVal = c.Builder->CreateICmpSGT(lhsCode, rhsCode, "gttemp");
            default:
                break;
        }
    }
    if (rhs->evalType == FLOAT) {
        switch (op){
            case TOK_OP_ADD:
                return c.Builder->CreateFAdd(lhsCode, rhsCode, "addtmp");
            case TOK_OP_MINUS:
                return c.Builder->CreateFSub(lhsCode, rhsCode, "subtmp");
            case TOK_OP_TIMES:
                return c.Builder->CreateFMul(lhsCode, rhsCode, "timetmp");
            case TOK_OP_DIVIDE:
                return c.Builder->CreateFDiv(lhsCode, rhsCode, "divtmp");
            case TOK_OP_UNEQUAL:
                returnVal = c.Builder->CreateFCmpONE(lhsCode, rhsCode, "uneqltemp");
            case TOK_OP_EQUAL:
                returnVal = c.Builder->CreateFCmpOEQ(lhsCode, rhsCode, "eqltemp");
            case TOK_OP_LE:
                returnVal = c.Builder->CreateFCmpOLE(lhsCode, rhsCode, "leqtemp");
            case TOK_OP_LT:
                returnVal = c.Builder->CreateFCmpOLT(lhsCode, rhsCode, "ltemp");
            case TOK_OP_GE:
                returnVal = c.Builder->CreateFCmpOGE(lhsCode, rhsCode, "geqtemp");
            case TOK_OP_GT:
                returnVal = c.Builder->CreateFCmpOGT(lhsCode, rhsCode, "gttemp");
            default:
                break;
        }
    }

    if (lhs->evalType == FLOAT)
        lhsCode = c.Builder->CreateFCmpONE(lhsCode, ConstantFP::get(lhsCode->getType(), 0.0), "fcmp");
    else
        lhsCode = c.Builder->CreateICmpNE(lhsCode, ConstantInt::get(lhsCode->getType(), 0), "icmp");
    if (rhs->evalType == FLOAT)
        rhsCode = c.Builder->CreateFCmpONE(rhsCode, ConstantFP::get(rhsCode->getType(), 0.0), "fcmp");
    else
        rhsCode = c.Builder->CreateICmpNE(rhsCode, ConstantInt::get(rhsCode->getType(), 0), "icmp");

    switch (op) {
        case TOK_OP_AND:            
            returnVal = c.Builder->CreateLogicalAnd(lhsCode, rhsCode, "logicalAnd");
            break;
        case TOK_OP_OR:
            returnVal = c.Builder->CreateLogicalOr(lhsCode, rhsCode, "logicalAnd");
            break;

        default:
            break;
    }

    return c.Builder->CreateIntCast(returnVal, Type::getInt32Ty(*c.TheContext), true, "intCast");
    
}

bool BinaryOpNode::eval(Analyser& a) {
    bool lhsEval = lhs->eval(a);
    bool rhsEval = rhs->eval(a);
    bool result = true;

    if (!lhsEval || !rhsEval)
        result = false;

    switch (op) {    
        case TOK_OP_AND:
        case TOK_OP_OR: 
        case TOK_OP_LT:
        case TOK_OP_GT: 
        case TOK_OP_LE:
        case TOK_OP_GE:
        case TOK_OP_EQUAL:
        case TOK_OP_UNEQUAL:
            evalType = INTEGER;
            break;
        case TOK_OP_ASSIGN:
            evalType = lhs->evalType;
            break;
        default:
            if (lhs->evalType != rhs->evalType){
                evalType = INTEGER;
            }
            else {
                evalType = lhs->evalType;
            }
            break;
    }
    return result;
}
