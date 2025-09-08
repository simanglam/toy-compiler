#ifndef __MemoryType_Header__
#define __MemoryType_Header__

#include "TypeInfo.h"

class MemoryType : public TypeInfo {
    TypeInfo* baseType;
    int depth;
public:
    MemoryType(TypeInfo*, int);
    ~MemoryType();

    llvm::Type* getType(llvm::LLVMContext*) override;
    llvm::Type* getBaseType();
    int getDepth();
    EVALTYPE getEvalType() override;
};

#endif