#include "Compiler.h"
#include "asts/CastNode.h"
#include "asts/BinaryOpNode.h"
#include "asts/BinaryOpStrategy.h"

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

    if (op == TOK_OP_LEFTBRA) {
        Value* v = c.Builder->CreateGEP(lhsCode->getType(), lhsCode, rhsCode, "array");
        return c.Builder->CreateLoad(c.Builder->getInt32Ty(), v, "arrayElement");
    }

    return BinaryOpStrategy::getStrategy(lhs->evalType).codegen(lhsCode, rhsCode, op, c);

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
            if (lhs->evalType != rhs->evalType) {
                rhs = new CastNode(rhs, lhs->evalType, CastNodeStrategy::getCastStrategy(rhs->evalType));
                rhs->eval(a);
            }
            evalType = BOOL;
            break;
        case TOK_OP_EQUAL: case TOK_OP_UNEQUAL:
            if (lhs->evalType != BOOL) {
                lhs = new CastNode(lhs, BOOL, CastNodeStrategy::getCastStrategy(lhs->evalType));
                lhs->eval(a);
            }
            if (rhs->evalType != BOOL) {
                rhs = new CastNode(rhs, BOOL, CastNodeStrategy::getCastStrategy(rhs->evalType));
                rhs->eval(a);
            }
            evalType = BOOL;
            break;
        case TOK_OP_ASSIGN:
            evalType = lhs->evalType;
            if (!lhs->isLvalue()) {
                cerr << "Expect Lvalue at left hand side of assignment." << endl;
                return false;
            }
            break;
        case TOK_OP_LEFTBRA:
            if (rhs->evalType != INTEGER) {
                rhs = new CastNode(rhs, lhs->evalType, CastNodeStrategy::getCastStrategy(rhs->evalType));
            }

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