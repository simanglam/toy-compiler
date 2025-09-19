#include <llvm/IR/Type.h>

#include "types/MemoryType.h"

MemoryType::MemoryType(TypeInfo* _baseType): baseType(_baseType) {

}

MemoryType::~MemoryType() {
}

llvm::Type* MemoryType::toLLVMType(llvm::LLVMContext* c){
    return (llvm::Type*)baseType->toLLVMType(c)->getPointerTo();
}

EVALTYPE MemoryType::getEvalType() {
    return INT_POINTER;
}