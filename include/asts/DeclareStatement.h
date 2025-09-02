#ifndef __DeclareStatement_Header__
#define __DeclareStatement_Header__

#include <vector>

#include "asts/DeclareNode.h"
#include "asts/Statement.h"

class DeclareStatement : public Statement {
    TOKENS type;
    vector<DeclareNode*> declares;
public:
    DeclareStatement();
    ~DeclareStatement();

    void pushNode(DeclareNode*);

    bool eval(Analyser& ) override;
    void codegen(Compiler&) override;
    
};

#endif