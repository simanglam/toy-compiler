#include <llvm/IR/Type.h>

#include "types/DoubleTypeInfo.h"

using namespace llvm;

DoubleTypeInfo::DoubleTypeInfo() {}

DoubleTypeInfo::~DoubleTypeInfo() {}

Type* DoubleTypeInfo::toLLVMType(LLVMContext* c) {
    return Type::getDoubleTy(*c);
} 

EVALTYPE DoubleTypeInfo::getEvalType() {
    return FLOAT;
}