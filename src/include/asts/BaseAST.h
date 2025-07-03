#ifndef __BaseAST_HEADER__
#define __BaseAST_HEADER__

#include <string>
#include <llvm/IR/Value.h>


using namespace llvm;
using namespace std;

class BaseAST{
public:
    BaseAST();
    virtual ~BaseAST();
    virtual void print() = 0;
    virtual Value* codegen() = 0;
    virtual int result() = 0;
};

#endif