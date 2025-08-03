#ifndef __PAESER_HEADER__
#define __PAESER_HEADER__

#include "Token.h" 
#include "Scanner.h"

class Expression;
class DeclareNode;
class BlockNode;

class Parser{
private:
    Scanner& s;
    Expression* parsePrimary();
    Expression* parseUnary();
    Expression* parseIndExpression();
    Expression* parseParExpression();
    Expression* parseExpression();
    Expression* parseInteger();
    Expression* parseDouble();
    Expression* parseGlobalDeclare();
    Expression* parseBinOpRhs(int, Expression*);
    Expression* parseFunction(string, TOKENS);
    Expression* parseDeclare();
    BlockNode* parseBlock();
    Expression* parseReturn();
    DeclareNode* parseFunctionDeclare();
    Expression* parseIf();

public:
    Parser();
    Parser(Scanner&);
    ~Parser();
    Expression* parseLine();
};

#include "asts/Expression.h"
#include "asts/BlockNode.h"
#include "asts/DeclareNode.h"
#include "asts/FunctionAST.h"
#include "asts/PrototypeAST.h"

#endif
