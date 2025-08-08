#include "Compiler.h"
#include "asts/CastNode.h"

CastNodeStrategy::CastNodeStrategy() {}
CastNodeStrategy::~CastNodeStrategy() {}

class FloatCastStrategy : public CastNodeStrategy {
public:

    llvm::Value* cast(llvm::Value* v, EVALTYPE target, Compiler& c) override {
        switch (target) {
            case INTEGER:
                return c.Builder->CreateFPToSI(v, c.Builder->getInt32Ty(), "FpToInt");
            case BOOL:
                return c.Builder->CreateFCmpONE(v, ConstantFP::get(c.Builder->getDoubleTy(), 0.0), "FpToBool");
            default:
                cerr << "Not able to cast type Float to typeid: " << target << endl;
                return nullptr;
        }
    }

    bool eval(EVALTYPE target) override {
        switch (target) {
            case INTEGER:
                return true;
            case BOOL:
                return true;
            default:
                cerr << "Not able to cast type Float to typeid: " << target << endl;
                return false;
        }
    }
};

class IntegerCastStrategy : public CastNodeStrategy {
public:

    llvm::Value* cast(llvm::Value* v, EVALTYPE target, Compiler& c) override {
        switch (target) {
            case FLOAT:
                return c.Builder->CreateSIToFP(v, c.Builder->getDoubleTy(), "FpToInt");
            case BOOL:
                return c.Builder->CreateICmpNE(v, c.Builder->getInt32(0), "FpToBool");
            default:
                cerr << "Not able to cast type Float to typeid: " << target << endl;
                return nullptr;
        }
    }

    bool eval(EVALTYPE) override {

    }
};

class PointerCastStrategy : public CastNodeStrategy {
public:

    llvm::Value* cast(llvm::Value* v, EVALTYPE target, Compiler& c) override {
        switch (target) {
            case FLOAT:
                return c.Builder->CreateSIToFP(v, c.Builder->getDoubleTy(), "IntToFp");
            case BOOL:
                return c.Builder->CreateICmpNE(v, c.Builder->getInt32(0), "IntToBool");
            default:
                cerr << "Not able to cast type Float to typeid: " << target << endl;
                return nullptr;
        }
    }

    bool eval(EVALTYPE target) override {
        switch (target) {
            case FLOAT:
                return true;
            case BOOL:
                return true;
            default:
                cerr << "Not able to cast type Integer to typeid: " << target << endl;
                return false;
        }
    }
};

class BoolCastStrategy : public CastNodeStrategy {
public:

    llvm::Value* cast(llvm::Value* v, EVALTYPE target, Compiler& c) override {
        switch (target) {
            case FLOAT:
                return c.Builder->CreateSIToFP(v, c.Builder->getDoubleTy(), "IntToFp");
            case INTEGER:
                return c.Builder->CreateIntCast(v, c.Builder->getInt32Ty(), true, "IntToBool");
            default:
                cerr << "Not able to cast type Bool to typeid: " << target << endl;
                return nullptr;
        }
    }

    bool eval(EVALTYPE target) override {
        switch (target) {
            case FLOAT:
                return true;
            case BOOL:
                return true;
            default:
                cerr << "Not able to cast type Float to typeid: " << target << endl;
                return false;
        }
    }
};

class ErrorCastStrategy : public CastNodeStrategy {
public:

    llvm::Value* cast(llvm::Value* v, EVALTYPE target, Compiler& c) override {
        return nullptr;
    }

    bool eval(EVALTYPE target) override {
        return false;
    }
};

static BoolCastStrategy boolCastStrategy;
static IntegerCastStrategy integerCastStrategy;
static FloatCastStrategy floatCastStrategy;
static ErrorCastStrategy errorCastStrategy;

CastNodeStrategy& CastNodeStrategy::getCastStrategy(EVALTYPE target) {
    switch (target){
    case BOOL:
        return boolCastStrategy;
    case INTEGER:
        return integerCastStrategy;
    case FLOAT:
        return floatCastStrategy;
    default:
        return errorCastStrategy;
    }
}