#ifndef __DoubleType_Header__
#define __DoubleType_Header__

#include "TypeInfo.h"

class DoubleTypeInfo : public TypeInfo {
public:
    DoubleTypeInfo();
    ~DoubleTypeInfo();

    llvm::Type* toLLVMType(llvm::LLVMContext*) override;
    EVALTYPE getEvalType() override;
};

#endif