#ifndef __BaseAST_HEADER__
#define __BaseAST_HEADER__

class BaseAST;

#include <string>
#include <llvm/IR/Value.h>

#include "Compiler.h"

using namespace llvm;
using namespace std;

class BaseAST{
public:
    BaseAST();
    virtual ~BaseAST();
    virtual void print() = 0;
    virtual Value* codegen(Compiler&) = 0;
    virtual int result() = 0;
};

#endif