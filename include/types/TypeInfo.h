#ifndef __TypeInfo_Header__
#define __TypeInfo_Header__

#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>

#include "EvalType.h"

class TypeInfo {
public:
    TypeInfo();
    virtual ~TypeInfo() = 0;

    virtual llvm::Type* getType(llvm::LLVMContext*) = 0;
    virtual EVALTYPE getEvalType() = 0;
};


#endif