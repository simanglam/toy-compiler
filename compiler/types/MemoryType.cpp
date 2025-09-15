#include <llvm/IR/Type.h>

#include "types/MemoryType.h"

MemoryType::MemoryType(TypeInfo* _baseType, int _depth): baseType(_baseType), depth(_depth) {

}

MemoryType::~MemoryType() {
}

llvm::Type* MemoryType::toLLVMType(llvm::LLVMContext* c){
    return (llvm::Type*)baseType->toLLVMType(c)->getPointerTo();
}

EVALTYPE MemoryType::getEvalType() {
    return INT_POINTER;
}