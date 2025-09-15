#include <llvm/IR/Type.h>

#include "types/SignedInt32Type.h"

using namespace llvm;

SignedInt32Type::SignedInt32Type() {

}

SignedInt32Type::~SignedInt32Type() {

}

Type* SignedInt32Type::toLLVMType(LLVMContext* c) {
    return (Type*)Type::getInt32Ty(*c);
}

EVALTYPE SignedInt32Type::getEvalType() {
    return INTEGER;
}