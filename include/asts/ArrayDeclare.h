#ifndef __ArrayDeclare_HEADER__
#define __ArrayDeclare_HEADER__

#include "BaseExpr.h"

class ArrayDeclare: public BaseExpr {
    TOKENS type;
    vector<BaseExpr*> values;
    BaseExpr* size;
    string name;
public:
    ArrayDeclare(TOKENS, vector<BaseExpr*>&, BaseExpr*, string&);
    ~ArrayDeclare();
    Value* codegen(Compiler&) override;
    bool eval(Analyser&) override;
};


#endif