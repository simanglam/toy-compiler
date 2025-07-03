#ifndef __PAESER_HEADER__
#define __PAESER_HEADER__

class Parser;

#include "Token.h" 
#include "Scanner.h"
#include "asts/BaseAST.h"

class Parser{
private:
    Scanner& s;
    BaseAST* parsePrimary();
    BaseAST* parseIndExpression();
    BaseAST* parseParExpression();
    BaseAST* parseExpression();
    BaseAST* parseNumber();
    BaseAST* parseBinOpRhs(int, BaseAST*);
public:
    Parser(Scanner&);
    ~Parser();
    BaseAST* parseLine();
};

#endif