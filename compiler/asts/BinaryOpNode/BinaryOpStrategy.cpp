#include "Compiler.h"
#include "asts/BinaryOpStrategy.h"

using namespace llvm;

BinaryOpStrategy::BinaryOpStrategy(){ }
BinaryOpStrategy::~BinaryOpStrategy(){ }

class IntegerOpStrategy : public BinaryOpStrategy {
public:
    IntegerOpStrategy() {}
    ~IntegerOpStrategy() {}

    Value* codegen(llvm::Value* lhsCode, llvm::Value* rhsCode, TOKENS op, Compiler& c) override {
        Value* v = nullptr;
        switch (op) {
            case TOK_OP_ADD:
                return c.Builder->CreateAdd(lhsCode, rhsCode, "addtmp");
            case TOK_OP_MINUS:
                return c.Builder->CreateSub(lhsCode, rhsCode, "subtmp");
            case TOK_OP_TIMES:
                return c.Builder->CreateMul(lhsCode, rhsCode, "multmp");
            case TOK_OP_DIVIDE:
                return c.Builder->CreateSDiv(lhsCode, rhsCode, "divtmp");
            case TOK_OP_UNEQUAL:
                return c.Builder->CreateICmpNE(lhsCode, rhsCode, "uneqltemp");
            case TOK_OP_EQUAL:
                return c.Builder->CreateICmpEQ(lhsCode, rhsCode, "eqltemp");
            case TOK_OP_LE:
                return c.Builder->CreateICmpSLE(lhsCode, rhsCode, "leqtemp");
            case TOK_OP_LT:
                return c.Builder->CreateICmpSLT(lhsCode, rhsCode, "ltemp");
            case TOK_OP_GE:
                return c.Builder->CreateICmpSGE(lhsCode, rhsCode, "geqtemp");
            case TOK_OP_GT:
                return c.Builder->CreateICmpSGT(lhsCode, rhsCode, "gttemp");
            case TOK_OP_LEFTBRA:
                v = c.Builder->CreateGEP(lhsCode->getType(), lhsCode, rhsCode, "array") ;
                return c.Builder->CreateLoad(c.Builder->getInt32Ty(), v, "arrayElement");
            default:
                return nullptr;
        }
    }
};

class FloatOpStrategy : public BinaryOpStrategy {
public:
    FloatOpStrategy() {}
    ~FloatOpStrategy() {}

    llvm::Value* codegen(llvm::Value* lhsCode, llvm::Value* rhsCode, TOKENS op, Compiler& c) override {
        Value* v = nullptr;
        switch (op) {
            case TOK_OP_ADD:
                return c.Builder->CreateFAdd(lhsCode, rhsCode, "addtmp");
            case TOK_OP_MINUS:
                return c.Builder->CreateFSub(lhsCode, rhsCode, "subtmp");
            case TOK_OP_TIMES:
                return c.Builder->CreateFMul(lhsCode, rhsCode, "multmp");
            case TOK_OP_DIVIDE:
                return c.Builder->CreateFDiv(lhsCode, rhsCode, "divtmp");
            case TOK_OP_UNEQUAL:
                return c.Builder->CreateFCmpONE(lhsCode, rhsCode, "uneqltemp");
            case TOK_OP_EQUAL:
                return c.Builder->CreateFCmpOEQ(lhsCode, rhsCode, "eqltemp");
            case TOK_OP_LE:
                return c.Builder->CreateFCmpOLE(lhsCode, rhsCode, "leqtemp");
            case TOK_OP_LT:
                return c.Builder->CreateFCmpOLT(lhsCode, rhsCode, "ltemp");
            case TOK_OP_GE:
                return c.Builder->CreateFCmpOGE(lhsCode, rhsCode, "geqtemp");
            case TOK_OP_GT:
                return c.Builder->CreateFCmpOGT(lhsCode, rhsCode, "gttemp");
            case TOK_OP_LEFTBRA:
                v = c.Builder->CreateGEP(lhsCode->getType(), lhsCode, rhsCode, "array");
                return c.Builder->CreateLoad(c.Builder->getDoubleTy(), v, "arrayElement");
            default:
                return nullptr;
        }
    }
};

class BoolOpStrategy : public BinaryOpStrategy {
public:
    BoolOpStrategy() {}
    ~BoolOpStrategy() {}

    llvm::Value* codegen(llvm::Value* lhsCode, llvm::Value* rhsCode, TOKENS op, Compiler& c) override {
        switch (op) {
            case TOK_OP_AND:
                return c.Builder->CreateLogicalAnd(lhsCode, rhsCode, "logicalAnd");
                break;
            case TOK_OP_OR:
                return c.Builder->CreateLogicalOr(lhsCode, rhsCode, "logicalAnd");
                break;
            default:
                return nullptr;
        }
    }
};

static BoolOpStrategy boolOpStrategy;
static IntegerOpStrategy integerOpStrategy;
static FloatOpStrategy floatOpStrategy;


BinaryOpStrategy& BinaryOpStrategy::getStrategy(EVALTYPE type) {
    switch (type) {
        case INTEGER:
            return integerOpStrategy;
        case FLOAT:
            return floatOpStrategy;
        case BOOL:
            return boolOpStrategy;
        default:
            break;
    }
}