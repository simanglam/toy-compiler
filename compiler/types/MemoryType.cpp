#include <llvm/IR/Type.h>

#include "types/MemoryType.h"

MemoryType::MemoryType(TypeInfo* _baseType, int _depth): baseType(_baseType), depth(_depth) {

}

MemoryType::~MemoryType() {
}

llvm::Type* MemoryType::getType(llvm::LLVMContext* c){
    return (llvm::Type*)baseType->getType(c)->getPointerTo();
}

EVALTYPE MemoryType::getEvalType() {
    return INT_POINTER;
}