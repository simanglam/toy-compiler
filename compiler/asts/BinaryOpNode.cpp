#include "Compiler.h"
#include "asts/BinaryOpNode.h"
#include "asts/VariableNode.h"
#include "asts/CastNode.h"

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

BinaryOpNode::BinaryOpNode(Expression* _lhs, TOKENS _op, Expression* _rhs): lhs(_lhs), op(_op), rhs(_rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs; delete rhs;
}


Value* BinaryOpNode::codegenExpr(Compiler& c) {
    if (op == TOK_OP_ASSIGN) {
        if (!lhs->isLvalue())  {
            cerr << "Expect lvalue at lhs of assign operator" << endl;
            return nullptr;
        }
        Value* var = lhs->codegenAddr(c);
        assert(var != nullptr);
        
        Value* storeValue = rhs->codegenExpr(c);
        if (lhs->evalType != rhs->evalType){
            storeValue = castToSameType(c, lhs->evalType, storeValue);
        }
        return c.Builder->CreateStore(storeValue, var);
    }
    

    llvm::Value* lhsCode = lhs->codegenExpr(c);
    llvm::Value* rhsCode = rhs->codegenExpr(c);
    if (!lhsCode || !rhsCode)
        return nullptr;

    Value* returnVal = nullptr;
    if (evalType == INTEGER) {
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
                break;
            case TOK_OP_EQUAL:
                returnVal = c.Builder->CreateICmpEQ(lhsCode, rhsCode, "eqltemp");
                break;
            case TOK_OP_LE:
                returnVal = c.Builder->CreateICmpSLE(lhsCode, rhsCode, "leqtemp");
                break;
            case TOK_OP_LT:
                returnVal = c.Builder->CreateICmpSLT(lhsCode, rhsCode, "ltemp");
                break;
            case TOK_OP_GE:
                returnVal = c.Builder->CreateICmpSGE(lhsCode, rhsCode, "geqtemp");
                break;
            case TOK_OP_GT:
                returnVal = c.Builder->CreateICmpSGT(lhsCode, rhsCode, "gttemp");
                break;
            default:
                break;
        }
    }
    if (evalType == FLOAT) {
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
                break;
            case TOK_OP_EQUAL:
                returnVal = c.Builder->CreateFCmpOEQ(lhsCode, rhsCode, "eqltemp");
                break;
            case TOK_OP_LE:
                returnVal = c.Builder->CreateFCmpOLE(lhsCode, rhsCode, "leqtemp");
                break;
            case TOK_OP_LT:
                returnVal = c.Builder->CreateFCmpOLT(lhsCode, rhsCode, "ltemp");
                break;
            case TOK_OP_GE:
                returnVal = c.Builder->CreateFCmpOGE(lhsCode, rhsCode, "geqtemp");
                break;
            case TOK_OP_GT:
                returnVal = c.Builder->CreateFCmpOGT(lhsCode, rhsCode, "gttemp");
                break;
            default:
                break;
        }
    }

    if (op == TOK_OP_LEFTBRA) {
        Value* v = c.Builder->CreateGEP(lhsCode->getType(), lhsCode, rhsCode, "array");
        return c.Builder->CreateLoad(c.Builder->getInt32Ty(), v, "arrayElement");
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
        case TOK_OP_LEFTBRA:
            return c.Builder->CreateGEP(lhsCode->getType(), lhsCode, {c.Builder->getInt32(0), rhsCode}, "array");
            //return c.Builder->CreateExtractElement(c.Builder->CreateGEP(lhsCode->getType(), lhsCode, {c.Builder->getInt32(0), rhs}, "array"), rhsCode, "Element");
        default:
            break;
    }


    return c.Builder->CreateIntCast(returnVal, Type::getInt32Ty(*c.TheContext), true, "intCast");
    
}

bool BinaryOpNode::eval(Analyser& a) {
    bool lhsEval = lhs->eval(a);
    bool rhsEval = rhs->eval(a);

    if (!lhsEval || !rhsEval)
        return false;

    switch (op) {    
        case TOK_OP_AND: case TOK_OP_OR: 
        case TOK_OP_LT: case TOK_OP_GT: 
        case TOK_OP_LE: case TOK_OP_GE:
        case TOK_OP_EQUAL: case TOK_OP_UNEQUAL:
            evalType = INTEGER;
            break;
        case TOK_OP_ASSIGN:
            evalType = lhs->evalType;
            if (!lhs->isLvalue()) {
                cerr << "Expect Lvalue at left hand side of assignment." << endl;
                return false;
            }
            break;
        case TOK_OP_LEFTBRA:
            assert(rhs->evalType == INTEGER);
            if (lhs->evalType == INT_POINTER)
                evalType = INTEGER;
            else
                evalType = FLOAT;
            break;
        default:
            if (lhs->evalType != rhs->evalType){
                rhs = new CastNode(rhs, lhs->evalType, CastNodeStrategy::getCastStrategy(rhs->evalType));
                rhs->eval(a);
                evalType = lhs->evalType;
            }
            else {
                evalType = lhs->evalType;
            }
            break;
    }
    return true;
}

bool BinaryOpNode::isLvalue() {
    return op == TOK_OP_LEFTBRA && lhs->isLvalue();
}

Value* BinaryOpNode::codegenAddr(Compiler& c) {
    if (op != TOK_OP_LEFTBRA)
        return nullptr;
    Value* lhsCode = lhs->codegenExpr(c);
    Value* rhsCode = rhs->codegenExpr(c);
    Value* v = c.Builder->CreateGEP(lhsCode->getType(), lhsCode, rhsCode, "arrayPointer");
    return v;
}