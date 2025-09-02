#ifndef __DoubleType_Header__
#define __DoubleType_Header__

#include "TypeInfo.h"

class DoubleType : public TypeInfo {
public:
    DoubleType();
    ~DoubleType();

    llvm::Type* getType(llvm::LLVMContext*) override;
    EVALTYPE getEvalType() override;
};

#endif