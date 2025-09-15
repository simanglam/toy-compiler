#ifndef __PAESER_HEADER__
#define __PAESER_HEADER__

#include "Token.h" 
#include "Scanner.h"
#include "types/TypeInfo.h"

class Expression;
class DeclareNode;
class BlockNode;
class Statement;
class ASTNode;

class Parser{
private:
    Scanner& s;
    ASTNode* parseLinePrimary();
    Expression* parsePrimary();
    Expression* parseUnary();
    Expression* parseIndExpression();
    Expression* parseParExpression();
    Expression* parseExpression();
    Expression* parseInteger();
    Expression* parseDouble();
    Expression* parseBinOpRhs(int, Expression*);
    BlockNode* parseBlock();
    Statement* parseReturn();
    Statement* parseFunction(string, TypeInfo*);
    Statement* parseGlobalDeclare();
    Statement* parseDeclare();
    DeclareNode* parseFunctionDeclare();
    Statement* parseIf();

public:
    Parser();
    Parser(Scanner&);
    ~Parser();
    ASTNode* parseLine();
};

#include "asts/ASTNode.h"
#include "asts/Expression.h"
#include "asts/Statement.h"
#include "asts/BlockNode.h"
#include "asts/DeclareNode.h"
#include "asts/FunctionAST.h"
#include "asts/PrototypeAST.h"

#endif
