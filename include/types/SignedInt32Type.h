#ifndef __SignedInt32Type_Header__
#define __SignedInt32Type_Header__

#include "TypeInfo.h"

class SignedInt32Type : public TypeInfo {
public:
    SignedInt32Type();
    ~SignedInt32Type();

    llvm::Type* getType(llvm::LLVMContext*) override;
    EVALTYPE getEvalType() override;
};

#endif