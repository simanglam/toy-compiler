#ifndef __PAESER_HEADER__
#define __PAESER_HEADER__

class Parser;

#include "Token.h" 
#include "Scanner.h"
#include "asts/BaseExpr.h"
#include "asts/BlockNode.h"
#include "asts/DeclareNode.h"
#include "asts/FunctionAST.h"
#include "asts/PrototypeAST.h"

class Parser{
private:
    Scanner& s;
    BaseExpr* parsePrimary();
    BaseExpr* parseIndExpression();
    BaseExpr* parseParExpression();
    BaseExpr* parseExpression();
    BaseExpr* parseNumber();
    BaseExpr* parseGlobalDeclare();
    BaseExpr* parseBinOpRhs(int, BaseExpr*);
    BaseExpr* parseFunction(string, TOKENS);
    DeclareNode* parseDeclare();
    BlockNode* parseBlock();
    BaseExpr* parseReturn();
    DeclareNode* parseFunctionDeclare();

public:
    Parser(Scanner&);
    ~Parser();
    BaseExpr* parseLine();
};

#endif
