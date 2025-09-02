#include <llvm/IR/Type.h>

#include "types/DoubleType.h"

using namespace llvm;

DoubleType::DoubleType() {}

DoubleType::~DoubleType() {}

Type* DoubleType::getType(LLVMContext* c) {
    return Type::getDoubleTy(*c);
} 

EVALTYPE DoubleType::getEvalType() {
    return FLOAT;
}